# Project 2

## Implementation

A "dense" matrix was implemented as a 2d vector.
A "sparse" matrix was implemented in CSR form.
While there is no explicit sparsity tied to either of these forms, and they should work for any size and sparsity.
This was designed intentionally like this in order to perform analysis on different matrix data formats.

I implemented a native implementation, multithreaded, cache miss optimization via tiling, and SIMD via intrinsic AVX instructions. 
Each implementation includes a CSR * CSR, 2d * 2d, and CSR * 2D.
Like the different matrix formats, this was done intentionally to analyze the benefits of different implementations.

## Results

Please see results.csv for a full list of all experiments run. I will be included more limited and tailored datasets filtered for more relevant data for each analysis.

### Optimization Experiment

Looking at all 500x500, 0.001 sparity multiplactions:

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |      0.001 | Dense           | Dense           | Unoptimized    |         1 |           4 |    963.327  |           0       |
|    500 |      0.001 | Dense           | Dense           | Multithreaded  |         1 |           4 |    936.211  |           2.81483 |
|    500 |      0.001 | Dense           | Dense           | MT with SIMD   |         1 |           4 |    565.805  |          41.2655  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt      |         1 |           4 |   1403.16   |         -45.6577  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt SIMD |         1 |           4 |   1511.08   |         -56.8605  |
|    500 |      0.001 | Dense           | Dense           | Unoptimized    |         1 |         256 |    937.256  |           2.70635 |
|    500 |      0.001 | Dense           | Dense           | Multithreaded  |         1 |         256 |   1016.56   |          -5.52595 |
|    500 |      0.001 | Dense           | Dense           | MT with SIMD   |         1 |         256 |    578.233  |          39.9754  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt      |         1 |         256 |   1124.36   |         -16.7163  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt SIMD |         1 |         256 |    183.18   |          80.9847  |
|    500 |      0.001 | Dense           | Dense           | Unoptimized    |         8 |           4 |    918.157  |           4.68896 |
|    500 |      0.001 | Dense           | Dense           | Multithreaded  |         8 |           4 |    189.399  |          80.3391  |
|    500 |      0.001 | Dense           | Dense           | MT with SIMD   |         8 |           4 |    107.839  |          88.8056  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt      |         8 |           4 |    266.74   |          72.3105  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt SIMD |         8 |           4 |    297.522  |          69.1152  |
|    500 |      0.001 | Dense           | Dense           | Unoptimized    |         8 |         256 |    932.651  |           3.18438 |
|    500 |      0.001 | Dense           | Dense           | Multithreaded  |         8 |         256 |    192.376  |          80.03    |
|    500 |      0.001 | Dense           | Dense           | MT with SIMD   |         8 |         256 |    106.014  |          88.995   |
|    500 |      0.001 | Dense           | Dense           | Cache Opt      |         8 |         256 |    223.317  |          76.8182  |
|    500 |      0.001 | Dense           | Dense           | Cache Opt SIMD |         8 |         256 |     36.2121 |          96.2409  |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |      0.001 | Dense           | Sparse          | Unoptimized    |         1 |           4 |    2.87437  |           0       |
|    500 |      0.001 | Dense           | Sparse          | Multithreaded  |         1 |           4 |    2.08524  |          27.454   |
|    500 |      0.001 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    0.484899 |          83.1303  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt      |         1 |           4 |    3.42436  |         -19.1343  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 |  109.947    |       -3725.08    |
|    500 |      0.001 | Dense           | Sparse          | Unoptimized    |         1 |         256 |    2.80206  |           2.51568 |
|    500 |      0.001 | Dense           | Sparse          | Multithreaded  |         1 |         256 |    2.50433  |          12.8738  |
|    500 |      0.001 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    0.435958 |          84.8329  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt      |         1 |         256 |    3.23637  |         -12.5941  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 |  110.285    |       -3736.84    |
|    500 |      0.001 | Dense           | Sparse          | Unoptimized    |         8 |           4 |    2.81563  |           2.04358 |
|    500 |      0.001 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    0.886922 |          69.1438  |
|    500 |      0.001 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |    0.593693 |          79.3453  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    1.46195  |          49.1384  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 |   26.7319   |        -830.009   |
|    500 |      0.001 | Dense           | Sparse          | Unoptimized    |         8 |         256 |    2.90991  |          -1.23644 |
|    500 |      0.001 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    1.14009  |          60.336   |
|    500 |      0.001 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |    0.296185 |          89.6957  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    1.36992  |          52.3402  |
|    500 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 |   34.5307   |       -1101.33    |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    0.04845  |          0        |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    0.24772  |       -411.29     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    0.22226  |       -358.741    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    0.188079 |       -288.192    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    0.179746 |       -270.993    |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    0.049373 |         -1.90506  |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    0.180989 |       -273.558    |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    0.151975 |       -213.674    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    0.219732 |       -353.523    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    0.155341 |       -220.621    |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    0.048802 |         -0.726522 |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |    0.626544 |      -1193.18     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |    0.760004 |      -1468.64     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |    0.548598 |      -1032.3      |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |    0.656801 |      -1255.63     |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    0.052168 |         -7.67389  |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |    0.661278 |      -1264.87     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |    0.969767 |      -1901.58     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |    0.573485 |      -1083.66     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |    0.702486 |      -1349.92     |

