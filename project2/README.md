# Project 2

## Background

Each function has the ability to run with multiple threads, based on user input. Set something to 1 thread to "disable" multithreading. It will still set up the threads, but obviously the one thread will handle everything.
I deemed this to be an acceptable compromise, as theres only a slight overhead for 1 threaded "multithreading" vs no multithreading, and is inconsequential for most purposes.
I also capped the matrix size as 5000x5000 for time. My code should work with larger matricies though.

## Setup

The runTest(size, sparsity) function, multiplies two matricies of the same size and sparsity, and prints the results. I included all combinations of tests, and a variety of threadcounts and block sizes (for cache optimization).
limitedTest(size, sparsity) does the same, but with fewer tests. I use this for large matrix sizes, where the full tests would take way too long.
variedSparsityTest(size, sparsity1, sparsity2) multiples two matricies of the same size with the given sparsity. This is used primarily for dense-sparse multiplication.

## Optimizations

### Multithreading

This simply uses multiple threads and segments the matrix, assigning specific blocks to each thread to increase performance.

### SIMD

Uses "#include <immintrin.h>" to allow for SIMD instructions, working with multiple columns of data at a time.

### Cache miss optimization

Uses tiling to increase hit rate. Accesses contiguous emory locations more frequently.

## Results

Check results.md for a full list of results. I will only be showing tables for experiments I will be explicitly mentioning.

### Optimization Experiment

For these 2500x2500 experiments of different sparsities, adding multithreading always saw a significant performance increase.
Using 8 threads as opposed to 1 saw a speed increase of 6-7x, which is around what would be expected. This is not a flat 8x increase for 8x the threads, as each individual thread can't function at 100% efficency, and there is some overhead when working with threads.
The largest performance increase came from all options on, using 8 threads and the largest block size for cache optimization. This makes the most sense, as more optimizations should lead to better performace.

Multithreading provided the most standalone benefit, followed by SIMD and then cache optimization with the largest block size.
All combined, these provided a 25x increase to performance.
There is no significant benefit for the different sparsities.

When comparing the 2500x2500 and 500x500 speeds, we get some interesting results.

For the smaller size, single threaded cache optimization actually causes a slowdown. This is likely due to cache misses being a less significant issue when less memory is used. 
There are simply less disconnected cache segments, so the optimization does less. The overhead caused is so significant that the benefit for the smaller size does not overcome the overhead.

The table below gives the methods performance benefit over the native implementation, as a percentage.

