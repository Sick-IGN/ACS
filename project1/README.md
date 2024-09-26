# Project 1

## Background

For context, all work has been done on a machine with the following specifications.

CPU: Ryzen 9 3900X, 12 cores @ 4.2GHz
64KB L1 cache per core
512KB L2 cache per core
64MB L3 cache shared

RAM: Corsair Vengeance RGB Pro
4 * 16GB
3200MHz, CL16

## Objective 1

To measure latency of varied types of cache and memory with a queue of length 0, Intel Memory Latency Checker was used.
Buffer size was varied to test different caches, and the --idle_latency flag was used to check with an unloaded system, where the queue length should be near 0.
Tests were ran with the computer under minimal load to ensure as close to 0 queue length as possible.

### L1 cache

A buffer size of 1KB was used, which can completely fit in L1 cache.
Running 5 tests, results were 3.6-3.7 frequency clocks, or 0.9-1.0ns

### L2 cache

A buffer size of 100KB was used, which is bigger then L1 cache but can fit in L2 cache.
Running 5 tests, results were 9.5-9.6 frequency clocks, or 2.5ns

### L3 cache

A buffer size of 10MB was used, which is bigger then L2 cache but can fit in L3 cache.
Results varied significantly more then with smaller cache sizes.
This is likely due to the cache being shared among CPUs. With L1 or L2 cache, it is possible for the specific cache to exclusively be utilized by the program doing the analysis. 
Any other programs would likely primarily be using a different core, or only minimal other processing would be happening on the single core. 
With the L3 cache, all cores are accessing it, so it likely has higher utilization and variability due background OS processes and the browser I have open.
I ran 18 tests. These resulted in an average of 105.4 cycles / 27.8 ns, a median of 89.1 cycles / 23.45 ns, a minimum of 42.9 cycles / 11.3 ns, and a maximum of 404.3 cycles / 106.6 ns.
An interesting note, I noticed my CPU fan spin up right before the max, and spin down shortly after it. There was likely some background process running at that moment that taxed a core slightly, which is reflected by my measurements.

### Memory

A buffer size of 100MB was used, which can only fit into memory.
Oddly, results varied significantly less then with L3 cache. My assumption is that it simply has lower utilization. 
Since most of the running processes are background processes and typically small, there likely arent many large read or write operations that would require sizes larger then what is available in L3 cache.
This lower utilization likely causes more standard measurements, close to ideal.
I ran 5 tests, averaging 451 cycles / 124 ns.

### Results

| L1 | L2| L3| MEM|
|---|---|---|---|
| 1.0 ns | 2.5 ns | 23.5 ns | 124 ns |


According to research, expected values for L1, L2, and L3 cache and memory are 1-4ns, 4-12ns, 10-30ns, and 50-150ns.
My values are all within reasonable margins. For L1, and L2 cache, my system is defintely on the quicker side, however this is likely due to me having a very powerful processor. 
It likely has quicker then average ram, combined with my researched values likely being a bit old. For my L3 cache measurements, most of my values are within the expected range.
While I do have some outliers, this can be explained by my system being under slight load, and there unfortunately being a queue.
If you remove some of the extremes, it more closely lines up to expected values. Finally, my memory latency is within the range of expected values.
While on the higher end, this makes sense for my system, as larger amounts of memory attached can increase latency according to my research.
As well, my systems memory is not at all optimized, overclocked, or even that high end hardware, so the slightly higher latency is reasonable.


## Objective 2

### Intro

A simple C program (obj2.c) was written to accomplish this.
A large array was created, and then read from and written to in different ratios with different simulated block sizes.
Research was also done beforehand as to what general trends should look like, so the data gathered could be confirmed.


### Results