Looking at this gets us some interesting results. Firstly, Dense * Dense form. For the smaller tile size, for anything cache optimized, there is actually a performance decrease. 
This is likely due to the fact that for these smaller operations, cache optimization doesn't do much. There are few blocks of cache, and a high likelyhood that they are already aligned. So the benefit does not surpass the overhead.

When looking at Dense * Sparse, we see a similar performance hit from cache optimization. More notably, we see a significant performance decrease from SIMD instructions. This is likely because the values are no longer nicely aligned like they are in Dense matricies.

Finally, for Sparse * Sparse, we see something even more interesting: the unoptimized is the fastest. This is likely because it is already so fast that the overhead from all other optimizations is significantly greater then the unoptimized completion time.

Now lets look at 2500 * 2500, with 0.01 Sparsity:

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |       0.01 | Dense           | Dense           | Unoptimized    |         1 |           4 |   207678    |           0       |
|   2500 |       0.01 | Dense           | Dense           | Multithreaded  |         1 |           4 |   209276    |          -0.76946 |
|   2500 |       0.01 | Dense           | Dense           | MT with SIMD   |         1 |           4 |   126934    |          38.8794  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt      |         1 |           4 |   187125    |           9.89657 |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt SIMD |         1 |           4 |   198614    |           4.36445 |
|   2500 |       0.01 | Dense           | Dense           | Unoptimized    |         1 |         256 |   214596    |          -3.33112 |
|   2500 |       0.01 | Dense           | Dense           | Multithreaded  |         1 |         256 |   212680    |          -2.40854 |
|   2500 |       0.01 | Dense           | Dense           | MT with SIMD   |         1 |         256 |   124484    |          40.0591  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt      |         1 |         256 |   148857    |          28.3232  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt SIMD |         1 |         256 |    22709    |          89.0653  |
|   2500 |       0.01 | Dense           | Dense           | Unoptimized    |         8 |           4 |   213843    |          -2.96854 |
|   2500 |       0.01 | Dense           | Dense           | Multithreaded  |         8 |           4 |    38527.1  |          81.4486  |
|   2500 |       0.01 | Dense           | Dense           | MT with SIMD   |         8 |           4 |    20599    |          90.0813  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt      |         8 |           4 |    31502.8  |          84.8309  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt SIMD |         8 |           4 |    33875.6  |          83.6884  |
|   2500 |       0.01 | Dense           | Dense           | Unoptimized    |         8 |         256 |   213948    |          -3.0191  |
|   2500 |       0.01 | Dense           | Dense           | Multithreaded  |         8 |         256 |    39688.7  |          80.8893  |
|   2500 |       0.01 | Dense           | Dense           | MT with SIMD   |         8 |         256 |    20886.7  |          89.9427  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt      |         8 |         256 |    26036.3  |          87.4631  |
|   2500 |       0.01 | Dense           | Dense           | Cache Opt SIMD |         8 |         256 |     3964.66 |          98.091   |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |           4 |   1422.05   |          0        |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |           4 |   1517.74   |         -6.72902  |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    266.976  |         81.226    |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |           4 |   1458.33   |         -2.55125  |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 666143      |     -46743.9      |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |         256 |   1451.46   |         -2.06814  |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |         256 |   1616.31   |        -13.6606   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    280.075  |         80.3048   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |         256 |   1499.02   |         -5.41261  |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 689969      |     -48419.3      |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |           4 |   1470.34   |         -3.3958   |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    300.393  |         78.8761   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |     51.5217 |         96.3769   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    274.401  |         80.7038   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 | 124828      |      -8678.03     |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |         256 |   1427.3    |         -0.369185 |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    297.91   |         79.0507   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |     50.732  |         96.4325   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    271.159  |         80.9318   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 | 139794      |      -9730.46     |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    158.639  |          0        |
|   2500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    165.367  |         -4.24108  |
|   2500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    161.64   |         -1.89172  |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    157.006  |          1.02938  |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    163.009  |         -2.75468  |
|   2500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    151.936  |          4.22532  |
|   2500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    156.926  |          1.07981  |
|   2500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    159.772  |         -0.7142   |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    159.861  |         -0.770302 |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    161.939  |         -2.08019  |
|   2500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    150.075  |          5.39842  |
|   2500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |     36.1755 |         77.1963   |
|   2500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |     42.8051 |         73.0173   |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |     44.0638 |         72.2239   |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |     44.0387 |         72.2397   |
|   2500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    154.154  |          2.82717  |
|   2500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |     38.3157 |         75.8472   |
|   2500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |     39.228  |         75.2722   |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |     36.0262 |         77.2905   |
|   2500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |     43.4173 |         72.6314   |