![500x500 vs 2500x2500 matrix multiplication tests](https://i.gyazo.com/efe1d4505da587584bb5e5cabcbe4533.png)


#### Size: 2500x2500 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 147548128335 |
| Threaded (1 thread)                  | 142350196352 |
| Threaded (8 threads)                 | 23369633423 |
| SIMD (1 thread)                      | 49148615887 |
| SIMD (8 threads)                     | 7009353772 |
| Cache (block 4, 1 thread)            | 96056382602 |
| Cache (block 4, 8 threads)           | 16802989603 |
| Cache (block 256, 1 thread)          | 64310123719 |
| Cache (block 256, 8 threads)         | 11379351920 |
| All opt (block 4, 1 thread)          | 54285144311 |
| All opt (block 4, 8 threads)         | 8307885554 |
| All opt (block 256, 1 thread)        | 31986699266 |
| All opt (block 256, 8 threads)       | 5861582814 |

#### Size: 2500x2500 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 150353737805 |
| Threaded (1 thread)                  | 152078556601 |
| Threaded (8 threads)                 | 24410398079 |
| SIMD (1 thread)                      | 59960648990 |
| SIMD (8 threads)                     | 7566740119 |
| Cache (block 4, 1 thread)            | 98261919515 |
| Cache (block 4, 8 threads)           | 16513427910 |
| Cache (block 256, 1 thread)          | 64414986010 |
| Cache (block 256, 8 threads)         | 11103049589 |
| All opt (block 4, 1 thread)          | 55292969172 |
| All opt (block 4, 8 threads)         | 9072665334 |
| All opt (block 256, 1 thread)        | 32057745856 |
| All opt (block 256, 8 threads)       | 6387365324 |



#### Size: 500x500 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 523828478 |
| Threaded (1 thread)                  | 505817276 |
| Threaded (4 threads)                 | 129229407 |
| Threaded (8 threads)                 | 93175751 |
| Threaded (16 threads)                | 55598984 |
| SIMD (1 thread)                      | 193987132 |
| SIMD (4 threads)                     | 51252935 |
| SIMD (8 threads)                     | 39171482 |
| SIMD (16 threads)                    | 22400958 |
| Cache (block 4, 1 thread)            | 706790103 |
| Cache (block 4, 4 threads)           | 253832158 |
| Cache (block 4, 8 threads)           | 153888598 |
| Cache (block 4, 16 threads)          | 83938570 |
| Cache (block 64, 1 thread)           | 495241239 |
| Cache (block 64, 4 threads)          | 124523416 |
| Cache (block 64, 8 threads)          | 105843942 |
| Cache (block 64, 16 threads)         | 59168775 |
| Cache (block 256, 1 thread)          | 508999627 |
| Cache (block 256, 4 threads)         | 121367963 |
| Cache (block 256, 8 threads)         | 112600768 |
| Cache (block 256, 16 threads)        | 56797996 |
| All opt (block 4, 1 thread)          | 381679118 |
| All opt (block 4, 4 threads)         | 130955435 |
| All opt (block 4, 8 threads)         | 74541594 |
| All opt (block 4, 16 threads)        | 46575511 |
| All opt (block 64, 1 thread)         | 255722186 |
| All opt (block 64, 4 threads)        | 62742229 |
| All opt (block 64, 8 threads)        | 36555160 |
| All opt (block 64, 16 threads)       | 29509067 |
| All opt (block 256, 1 thread)        | 246005602 |
| All opt (block 256, 4 threads)       | 76220415 |
| All opt (block 256, 8 threads)       | 48247451 |
| All opt (block 256, 16 threads)      | 28617587 |

#### Size: 500x500 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 505042190 |
| Threaded (1 thread)                  | 501466058 |
| Threaded (4 threads)                 | 180509817 |
| Threaded (8 threads)                 | 111621094 |
| Threaded (16 threads)                | 55750840 |
| SIMD (1 thread)                      | 191899753 |
| SIMD (4 threads)                     | 69307020 |
| SIMD (8 threads)                     | 37053223 |
| SIMD (16 threads)                    | 22288218 |
| Cache (block 4, 1 thread)            | 709223567 |
| Cache (block 4, 4 threads)           | 178460593 |
| Cache (block 4, 8 threads)           | 113807708 |
| Cache (block 4, 16 threads)          | 83264429 |
| Cache (block 64, 1 thread)           | 518566366 |
| Cache (block 64, 4 threads)          | 138735361 |
| Cache (block 64, 8 threads)          | 112598956 |
| Cache (block 64, 16 threads)         | 64295097 |
| Cache (block 256, 1 thread)          | 482468274 |
| Cache (block 256, 4 threads)         | 119637428 |
| Cache (block 256, 8 threads)         | 86882709 |
| Cache (block 256, 16 threads)        | 59331232 |
| All opt (block 4, 1 thread)          | 366291246 |
| All opt (block 4, 4 threads)         | 120316334 |
| All opt (block 4, 8 threads)         | 69980008 |
| All opt (block 4, 16 threads)        | 40981942 |
| All opt (block 64, 1 thread)         | 254413699 |
| All opt (block 64, 4 threads)        | 111477912 |
| All opt (block 64, 8 threads)        | 52476431 |
| All opt (block 64, 16 threads)       | 29522003 |
| All opt (block 256, 1 thread)        | 257563569 |
| All opt (block 256, 4 threads)       | 90579424 |
| All opt (block 256, 8 threads)       | 49402394 |
| All opt (block 256, 16 threads)      | 29395127 |

## Sparse-Sparse, Dense-Dense, Sparse-Dense multiplcation

### Dense-Dense
  Below is a table of 3 experiments with a fully saturated matrix, all 3 with varied size
  Besides the expected slowdown from small size cache optimization, the optimizations all have around the same impact, with a reasonable speed difference between sizes.

  ![Dense-Dense matrix multiplication tests](https://i.gyazo.com/f7c60b57b39c9526aabc48135810c44c.png)

### Sparse-Sparse
  Below is a table of 3 experiments with a sparse matrix, all 3 with varied size. Also included is 3 of the same size matricies with varied low sparsities.

  ![Sparse-Sparse same sparsity matrix multiplication tests](https://i.gyazo.com/e73eea8b348b06f8b76b675281a6359b.png)

  This shows similar results to the Dense-Dense multiplication, except the cache optimization performs significantly worse.
  
  ![Sparse-Sparse same sparsity matrix multiplication tests](https://i.gyazo.com/5354d7c5b438ce4591a32a4e034f3b5a.png)

  As shown previously, this also shows little difference with matrix sparsity.

### Dense-Sparse

The data shows that most matricies perform similary, even with different sparsities.
The different sizes confirm that the impact of cache optimization increases in effect with a larger matrix and with a larger block size.

The tables below has the relative speeds of the given multiplications, relative to a 0.001 sparisty matrix * 0.001 sparsity matrix.
For example, a score of -8% would indicate that the specific multiplication completed 8% slower then the multiplication of 2 matricies with a sparsity of 0.001, for the given size.

![500x500 matrix multiplication tests](https://i.gyazo.com/3382d1b5830409bc93f03ab422690c6c.png)

![1000x1000 matrix multiplication tests](https://i.gyazo.com/1f95608178b70fadd7343b8d4a73ee5e.png)

![1500x1500 matrix multiplication tests](https://i.gyazo.com/9381ef25fe0faee64be9395cbf003ccc.png)

The tables below show relative performance on different sized matricies with the same sparsities.

![0.01 * 1.0 matrix multiplication tests](https://i.gyazo.com/55390361fd9397b24e15737dbf68d966.png)

![0.05 * 0.5 matrix multiplication tests](https://i.gyazo.com/ca5c3e194768eca131402818cf607c2d.png)

![0.1 * 0.9 matrix multiplication tests](https://i.gyazo.com/9ed4cf23a289f21422000e1c56afa3a4.png)


The tables below show performance in nanoseconds

#### Size: 500x500 ------ Sparsity: 0.01 * 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 510291382 |
| Threaded (1 thread)                  | 507514378 |
| Threaded (4 threads)                 | 128450373 |
| Threaded (8 threads)                 | 107611794 |
| Threaded (16 threads)                | 56122740 |
| SIMD (1 thread)                      | 194175094 |
| SIMD (4 threads)                     | 54980241 |
| SIMD (8 threads)                     | 43238252 |
| SIMD (16 threads)                    | 23805092 |
| Cache (block 4, 1 thread)            | 767192434 |
| Cache (block 4, 4 threads)           | 225399613 |
| Cache (block 4, 8 threads)           | 152431803 |
| Cache (block 4, 16 threads)          | 87593848 |
| Cache (block 64, 1 thread)           | 511722287 |
| Cache (block 64, 4 threads)          | 127217999 |
| Cache (block 64, 8 threads)          | 117533188 |
| Cache (block 64, 16 threads)         | 61834294 |
| Cache (block 256, 1 thread)          | 481827152 |
| Cache (block 256, 4 threads)         | 120851199 |
| Cache (block 256, 8 threads)         | 106506250 |
| Cache (block 256, 16 threads)        | 56414089 |
| All opt (block 4, 1 thread)          | 385546702 |
| All opt (block 4, 4 threads)         | 107137311 |
| All opt (block 4, 8 threads)         | 66704227 |
| All opt (block 4, 16 threads)        | 41653554 |
| All opt (block 64, 1 thread)         | 249576781 |
| All opt (block 64, 4 threads)        | 75922039 |
| All opt (block 64, 8 threads)        | 56610238 |
| All opt (block 64, 16 threads)       | 29914362 |
| All opt (block 256, 1 thread)        | 244512529 |
| All opt (block 256, 4 threads)       | 69506122 |
| All opt (block 256, 8 threads)       | 51188062 |
| All opt (block 256, 16 threads)      | 28295902 |

#### Size: 500x500 ------ Sparsity: 0.05 * 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 506746047 |
| Threaded (1 thread)                  | 507850244 |
| Threaded (4 threads)                 | 158860937 |
| Threaded (8 threads)                 | 96958011 |
| Threaded (16 threads)                | 54692000 |
| SIMD (1 thread)                      | 193369977 |
| SIMD (4 threads)                     | 65291169 |
| SIMD (8 threads)                     | 42214147 |
| SIMD (16 threads)                    | 22308894 |
| Cache (block 4, 1 thread)            | 746039585 |
| Cache (block 4, 4 threads)           | 221868304 |
| Cache (block 4, 8 threads)           | 162883007 |
| Cache (block 4, 16 threads)          | 82451560 |
| Cache (block 64, 1 thread)           | 502277719 |
| Cache (block 64, 4 threads)          | 151275661 |
| Cache (block 64, 8 threads)          | 108223022 |
| Cache (block 64, 16 threads)         | 58413415 |
| Cache (block 256, 1 thread)          | 487035660 |
| Cache (block 256, 4 threads)         | 122562696 |
| Cache (block 256, 8 threads)         | 111762856 |
| Cache (block 256, 16 threads)        | 60463160 |
| All opt (block 4, 1 thread)          | 387971655 |
| All opt (block 4, 4 threads)         | 96119228 |
| All opt (block 4, 8 threads)         | 77038653 |
| All opt (block 4, 16 threads)        | 40945795 |
| All opt (block 64, 1 thread)         | 250351148 |
| All opt (block 64, 4 threads)        | 63035743 |
| All opt (block 64, 8 threads)        | 47351109 |
| All opt (block 64, 16 threads)       | 29486598 |
| All opt (block 256, 1 thread)        | 244351701 |
| All opt (block 256, 4 threads)       | 61403136 |
| All opt (block 256, 8 threads)       | 55398369 |
| All opt (block 256, 16 threads)      | 28373300 |

#### Size: 500x500 ------ Sparsity: 0.1 * 0.9
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 512465271 |
| Threaded (1 thread)                  | 508792636 |
| Threaded (4 threads)                 | 128080050 |
| Threaded (8 threads)                 | 91210118 |
| Threaded (16 threads)                | 60884276 |
| SIMD (1 thread)                      | 196150123 |
| SIMD (4 threads)                     | 57458521 |
| SIMD (8 threads)                     | 39170314 |
| SIMD (16 threads)                    | 23066208 |
| Cache (block 4, 1 thread)            | 740085113 |
| Cache (block 4, 4 threads)           | 325233779 |
| Cache (block 4, 8 threads)           | 138725225 |
| Cache (block 4, 16 threads)          | 84736806 |
| Cache (block 64, 1 thread)           | 508853405 |
| Cache (block 64, 4 threads)          | 183019923 |
| Cache (block 64, 8 threads)          | 116451810 |
| Cache (block 64, 16 threads)         | 60953845 |
| Cache (block 256, 1 thread)          | 498165294 |
| Cache (block 256, 4 threads)         | 122576811 |
| Cache (block 256, 8 threads)         | 113316264 |
| Cache (block 256, 16 threads)        | 60069796 |
| All opt (block 4, 1 thread)          | 373755816 |
| All opt (block 4, 4 threads)         | 106053807 |
| All opt (block 4, 8 threads)         | 72251455 |
| All opt (block 4, 16 threads)        | 44446901 |
| All opt (block 64, 1 thread)         | 258893441 |
| All opt (block 64, 4 threads)        | 78453870 |
| All opt (block 64, 8 threads)        | 53698181 |
| All opt (block 64, 16 threads)       | 30473142 |
| All opt (block 256, 1 thread)        | 247766984 |
| All opt (block 256, 4 threads)       | 71483842 |
| All opt (block 256, 8 threads)       | 46528267 |
| All opt (block 256, 16 threads)      | 30343205 |

#### Size: 1000x1000 ------ Sparsity: 0.01 * 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4804470644 |
| Threaded (1 thread)                  | 5407660103 |
| Threaded (4 threads)                 | 1510782777 |
| Threaded (8 threads)                 | 810896310 |
| Threaded (16 threads)                | 578819936 |
| SIMD (1 thread)                      | 2245150627 |
| SIMD (4 threads)                     | 607322222 |
| SIMD (8 threads)                     | 348680807 |
| SIMD (16 threads)                    | 170432599 |
| Cache (block 4, 1 thread)            | 6214875405 |
| Cache (block 4, 4 threads)           | 1885197035 |
| Cache (block 4, 8 threads)           | 1157010596 |
| Cache (block 4, 16 threads)          | 668006770 |
| Cache (block 64, 1 thread)           | 4184108338 |
| Cache (block 64, 4 threads)          | 1335149015 |
| Cache (block 64, 8 threads)          | 782307817 |
| Cache (block 64, 16 threads)         | 489619637 |
| Cache (block 256, 1 thread)          | 4025057428 |
| Cache (block 256, 4 threads)         | 1368679339 |
| Cache (block 256, 8 threads)         | 791928418 |
| Cache (block 256, 16 threads)        | 449911325 |
| All opt (block 4, 1 thread)          | 3352662388 |
| All opt (block 4, 4 threads)         | 1015530616 |
| All opt (block 4, 8 threads)         | 597456570 |
| All opt (block 4, 16 threads)        | 328388923 |
| All opt (block 64, 1 thread)         | 2182555555 |
| All opt (block 64, 4 threads)        | 579760475 |
| All opt (block 64, 8 threads)        | 370234669 |
| All opt (block 64, 16 threads)       | 221399208 |
| All opt (block 256, 1 thread)        | 2051076565 |
| All opt (block 256, 4 threads)       | 619964388 |
| All opt (block 256, 8 threads)       | 444232525 |
| All opt (block 256, 16 threads)      | 228851196 |

#### Size: 1000x1000 ------ Sparsity: 0.05 * 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 5862695417 |
| Threaded (1 thread)                  | 5254225206 |
| Threaded (4 threads)                 | 1431395354 |
| Threaded (8 threads)                 | 875995803 |
| Threaded (16 threads)                | 445218841 |
| SIMD (1 thread)                      | 1905360253 |
| SIMD (4 threads)                     | 571188932 |
| SIMD (8 threads)                     | 350794729 |
| SIMD (16 threads)                    | 173640438 |
| Cache (block 4, 1 thread)            | 6044182440 |
| Cache (block 4, 4 threads)           | 1924838328 |
| Cache (block 4, 8 threads)           | 1065262215 |
| Cache (block 4, 16 threads)          | 685771214 |
| Cache (block 64, 1 thread)           | 4217175073 |
| Cache (block 64, 4 threads)          | 1406945468 |
| Cache (block 64, 8 threads)          | 860680079 |
| Cache (block 64, 16 threads)         | 562301589 |
| Cache (block 256, 1 thread)          | 3947029123 |
| Cache (block 256, 4 threads)         | 1286515490 |
| Cache (block 256, 8 threads)         | 771962863 |
| Cache (block 256, 16 threads)        | 476675744 |
| All opt (block 4, 1 thread)          | 3236429765 |
| All opt (block 4, 4 threads)         | 994574842 |
| All opt (block 4, 8 threads)         | 583708182 |
| All opt (block 4, 16 threads)        | 319374645 |
| All opt (block 64, 1 thread)         | 2019281689 |
| All opt (block 64, 4 threads)        | 684298925 |
| All opt (block 64, 8 threads)        | 371549044 |
| All opt (block 64, 16 threads)       | 214926301 |
| All opt (block 256, 1 thread)        | 2033512322 |
| All opt (block 256, 4 threads)       | 659379188 |
| All opt (block 256, 8 threads)       | 394073572 |
| All opt (block 256, 16 threads)      | 269298448 |

#### Size: 1000x1000 ------ Sparsity: 0.1 * 0.9
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 5390382645 |
| Threaded (1 thread)                  | 5279845862 |
| Threaded (4 threads)                 | 1433596866 |
| Threaded (8 threads)                 | 799242776 |
| Threaded (16 threads)                | 469100224 |
| SIMD (1 thread)                      | 1905768066 |
| SIMD (4 threads)                     | 491809811 |
| SIMD (8 threads)                     | 291214861 |
| SIMD (16 threads)                    | 176048856 |
| Cache (block 4, 1 thread)            | 6039881136 |
| Cache (block 4, 4 threads)           | 1920490104 |
| Cache (block 4, 8 threads)           | 1101178430 |
| Cache (block 4, 16 threads)          | 667396132 |
| Cache (block 64, 1 thread)           | 4239384076 |
| Cache (block 64, 4 threads)          | 1515262840 |
| Cache (block 64, 8 threads)          | 891060505 |
| Cache (block 64, 16 threads)         | 475715786 |
| Cache (block 256, 1 thread)          | 3979895062 |
| Cache (block 256, 4 threads)         | 1092594617 |
| Cache (block 256, 8 threads)         | 779035153 |
| Cache (block 256, 16 threads)        | 458668631 |
| All opt (block 4, 1 thread)          | 3397355002 |
| All opt (block 4, 4 threads)         | 1051620743 |
| All opt (block 4, 8 threads)         | 607813984 |
| All opt (block 4, 16 threads)        | 363391509 |
| All opt (block 64, 1 thread)         | 2037288081 |
| All opt (block 64, 4 threads)        | 725464269 |
| All opt (block 64, 8 threads)        | 396853521 |
| All opt (block 64, 16 threads)       | 224904087 |
| All opt (block 256, 1 thread)        | 1983673186 |
| All opt (block 256, 4 threads)       | 645825231 |
| All opt (block 256, 8 threads)       | 372424338 |
| All opt (block 256, 16 threads)      | 222877282 |

#### Size: 1500x1500 ------ Sparsity: 0.01 * 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 18495786791 |
| Threaded (1 thread)                  | 18367048223 |
| Threaded (4 threads)                 | 5807300397 |
| Threaded (8 threads)                 | 3263464347 |
| Threaded (16 threads)                | 2046306207 |
| SIMD (1 thread)                      | 8212025258 |
| SIMD (4 threads)                     | 2228506291 |
| SIMD (8 threads)                     | 1145239458 |
| SIMD (16 threads)                    | 619714058 |
| Cache (block 4, 1 thread)            | 20745559503 |
| Cache (block 4, 4 threads)           | 7219968215 |
| Cache (block 4, 8 threads)           | 3769635108 |
| Cache (block 4, 16 threads)          | 2296530876 |
| Cache (block 64, 1 thread)           | 14405881313 |
| Cache (block 64, 4 threads)          | 4561980147 |
| Cache (block 64, 8 threads)          | 2598815333 |
| Cache (block 64, 16 threads)         | 1651712782 |
| Cache (block 256, 1 thread)          | 13769923666 |
| Cache (block 256, 4 threads)         | 4539039372 |
| Cache (block 256, 8 threads)         | 2486018356 |
| Cache (block 256, 16 threads)        | 1543816460 |
| All opt (block 4, 1 thread)          | 11176433988 |
| All opt (block 4, 4 threads)         | 3365998742 |
| All opt (block 4, 8 threads)         | 1888082349 |
| All opt (block 4, 16 threads)        | 1217520609 |
| All opt (block 64, 1 thread)         | 7054601166 |
| All opt (block 64, 4 threads)        | 2285489442 |
| All opt (block 64, 8 threads)        | 1297488293 |
| All opt (block 64, 16 threads)       | 781617956 |
| All opt (block 256, 1 thread)        | 6752461247 |
| All opt (block 256, 4 threads)       | 2151296071 |
| All opt (block 256, 8 threads)       | 1224088707 |
| All opt (block 256, 16 threads)      | 757968919 |

#### Size: 1500x1500 ------ Sparsity: 0.05 * 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 18928590175 |
| Threaded (1 thread)                  | 19468015887 |
| Threaded (4 threads)                 | 6405157373 |
| Threaded (8 threads)                 | 3476866671 |
| Threaded (16 threads)                | 2299287851 |
| SIMD (1 thread)                      | 8281822128 |
| SIMD (4 threads)                     | 2095830283 |
| SIMD (8 threads)                     | 1208659029 |
| SIMD (16 threads)                    | 652193811 |
| Cache (block 4, 1 thread)            | 20633419426 |
| Cache (block 4, 4 threads)           | 6352273377 |
| Cache (block 4, 8 threads)           | 3562649136 |
| Cache (block 4, 16 threads)          | 2287400486 |
| Cache (block 64, 1 thread)           | 14302401554 |
| Cache (block 64, 4 threads)          | 4519940189 |
| Cache (block 64, 8 threads)          | 2615437065 |
| Cache (block 64, 16 threads)         | 1587474982 |
| Cache (block 256, 1 thread)          | 13244558633 |
| Cache (block 256, 4 threads)         | 4345225341 |
| Cache (block 256, 8 threads)         | 2376711868 |
| Cache (block 256, 16 threads)        | 1557692651 |
| All opt (block 4, 1 thread)          | 10949901278 |
| All opt (block 4, 4 threads)         | 3251377172 |
| All opt (block 4, 8 threads)         | 1937582946 |
| All opt (block 4, 16 threads)        | 1180175586 |
| All opt (block 64, 1 thread)         | 6933666248 |
| All opt (block 64, 4 threads)        | 1950687639 |
| All opt (block 64, 8 threads)        | 1354467296 |
| All opt (block 64, 16 threads)       | 779833226 |
| All opt (block 256, 1 thread)        | 6655061360 |
| All opt (block 256, 4 threads)       | 2227817533 |
| All opt (block 256, 8 threads)       | 1177197706 |
| All opt (block 256, 16 threads)      | 753398113 |

#### Size: 1500x1500 ------ Sparsity: 0.1 * 0.9
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 18986818012 |
| Threaded (1 thread)                  | 19148445615 |
| Threaded (4 threads)                 | 6276802101 |
| Threaded (8 threads)                 | 3487397307 |
| Threaded (16 threads)                | 2307171484 |
| SIMD (1 thread)                      | 7923371695 |
| SIMD (4 threads)                     | 1945812620 |
| SIMD (8 threads)                     | 1113450056 |
| SIMD (16 threads)                    | 663052118 |
| Cache (block 4, 1 thread)            | 20467975511 |
| Cache (block 4, 4 threads)           | 6393675714 |
| Cache (block 4, 8 threads)           | 3652859486 |
| Cache (block 4, 16 threads)          | 2307181277 |
| Cache (block 64, 1 thread)           | 14217390538 |
| Cache (block 64, 4 threads)          | 4720151978 |
| Cache (block 64, 8 threads)          | 2456678720 |
| Cache (block 64, 16 threads)         | 1579344004 |
| Cache (block 256, 1 thread)          | 13398164229 |
| Cache (block 256, 4 threads)         | 4461412072 |
| Cache (block 256, 8 threads)         | 2336726331 |
| Cache (block 256, 16 threads)        | 1512383087 |
| All opt (block 4, 1 thread)          | 10897006940 |
| All opt (block 4, 4 threads)         | 3122182006 |
| All opt (block 4, 8 threads)         | 1795343956 |
| All opt (block 4, 16 threads)        | 1137872091 |
| All opt (block 64, 1 thread)         | 6945274988 |
| All opt (block 64, 4 threads)        | 2149418412 |
| All opt (block 64, 8 threads)        | 1296821367 |
| All opt (block 64, 16 threads)       | 795431476 |
| All opt (block 256, 1 thread)        | 6671144656 |
| All opt (block 256, 4 threads)       | 2313380572 |
| All opt (block 256, 8 threads)       | 1410385086 |
| All opt (block 256, 16 threads)      | 758531145 |

## Conclusion

This data shows some interesting results. The first is with multithreading. There is a falloff with threadcount and time savings. It might be bettter to run 2 different multiplications with 8 threads each, rather than 1 multiplication with 16 threads, as the performance benefit from the last 8 is not as significant as the adding the first 7. 

Secondly, and most importantly comes with cache optimization. For smaller matricies, attempting this, especially with an unoptimal block size, can actually lead to a performance decrease. The swap to performance benefit for the 4 byte block occured between 1000-size matrix and a 2500-size matrix, while a 256 byte block already shows performance benefits on a 1000-size matrix, instead showing performance loss ona 100-size matrix.

Just because an optimization exists, does not mean it will necessarily be beneficial for every situation.