| Type  |     Granularity     |  Read Ratio  |        Bandwidth         |
|-------|---------------------|--------------|--------------------------|
| Read  | Granularity:    64B | Ratio:  1.00 | Bandwidth:    17.13 GB/s |
| Read  | Granularity:    64B | Ratio:  0.70 | Bandwidth:    17.20 GB/s |
| Read  | Granularity:    64B | Ratio:  0.50 | Bandwidth:    16.14 GB/s |
| Read  | Granularity:    64B | Ratio:  0.30 | Bandwidth:    15.26 GB/s |
| Write | Granularity:    64B | Ratio:  0.70 | Bandwidth:    10.74 GB/s |
| Write | Granularity:    64B | Ratio:  0.50 | Bandwidth:    10.52 GB/s |
| Write | Granularity:    64B | Ratio:  0.30 | Bandwidth:     9.57 GB/s |
| Write | Granularity:    64B | Ratio:  0.00 | Bandwidth:    10.21 GB/s |
|       |                     |              |                          |
| Read  | Granularity:   256B | Ratio:  1.00 | Bandwidth:    25.67 GB/s |
| Read  | Granularity:   256B | Ratio:  0.70 | Bandwidth:    26.40 GB/s |
| Read  | Granularity:   256B | Ratio:  0.50 | Bandwidth:    27.18 GB/s |
| Read  | Granularity:   256B | Ratio:  0.30 | Bandwidth:    27.14 GB/s |
| Write | Granularity:   256B | Ratio:  0.70 | Bandwidth:     9.43 GB/s |
| Write | Granularity:   256B | Ratio:  0.50 | Bandwidth:     9.32 GB/s |
| Write | Granularity:   256B | Ratio:  0.30 | Bandwidth:    10.41 GB/s |
| Write | Granularity:   256B | Ratio:  0.00 | Bandwidth:    10.51 GB/s |
|       |                     |              |                          |
| Read  | Granularity:  1024B | Ratio:  1.00 | Bandwidth:    63.69 GB/s |
| Read  | Granularity:  1024B | Ratio:  0.70 | Bandwidth:    77.38 GB/s |
| Read  | Granularity:  1024B | Ratio:  0.50 | Bandwidth:    80.13 GB/s |
| Read  | Granularity:  1024B | Ratio:  0.30 | Bandwidth:    76.39 GB/s |
| Write | Granularity:  1024B | Ratio:  0.70 | Bandwidth:    10.54 GB/s |
| Write | Granularity:  1024B | Ratio:  0.50 | Bandwidth:    10.39 GB/s |
| Write | Granularity:  1024B | Ratio:  0.30 | Bandwidth:    10.16 GB/s |
| Write | Granularity:  1024B | Ratio:  0.00 | Bandwidth:     8.41 GB/s |

Bandwidth increased as granularity goes up. This matched research, as larger block sizes result in less overhead when fetching data.
Read speed is also significantly faster then write speed, as is expected.

## Objective 3

### Intro

  Littles Law states that 

### Experiment

  Intel Memory Latency Checker is capable of simulating high latency in memory, as this feature was used to collect the data.

### Results

![Graph of Latency vs Bandwidth](https://i.gyazo.com/7ca48d398e3229c1a9f85bcdd502d175.png)

Littles law states:

$$ L = \lambda W $$

where:
- $L$ is the average number of items in a queue,
- $\lambda$ is the average arrival rate,
- $W$ is the average time an items spends in the queue. In practice, this would represent our latency.

  If $L$ is increasing, the system is getting backed up, and cannot handle the number of requests.
This is a bad case, and we aim to avoid that. Worst case, lets assume $L$ is constant at a value.
When $L$ is constant, our system can perfectly handle the amount of requests, and no increasing slowdown occurs.

Assuming $L$ is constant, if $W$, or latency, increases $\lambda$ must decrease in order to prevent our system from becoming backed up with requests. 
This directly means that our throughput must decrease. The experiment done shows this. As latency increases, throughput must decrease, as each request takes longer to service.

## Objective 4

### Experiment

A simple C program was written to simulate cache miss ratios.
Two 2000x2000 matrices seeded with random values were multiplied.

The first trial had the matricies set as volatile, preventing caching and forcing memory access for every read operation.
The second trial had the matricies set as const, allowing for caching.

A simple, unoptimized matrix multiplication algorithm was used.

### Results

These trials were repeated twice, and both times the optimized multiplication was faster.
Volatile multiplication took 57.6 seconds and 56.6 seconds, and const multiplication took 54.2 seconds and 53.2 seconds

Running this in valgrind's cachegrind tool, we see around double the L3 cache misses, and a slight increase for L1 and L2 cache misses, confirming our analysis.

While this is only a slight speed decrease, this experiment is definitely not ideal. A more complicated method to force cache misses could be devised. 
However, this is sufficient to prove that cache misses increase runtime.

## Objective 5

### Experiment

A simple C program was written to simulate TLB misses.
Two long, randomly seeded arrays were looped through, and the values multipled.

4 different experiments were run with varying strides. The index was incremented by 1, 512, 1024, and 10 * 1024. 
This was done to simulate TLB misses, as the TLB often stores associated pages. 
By increasing the stride, you are accessinng elements in memory that are farther apart, often increasing the TLB miss ratio.


### Result

|Stride|Runtime|
| | |
|1|3.3 seconds|
|512|24.5 seconds|
|1024|27.7 seconds|
|10 * 1024|38.0 seconds|

This result is reasonable as to what should be expected. When the stride is 1, there are the fewest TLB misses. 
This causes the best runtime by far. When the stride is increased, memory access is more random, and there are more TLB misses. 
This causes an significant increase in runtime, to a point. Once TLB misses are high, further increasing the stride doesnt significantly increase runtime further.