Now that the matricies are larger, we see more standard results. 
Firstly, in the Dense * Dense, all optimizations benefit, even the 4 bit tile size cache optimizations. This is likely due to the minor benefit provided now exceeds the overhead. 
For Dense * Sparse, SIMD instructions do even worse. Cache optimization seemingly provides little benefit either, likely for similar reasons as SIMD performance being poor. The data is structured in a way that does not benefit from these optimizations.
For Sparse * Sparse, we see very interesting results; all but multithreading seemingly does nothing. Now that the overhead is relatively insignificant, we can see that these optimizations do nothing. Multithreading of course still being beneficial.

### Dense * Dense

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |           4 |    921.707  |          0        |
|    500 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |           4 |    932.916  |         -1.21611  |
|    500 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |           4 |    554.28   |         39.8638   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |           4 |   1348      |        -46.2504   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |           4 |   1545.63   |        -67.6921   |
|    500 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |         256 |    936.906  |         -1.64901  |
|    500 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |         256 |    936.803  |         -1.63783  |
|    500 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |         256 |    578.46   |         37.2404   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |         256 |   1104.14   |        -19.7929   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |         256 |    179.831  |         80.4894   |
|    500 |        0.1 | Dense           | Dense           | Unoptimized    |         8 |           4 |    989.603  |         -7.36633  |
|    500 |        0.1 | Dense           | Dense           | Multithreaded  |         8 |           4 |    202.856  |         77.9913   |
|    500 |        0.1 | Dense           | Dense           | MT with SIMD   |         8 |           4 |    101.606  |         88.9763   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt      |         8 |           4 |    252.444  |         72.6113   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         8 |           4 |    277.481  |         69.8949   |
|    500 |        0.1 | Dense           | Dense           | Unoptimized    |         8 |         256 |    918.803  |          0.315068 |
|    500 |        0.1 | Dense           | Dense           | Multithreaded  |         8 |         256 |    175.258  |         80.9855   |
|    500 |        0.1 | Dense           | Dense           | MT with SIMD   |         8 |         256 |     95.3416 |         89.656    |
|    500 |        0.1 | Dense           | Dense           | Cache Opt      |         8 |         256 |    183.88   |         80.0501   |
|    500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         8 |         256 |     28.9436 |         96.8598   |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   1000 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |           4 |    7766.16  |          0        |
|   1000 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |           4 |    7806.53  |         -0.519819 |
|   1000 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |           4 |    4902.05  |         36.8794   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |           4 |   11048.6   |        -42.2659   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |           4 |   12314.8   |        -58.57     |
|   1000 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |         256 |    7640.23  |          1.62152  |
|   1000 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |         256 |    7746.11  |          0.258171 |
|   1000 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |         256 |    4773.59  |         38.5335   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |         256 |    8803.51  |        -13.3573   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |         256 |    1390.49  |         82.0955   |
|   1000 |        0.1 | Dense           | Dense           | Unoptimized    |         8 |           4 |    7591.99  |          2.24268  |
|   1000 |        0.1 | Dense           | Dense           | Multithreaded  |         8 |           4 |    1362.3   |         82.4585   |
|   1000 |        0.1 | Dense           | Dense           | MT with SIMD   |         8 |           4 |     799.636 |         89.7036   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt      |         8 |           4 |    1919.66  |         75.2817   |
|   1000 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         8 |           4 |    2124.41  |         72.6453   |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |           4 |   210237    |           0       |
|   2500 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |           4 |   214992    |          -2.26173 |
|   2500 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |           4 |   121827    |          42.0525  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |           4 |   184521    |          12.2319  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |           4 |   195994    |           6.77474 |
|   2500 |        0.1 | Dense           | Dense           | Unoptimized    |         1 |         256 |   218916    |          -4.1282  |
|   2500 |        0.1 | Dense           | Dense           | Multithreaded  |         1 |         256 |   222822    |          -5.9861  |
|   2500 |        0.1 | Dense           | Dense           | MT with SIMD   |         1 |         256 |   147094    |          30.0342  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt      |         1 |         256 |   152695    |          27.3701  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         1 |         256 |    23912    |          88.6262  |
|   2500 |        0.1 | Dense           | Dense           | Unoptimized    |         8 |           4 |   236012    |         -12.26    |
|   2500 |        0.1 | Dense           | Dense           | Multithreaded  |         8 |           4 |    40543.4  |          80.7154  |
|   2500 |        0.1 | Dense           | Dense           | MT with SIMD   |         8 |           4 |    21311    |          89.8633  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt      |         8 |           4 |    31862.9  |          84.8443  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         8 |           4 |    34401.1  |          83.637   |
|   2500 |        0.1 | Dense           | Dense           | Unoptimized    |         8 |         256 |   231241    |          -9.99063 |
|   2500 |        0.1 | Dense           | Dense           | Multithreaded  |         8 |         256 |    40496.8  |          80.7375  |
|   2500 |        0.1 | Dense           | Dense           | MT with SIMD   |         8 |         256 |    21692.1  |          89.6821  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt      |         8 |         256 |    26376.8  |          87.4538  |
|   2500 |        0.1 | Dense           | Dense           | Cache Opt SIMD |         8 |         256 |     4126.47 |          98.0372  |

