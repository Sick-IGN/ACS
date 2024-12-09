import cupy as cp
import time
import random

def gpu_radix_sort(arr, max_bits=32):
    if not isinstance(arr, cp.ndarray):
        raise TypeError("Input must be a CuPy array.")
    
    num_bits = 8
    num_buckets = 1 << num_bits  
    mask = num_buckets - 1
    
    n = arr.size
    output = cp.empty_like(arr)

    for shift in range(0, max_bits, num_bits):
        digit = (arr >> shift) & mask  
        histogram = cp.zeros(num_buckets, dtype=cp.int32)
        
        kernel_histogram = cp.ElementwiseKernel(
            'int32 x, int32 mask, int32 shift',
            'raw int32 hist',
            '''
            unsigned int d = (x >> shift) & mask;
            hist[d] += 1;
            ''',
            'compute_histogram',
        )
        kernel_histogram(arr, mask, shift, histogram)
        
        cumsum = cp.cumsum(histogram, dtype=cp.int32) - histogram
        
        scatter_indices = cp.zeros_like(arr)
        kernel_scatter_indices = cp.ElementwiseKernel(
            'int32 x, raw int32 cumsum, int32 mask, int32 shift',
            'raw int32 scatter_indices',
            '''
            unsigned int d = (x >> shift) & mask;
            scatter_indices[i] = cumsum[d];
            ''',
            'compute_scatter_indices',
        )
        kernel_scatter_indices(arr, cumsum, mask, shift, scatter_indices)
        
        output[scatter_indices] = arr
        
        arr[:] = output[:]
    
    return arr



if __name__ == "__main__":
    import random
    n = 1000000000
    arr = [random.randint(0, 1000000) for _ in range(n)]
    cupy_array = cp.array(arr, dtype=cp.int32)

    start = time.time()
    sorted_arr_gpu = gpu_radix_sort(cupy_array)
    end = time.time()

    print(f"{end - start:.6f}")