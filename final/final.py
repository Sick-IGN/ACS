import threading
import time
import random
import multiprocessing

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = merge_sort(arr[:mid])
    right_half = merge_sort(arr[mid:])
    return merge(left_half, right_half)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def merge_sort_multithreaded(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    left_thread = multiprocessing.Process(target=merge_sort_helper, args=(left_half,))
    right_thread = multiprocessing.Process(target=merge_sort_helper, args=(right_half,))
    left_thread.start()
    right_thread.start()
    left_thread.join()
    right_thread.join()
    return merge(left_half, right_half)

def merge_sort_helper(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    merge_sort_helper(left_half)
    merge_sort_helper(right_half)
    arr[:] = merge(left_half, right_half)

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def quick_sort_helper(sub_arr):
    return quick_sort(sub_arr)

def quick_sort_multithreaded(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    with multiprocessing.Pool(processes=2) as pool:
        left_result, right_result = pool.map(quick_sort_helper, [left, right])
    
    return left_result + middle + right_result

def test_sorting_algorithms():
    n = 10000

    arr = [random.randint(1, 1000000) for _ in range(n)]
    
    # Testing Merge Sort
    start = time.time()
    merge_sorted = merge_sort(arr.copy())
    end = time.time()
    print(f"Merge Sort Time: {end - start:.6f} seconds")
    
    # Testing Multithreaded Merge Sort
    start = time.time()
    merge_sorted_mt = merge_sort_multithreaded(arr.copy())
    end = time.time()
    print(f"Multithreaded Merge Sort Time: {end - start:.6f} seconds")
    
    # Testing Quick Sort
    start = time.time()
    quick_sorted = quick_sort(arr.copy())
    end = time.time()
    print(f"Quick Sort Time: {end - start:.6f} seconds")
    
    # Testing Multithreaded Quick Sort
    start = time.time()
    quick_sorted_mt = quick_sort_multithreaded(arr.copy())
    end = time.time()
    print(f"Multithreaded Quick Sort Time: {end - start:.6f} seconds")
    
    start = time.time()
    quick_sorted_mt = sorted(arr.copy())
    end = time.time()
    print(f"native: {end - start:.6f} seconds")

if __name__ == "__main__":
    test_sorting_algorithms()