Now inspecting two dense matricies being multiplied:
As expected, for the smallest matrix, cache optimization provides little benefit. As mentioned previously, small datasets are already likely to be grouped nearby, and the moderate overhead far exceeds the benefit.
Oddly, SIMD + Cache optimization provides a significant benefit though, far exceeding each alone. This is likely due to the fact that the SIMD works best with cache aligned a specific way, and I'm assuming that the cache optimization sets up the cache in an SIMD-friendly way.
Cache optimization seems to be more effective the larger the matricies get; likely due to the long-term benefit eventually exceeding the speed decrease. For 4 bit tile sizes, this happens around 2500, and for 256 bit tile sizes, this happens closer to 1250.
Overall, multithreading is a clear winner, with a significant peformance increase no matter the case.
However, SIMD and Cache Optimization can significantly help out, more effectively as sizes get larger and when combined.

### Sparse * Sparse

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    0.04845  |          0        |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    0.24772  |       -411.29     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    0.22226  |       -358.741    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    0.188079 |       -288.192    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    0.179746 |       -270.993    |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    0.049373 |         -1.90506  |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    0.180989 |       -273.558    |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    0.151975 |       -213.674    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    0.219732 |       -353.523    |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    0.155341 |       -220.621    |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    0.048802 |         -0.726522 |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |    0.626544 |      -1193.18     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |    0.760004 |      -1468.64     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |    0.548598 |      -1032.3      |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |    0.656801 |      -1255.63     |
|    500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    0.052168 |         -7.67389  |
|    500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |    0.661278 |      -1264.87     |
|    500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |    0.969767 |      -1901.58     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |    0.573485 |      -1083.66     |
|    500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |    0.702486 |      -1349.92     |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    1.42762  |           0       |
|    500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    1.62976  |         -14.1592  |
|    500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    1.50058  |          -5.1106  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    1.61572  |         -13.1758  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    1.55661  |          -9.03532 |
|    500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    1.47699  |          -3.4582  |
|    500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    1.57959  |         -10.645   |
|    500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    1.46541  |          -2.64706 |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    1.49275  |          -4.56214 |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    1.51327  |          -5.9995  |
|    500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    1.35981  |           4.74986 |
|    500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |    1.04833  |          26.568   |
|    500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |    0.720199 |          49.5525  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |    0.874419 |          38.7499  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |    1.17051  |          18.0097  |
|    500 |       0.01 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    1.36384  |           4.46758 |
|    500 |       0.01 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |    0.836377 |          41.4146  |
|    500 |       0.01 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |    0.873758 |          38.7962  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |    0.864213 |          39.4648  |
|    500 |       0.01 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |    0.856184 |          40.0272  |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |     61.9783 |          0        |
|    500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |     61.0447 |          1.50633  |
|    500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |     59.4754 |          4.03835  |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |     61.4881 |          0.790922 |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |     61.5696 |          0.659424 |
|    500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |     58.5106 |          5.59502  |
|    500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |     60.9965 |          1.5841   |
|    500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |     59.5443 |          3.92718  |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |     60.3153 |          2.6832   |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |     59.882  |          3.38231  |
|    500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |     59.225  |          4.44236  |
|    500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |     13.016  |         78.9991   |
|    500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |     13.502  |         78.215    |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |     13.6069 |         78.0457   |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |     13.2003 |         78.7017   |
|    500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |     59.1737 |          4.52513  |
|    500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |     12.6858 |         79.5319   |
|    500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |     12.2859 |         80.1771   |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |     11.87   |         80.8481   |
|    500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |     13.9914 |         77.4253   |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   1000 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    0.251571 |           0       |
|   1000 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    0.389079 |         -54.6597  |
|   1000 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    0.345056 |         -37.1605  |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    0.311834 |         -23.9547  |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    0.295534 |         -17.4754  |
|   1000 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    0.1919   |          23.7193  |
|   1000 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    0.347922 |         -38.2997  |
|   1000 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    0.328686 |         -30.6534  |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    0.297407 |         -18.2199  |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    0.299862 |         -19.1958  |
|   1000 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    0.228568 |           9.14374 |
|   1000 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |    1.0249   |        -307.4     |
|   1000 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |    0.948969 |        -277.217   |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |    0.91274  |        -262.816   |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |    0.604382 |        -140.243   |
|   1000 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    0.209232 |          16.8298  |
|   1000 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |    0.613269 |        -143.776   |
|   1000 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |    0.905033 |        -259.753   |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |    0.856885 |        -240.614   |
|   1000 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |    0.716532 |        -184.823   |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |     1.94135 |           0       |
|   2500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |     2.20517 |         -13.5895  |
|   2500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |     2.33231 |         -20.1386  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |     2.11645 |          -9.0195  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |     2.11294 |          -8.83869 |
|   2500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |     2.00085 |          -3.06488 |
|   2500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |     2.22496 |         -14.6089  |
|   2500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |     2.05685 |          -5.94947 |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |     2.14271 |         -10.3722  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |     2.11224 |          -8.80264 |
|   2500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |     1.9052  |           1.86211 |
|   2500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |     1.33497 |          31.235   |
|   2500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |     1.09326 |          43.6856  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |     1.00466 |          48.2494  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |     1.02153 |          47.3804  |
|   2500 |      0.001 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |     1.8961  |           2.33085 |
|   2500 |      0.001 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |     1.07602 |          44.5736  |
|   2500 |      0.001 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |     1.16912 |          39.778   |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |     1.04412 |          46.2168  |
|   2500 |      0.001 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |     1.28967 |          33.5684  |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         1 |           4 |    5300.23  |         0         |
|   2500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         1 |           4 |    5298.45  |         0.0335834 |
|   2500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         1 |           4 |    5261.73  |         0.726384  |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         1 |           4 |    5316.71  |        -0.31093   |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         1 |           4 |    5548.84  |        -4.69055   |
|   2500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         1 |         256 |    5441.01  |        -2.65611   |
|   2500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         1 |         256 |    5494.24  |        -3.66041   |
|   2500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         1 |         256 |    5359.38  |        -1.11599   |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         1 |         256 |    5431.85  |        -2.48329   |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         1 |         256 |    5794.09  |        -9.31771   |
|   2500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         8 |           4 |    5650.23  |        -6.60349   |
|   2500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         8 |           4 |     916.193 |        82.7141    |
|   2500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         8 |           4 |     935.361 |        82.3524    |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         8 |           4 |     954.804 |        81.9856    |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         8 |           4 |     933.285 |        82.3916    |
|   2500 |        0.1 | Sparse          | Sparse          | Unoptimized    |         8 |         256 |    5759.98  |        -8.67415   |
|   2500 |        0.1 | Sparse          | Sparse          | Multithreaded  |         8 |         256 |     994.869 |        81.2297    |
|   2500 |        0.1 | Sparse          | Sparse          | MT with SIMD   |         8 |         256 |     931.114 |        82.4326    |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt      |         8 |         256 |     928.166 |        82.4882    |
|   2500 |        0.1 | Sparse          | Sparse          | Cache Opt SIMD |         8 |         256 |     954.486 |        81.9916    |

