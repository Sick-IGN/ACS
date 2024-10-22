# Project 3

### Background

All tests were performed on a Sabrent Rocket 4.0 Plus (1TB).
All tests were ran for 60 seconds.
Occasionally, Block Size, Queue Depth, and Read ratio are kept constant to eliminate them as variables while testing other things.

For block size, I kept it constant at 16KB, as this is a moderate value that doesn't unnecessarily load the SSD.
Queue depth was set to 1, as this most replicates an ideal system.
Read ratio was kept at 100%. 

These values provide a reasonable bar for comparison for performance. 

## Latency

### Block Size

The first series of tests were done to measure latency as block size changes for a **read only** environment.
Block size was varied from 4KB to 512KB, and latency was recorded in microseconds. Queue depth was also kept constant.

The command used was as below, where **X** was varied
fio.exe --name=read_**X**k --rw=read --bs=**X**k --numjobs=1 --iodepth=1 --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Latency vs Block Size](https://i.gyazo.com/4659dfd14b639b8729ae35832f2e75e8.png)

Interestingly, this shows an extremely linear relationship between block size and latency, which makes sense. Long block sizes would obviously take more time to access. However, I was expecting it to be either an exponential or logarithmic graph, as a lot of disk activies are one of the those two.

This seems to show that there is little overhead, and most of the latency comes simply from reading the data. With a traditional spinning hard drive I would expect differing results. With a spinning drive, the seek time is a significant overhead, but once the data is found, reading a continuous block is relatively faster. Therefore, in that instance, it would make sense to have a more logarithmic graph, as the larger block size reduces the extremely slow seeking. As for a modern SSD, that is not necessary, and it can just find the data at a constant time cost, and the only other cost is the linear read cost.

### Read/Write ratio

The next series of tests were doen to measure latency as read/write ratio varies.
Tests were done on 100%, 70%, 50%, 30%, and 0% read. Block size was kept constant at 16KB and Queue depth remained constant at 1.

The command used was as below, where **X** was varied
fio.exe --name=rw_**X** --rw=rw --rwmixread=**X** --bs=16k --numjobs=1 --iodepth=1 --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Latency vs Read/Write Ratio](https://i.gyazo.com/69dfdea10682b5e9fb06e4061a821a91.png)

This graph shows there is almost no correlation between read/write ratio and latency. The write latency is slightly higher then the read latency, but this is expected, as writing is more technically demanding of an action then reading.

Since the data written per operation (block size) is constant, there is the same overhead and the same time to operation completion for every action, regardless of how many writes or reads occur. Each individual read and write is a seperate operation that takes its set amount of time to complete. Since the IO queue depth, or load, is the same for each operation, there is no reason for any slowdown.

### I/O queue

The final series of latency tests were done to measure latency as IODepth changed.
Tests were done with a queue depth of 1, 4, 32, 256, and 1024. Block size was constant at 16KB, and operations were read only.

The command used was as below, where **X** was varied
fio.exe --name=qd_**X** --rw=read --bs=16k --numjobs=1 --iodepth=**X** --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Latency vs Queue Depth](https://i.gyazo.com/2f739bae0e54831d7c5cb768b2e42fb4.png)

This result makes a lot of sense. A linear relationship for latency is very straightforward. According to Littles law:

L = λ ⋅ W

Where L is queue length,
λ is Arrival rate, and 
W is time in the system.

In our system, L is what we are varying.
λ is relatively constant, as assuming queue length is constant, it is also the speed at which we can serve a request. In this case, we have W, or latency, varying linearly based on L.
This relationship is proven by our graph. As queue length increases, each operation must wait in the queue for a lineraly increasing amount of time.

## Bandwidth

### Block Size

This first bandwidth experiment was designed to determine the effect of block size on throughput. As such, queue depth and read/write latency was kept constant, at 1 and 100% read.

The command used was as below, where **X** was varied
fio.exe --name=read_**X**k --rw=read --bs=**X**k --numjobs=1 --iodepth=1 --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Throughput vs Block Size](https://i.gyazo.com/ca1211fbf38304ff2b8d6b4a77c27594.png)

I have included graphs for throughput in IOPS and MBps, as I believe they both provide important context. As shown, increased block size leads to less overall IOPS. This is likely due to each individual operation taking longer due to more data being read, as shown previously with the increased latency. However, as block size goes up, so does the data access with each operation, and therefore throughput in MBps overall goes up.

This is interesting to note, as it is important to keep in mind that IOPS isn't the best metric for performance if block size is varied.

### Read/Write ratio

The next series of tests were doen to measure Throughput as read/write ratio varies.
Tests were done on 100%, 70%, 50%, 30%, and 0% read. Block size was kept constant at 16KB and Queue depth remained constant at 1.

The command used was as below, where **X** was varied
fio.exe --name=rw_**X** --rw=rw --rwmixread=**X** --bs=16k --numjobs=1 --iodepth=1 --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Throughput vs Read/Write Ratio](https://i.gyazo.com/e81428d4149495ceda5af7b9021bf669.png)

This shows similar results to latency. Most notably, that read/write ratio does not impact performance. As expected, write IOPS are slightly more demanding, so total IOPS does go down slightly. But the normalized IOPS (factoring in only a X% of all operations are writes and accounting for that in the data) shows a fairly steady throughput.

### I/O queue

The final series of throughput tests were done to measure throughput as IODepth changed.
Tests were done with a queue depth of 1, 4, 32, 256, and 1024. Block size was constant at 16KB, and operations were read only.

The command used was as below, where **X** was varied
fio.exe --name=qd_**X** --rw=read --bs=16k --numjobs=1 --iodepth=**X** --size=1G --runtime=60 --time_based --group_reporting --filename=E:\testfile

![Throughput vs Queue Depth](https://i.gyazo.com/70ef36f0c47bfdfb32f1cdb7b4caa5da.png)

This is an unusual graph. Throughput starts very low, then jumps up to a peak at lower-mid depth values, and then slowly decreases.

The low starting throughput is likely due to inefficiencies with minimal queues. If there is only 1 item in the system, then once the first one leaves, the system must wait for the next and perform some setup once it receives the item, likely causing some overhead. If the queue is above 1 but still small, then optimizations can be made to quickly transition from processing the first item to the next item

## Extra Analysis

None of my other experiments included a random write-only 4KB test, so I performed one, seeing an IOPS of 37.6k and a latency of 25.63us.
While I do not believe I got the results that were expected, I still have an explanation as to why a consumer-grade SSD might have higher IOPS then an enterprise-grade SSD.

The primary reason is likely the difference in consumer and enterprise workloads and priorities. For example, a typical consumer likely occasionally loads relatively small files, with their disk sitting at low utilization for a majority of the time.
A lot of consumer SSD implement cache, which allows them to hit extremely high burst speeds. My 3 year old SSD, a generation out of date, advertises a peak sequential read of 7100MBps, practically getting 6000MBps. However, these speeds are typically only sustainable for a short period of time, on the scale of a minute or so. After this point, the SSD noticably slows down. However, this is typically not a big concern for consumers, as most don't need to read at top speed for multiple minutes straight. A multiple hundred GB program can be read from disk in under a minute, and very few consumers need to do this consistantly. 

This is in direct contrast to enterprise workloads. These SSDs typically don't need as high burst speeds, but need more sustainable high speeds as well as more reliability and longevity. An enterprise SSD can be expected to be under high load almost constantly, and it must be designed to withstand high load for long periods of time.

An important piece of data that proves this is the endurance rating. My SSD, the Sabrent Rocket 4.0 Plus, has TBW value of up to 1400, meaning it can be expected to write 1400TB of data to itself before failing. As they say "up to" this is likely for their highest capacity version, which is 8TB. To contrast, the D7-P5600, with a max capacity of 6.4TB, has a TBW of 8800. When adjusted for overall storage capacity, this is almost 8x the expected lifespan. The D7-P5600 is also advertised to have half the sequential read bandwidth and a fourth the sequential read bandwidth, which goes to show that the consumer SSD space and enterprise SSD space are not directly comparable, due to different customer priorities.

### Raw Data

#### Varying Block Size

| Block Size (KB) | IOPS   | MBps | Latency (us) |
|------------------|--------|------|---------------|
| 4                | 54000  | 221  | 17.76         |
| 16               | 48800  | 799  | 19.78         |
| 32               | 40800  | 1336 | 23.75         |
| 128              | 22300  | 2917 | 44.1          |
| 512              | 7549   | 3958 | 131.29        |

#### Varying Read/Write Percentage

| Read % | Read IOPS | Read MBps | Read Latency (us) | Write IOPS | Write MBps | Write Latency (us) | Normalized Read | Normalized Write |
|--------|-----------|-----------|--------------------|------------|------------|---------------------|------------------|-------------------|
| 100%   | 47800     | 783       | 20.17              | NA         | NA         | NA                  | 47800            | NA                |
| 70%    | 28500     | 467       | 21.55              | 12100      | 199        | 28.46               | 40714.28571      | 40333.33333       |
| 50%    | 20600     | 337       | 20.29              | 20500      | 336        | 26.39               | 41200            | 41000             |
| 30%    | 11900     | 195       | 20.95              | 27600      | 452        | 25.92               | 39666.66667      | 39428.57143       |
| 0%     | NA        | NA        | NA                 | 37000      | 607        | 25.79               | NA               | 37000             |

#### Varying Queue Depth

| Queue Depth | IOPS   | MBps | Latency (us) |
|-------------|--------|------|---------------|
| 1           | 46500  | 762  | 20.7          |
| 4           | 101000 | 1657 | 29.28         |
| 32          | 108000 | 1769 | 155.56        |
| 256         | 106000 | 1735 | 1200.89       |
| 1024        | 94300  | 1545 | 5363.49       |