Results become very intersting for the CSR form matricies.
Overall time compared to Dense * Dense is typically better, however depending on the exact specifications, the effect of optimizations drastically change.
One note is that multithreading is almost always beneficial. The only exception is in extremely small and extremely sparse matricies. My extreme example only need ~25 multiplications, and doing these is much easier then setting up 8 threads to handle 3 operations each.

For all these CSR multiplications though, all other optimizations provide at the best, no benefit. Often times in fact reducing performance. This is interesting, and I would like to see how this performs as matrix size/density increases even further. I believe at some point the speedups from optimizations in the Dense * Dense multiplications would surpass the speedup from CSR form multiplications, but this would take too long to test with my machine.

One note is that the larger and less dense things become, the better the optimized forms perform proportionally to the unoptimized case. Likely due to overhead mattering less.

### Dense * Sparse

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   1000 |      0.001 | Dense           | Sparse          | Unoptimized    |         1 |           4 |   18.7781   |          0        |
|   1000 |      0.001 | Dense           | Sparse          | Multithreaded  |         1 |           4 |   12.1856   |         35.1074   |
|   1000 |      0.001 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    2.04382  |         89.1159   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt      |         1 |           4 |   23.4675   |        -24.9727   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 1688.99     |      -8894.47     |
|   1000 |      0.001 | Dense           | Sparse          | Unoptimized    |         1 |         256 |   18.703    |          0.399934 |
|   1000 |      0.001 | Dense           | Sparse          | Multithreaded  |         1 |         256 |   12.2545   |         34.7405   |
|   1000 |      0.001 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    2.20158  |         88.2758   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt      |         1 |         256 |   20.0097   |         -6.5587   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 1674.58     |      -8817.73     |
|   1000 |      0.001 | Dense           | Sparse          | Unoptimized    |         8 |           4 |   19.434    |         -3.4929   |
|   1000 |      0.001 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    3.87055  |         79.388    |
|   1000 |      0.001 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |    0.829444 |         95.5829   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    4.33887  |         76.894    |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 |  353.684    |      -1783.49     |
|   1000 |      0.001 | Dense           | Sparse          | Unoptimized    |         8 |         256 |   19.7441   |         -5.14429  |
|   1000 |      0.001 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    3.26073  |         82.6355   |
|   1000 |      0.001 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |    0.750556 |         96.003    |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    4.65399  |         75.2159   |
|   1000 |      0.001 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 |  441.199    |      -2249.54     |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   1000 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |           4 |    97.5508  |          0        |
|   1000 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |           4 |    97.7275  |         -0.181136 |
|   1000 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    17.058   |         82.5137   |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |           4 |   106.449   |         -9.12161  |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 16830.5     |     -17153.1      |
|   1000 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |         256 |    99.7548  |         -2.25934  |
|   1000 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |         256 |   101.582   |         -4.13241  |
|   1000 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    17.2409  |         82.3262   |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |         256 |    99.9854  |         -2.49573  |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 16873.3     |     -17196.9      |
|   1000 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |           4 |    97.6641  |         -0.116145 |
|   1000 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    20.2442  |         79.2475   |
|   1000 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |     4.1544  |         95.7413   |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    19.6254  |         79.8819   |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 |  3472.5     |      -3459.68     |
|   1000 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |         256 |    98.8771  |         -1.3596   |
|   1000 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    18.4828  |         81.0532   |
|   1000 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |     2.84459 |         97.084    |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    16.3119  |         83.2786   |
|   1000 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 |  5341.68    |      -5375.79     |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   1000 |        0.1 | Dense           | Sparse          | Unoptimized    |         1 |           4 |    875.311  |          0        |
|   1000 |        0.1 | Dense           | Sparse          | Multithreaded  |         1 |           4 |   1055.38   |        -20.572    |
|   1000 |        0.1 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    169.816  |         80.5994   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt      |         1 |           4 |    850.69   |          2.81283  |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 168035      |     -19097.2      |
|   1000 |        0.1 | Dense           | Sparse          | Unoptimized    |         1 |         256 |    870.975  |          0.495367 |
|   1000 |        0.1 | Dense           | Sparse          | Multithreaded  |         1 |         256 |    965.524  |        -10.3064   |
|   1000 |        0.1 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    167.096  |         80.9101   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt      |         1 |         256 |    872.227  |          0.352332 |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 167690      |     -19057.8      |
|   1000 |        0.1 | Dense           | Sparse          | Unoptimized    |         8 |           4 |    939.111  |         -7.28884  |
|   1000 |        0.1 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    208.609  |         76.1674   |
|   1000 |        0.1 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |     36.706  |         95.8065   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    157.242  |         82.0359   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 |  39562.7    |      -4419.84     |
|   1000 |        0.1 | Dense           | Sparse          | Unoptimized    |         8 |         256 |    880.559  |         -0.599558 |
|   1000 |        0.1 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    156.007  |         82.177    |
|   1000 |        0.1 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |     33.0944 |         96.2191   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    163.446  |         81.3271   |
|   1000 |        0.1 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 |  41495.1    |      -4640.61     |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|    500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |           4 |   14.4155   |           0       |
|    500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |           4 |   13.1952   |           8.46519 |
|    500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    2.29626  |          84.0709  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |           4 |   16.4856   |         -14.3602  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 1076.12     |       -7365.02    |
|    500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |         256 |   14.6825   |          -1.85217 |
|    500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |         256 |   12.3418   |          14.3852  |
|    500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    2.22262  |          84.5817  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |         256 |   14.6266   |          -1.4644  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 1063.45     |       -7277.13    |
|    500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |           4 |   14.9879   |          -3.97073 |
|    500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    2.547    |          82.3315  |
|    500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |    0.566151 |          96.0726  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    3.68398  |          74.4443  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 |  263.744    |       -1729.59    |
|    500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |         256 |   14.8222   |          -2.82127 |
|    500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    2.89534  |          79.9151  |
|    500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |    0.605023 |          95.803   |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    3.82158  |          73.4898  |
|    500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 |  471.274    |       -3169.22    |

|   Size |   Sparsity | Matrix A Type   | Matrix B Type   | Function       |   Threads |   Tile Size |   Time (ms) |   Time % Decrease |
|-------:|-----------:|:----------------|:----------------|:---------------|----------:|------------:|------------:|------------------:|
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |           4 |   1422.05   |          0        |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |           4 |   1517.74   |         -6.72902  |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |           4 |    266.976  |         81.226    |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |           4 |   1458.33   |         -2.55125  |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |           4 | 666143      |     -46743.9      |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         1 |         256 |   1451.46   |         -2.06814  |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         1 |         256 |   1616.31   |        -13.6606   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         1 |         256 |    280.075  |         80.3048   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         1 |         256 |   1499.02   |         -5.41261  |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         1 |         256 | 689969      |     -48419.3      |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |           4 |   1470.34   |         -3.3958   |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |           4 |    300.393  |         78.8761   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |           4 |     51.5217 |         96.3769   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |           4 |    274.401  |         80.7038   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |           4 | 124828      |      -8678.03     |
|   2500 |       0.01 | Dense           | Sparse          | Unoptimized    |         8 |         256 |   1427.3    |         -0.369185 |
|   2500 |       0.01 | Dense           | Sparse          | Multithreaded  |         8 |         256 |    297.91   |         79.0507   |
|   2500 |       0.01 | Dense           | Sparse          | MT with SIMD   |         8 |         256 |     50.732  |         96.4325   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt      |         8 |         256 |    271.159  |         80.9318   |
|   2500 |       0.01 | Dense           | Sparse          | Cache Opt SIMD |         8 |         256 | 139794      |      -9730.46     |

Dense form * CSR form matrix multipication results are even more interesting then Sparse * Sparse results.
Unlike Sparse * Sparse, multithreading is always beneficial, likely due to the fact that even the smallest case has hundreds-thousands of operations, so the overhead is less significant.
As with Dense * Dense, cache optimization alone is not beneficial with small sizes, and only starts to be beneficial as sizes/densities increase. However, the threshold for positive benefit is higher then with Dense * Dense.
The most interesting reuslt is SIMD + Cache optimizated. I have double checked my implementation, and I do not believe it is an implementation error, but I'm not 100% sure. While both SIMD and Cache optimizations provide some positive benefit under some conditions, SIMD + Cache is an extremely significant performance hit.
I am assuming it is something to do with how the cache is aligned in this scenario, and how the cache optimization modifies it to work poorly with SIMD.

## Analysis

Overall, this experiment provided some very interesting results. This shows how there is never a "best implementation", an that not everything that technically can result in a speedup is always beneficial.
Depending on the exact circumstances and implementation, the optimial configuration can vary significantly.