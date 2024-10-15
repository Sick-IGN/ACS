
## Size: 10x10 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4629 |
| Threaded (1 thread)                  | 244208 |
| Threaded (4 threads)                 | 272991 |
| Threaded (8 threads)                 | 1146346 |
| Threaded (16 threads)                | 1117762 |
| SIMD (1 thread)                      | 108803 |
| SIMD (4 threads)                     | 231333 |
| SIMD (8 threads)                     | 534541 |
| SIMD (16 threads)                    | 1136017 |
| Cache (block 4, 1 thread)            | 97182 |
| Cache (block 4, 4 threads)           | 227196 |
| Cache (block 4, 8 threads)           | 505587 |
| Cache (block 4, 16 threads)          | 1230454 |
| Cache (block 64, 1 thread)           | 93435 |
| Cache (block 64, 4 threads)          | 245580 |
| Cache (block 64, 8 threads)          | 514534 |
| Cache (block 64, 16 threads)         | 1199536 |
| Cache (block 256, 1 thread)          | 98625 |
| Cache (block 256, 4 threads)         | 238430 |
| Cache (block 256, 8 threads)         | 478523 |
| Cache (block 256, 16 threads)        | 1299925 |
| All opt (block 4, 1 thread)          | 110767 |
| All opt (block 4, 4 threads)         | 299113 |
| All opt (block 4, 8 threads)         | 509524 |
| All opt (block 4, 16 threads)        | 1309790 |
| All opt (block 64, 1 thread)         | 101160 |
| All opt (block 64, 4 threads)        | 252513 |
| All opt (block 64, 8 threads)        | 521467 |
| All opt (block 64, 16 threads)       | 1291578 |
| All opt (block 256, 1 thread)        | 101600 |
| All opt (block 256, 4 threads)       | 239511 |
| All opt (block 256, 8 threads)       | 551018 |
| All opt (block 256, 16 threads)      | 1271531 |

## Size: 10x10 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4629 |
| Threaded (1 thread)                  | 115657 |
| Threaded (4 threads)                 | 316233 |
| Threaded (8 threads)                 | 633806 |
| Threaded (16 threads)                | 1473490 |
| SIMD (1 thread)                      | 122338 |
| SIMD (4 threads)                     | 316563 |
| SIMD (8 threads)                     | 505126 |
| SIMD (16 threads)                    | 1311876 |
| Cache (block 4, 1 thread)            | 120496 |
| Cache (block 4, 4 threads)           | 296255 |
| Cache (block 4, 8 threads)           | 590806 |
| Cache (block 4, 16 threads)          | 1326603 |
| Cache (block 64, 1 thread)           | 185608 |
| Cache (block 64, 4 threads)          | 249107 |
| Cache (block 64, 8 threads)          | 651490 |
| Cache (block 64, 16 threads)         | 1238208 |
| Cache (block 256, 1 thread)          | 101360 |
| Cache (block 256, 4 threads)         | 254316 |
| Cache (block 256, 8 threads)         | 625512 |
| Cache (block 256, 16 threads)        | 1264560 |
| All opt (block 4, 1 thread)          | 111268 |
| All opt (block 4, 4 threads)         | 238864 |
| All opt (block 4, 8 threads)         | 463427 |
| All opt (block 4, 16 threads)        | 1371157 |
| All opt (block 64, 1 thread)         | 89868 |
| All opt (block 64, 4 threads)        | 365314 |
| All opt (block 64, 8 threads)        | 594533 |
| All opt (block 64, 16 threads)       | 1171984 |
| All opt (block 256, 1 thread)        | 95459 |
| All opt (block 256, 4 threads)       | 223238 |
| All opt (block 256, 8 threads)       | 448690 |
| All opt (block 256, 16 threads)      | 1144312 |

## Size: 10x10 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4619 |
| Threaded (1 thread)                  | 129031 |
| Threaded (4 threads)                 | 256774 |
| Threaded (8 threads)                 | 513782 |
| Threaded (16 threads)                | 1376126 |
| SIMD (1 thread)                      | 98775 |
| SIMD (4 threads)                     | 242631 |
| SIMD (8 threads)                     | 654926 |
| SIMD (16 threads)                    | 1261715 |
| Cache (block 4, 1 thread)            | 119190 |
| Cache (block 4, 4 threads)           | 356487 |
| Cache (block 4, 8 threads)           | 710591 |
| Cache (block 4, 16 threads)          | 1590819 |
| Cache (block 64, 1 thread)           | 104034 |
| Cache (block 64, 4 threads)          | 236242 |
| Cache (block 64, 8 threads)          | 529402 |
| Cache (block 64, 16 threads)         | 1126549 |
| Cache (block 256, 1 thread)          | 95549 |
| Cache (block 256, 4 threads)         | 224340 |
| Cache (block 256, 8 threads)         | 598581 |
| Cache (block 256, 16 threads)        | 1302014 |
| All opt (block 4, 1 thread)          | 113820 |
| All opt (block 4, 4 threads)         | 248182 |
| All opt (block 4, 8 threads)         | 474930 |
| All opt (block 4, 16 threads)        | 1247807 |
| All opt (block 64, 1 thread)         | 108483 |
| All opt (block 64, 4 threads)        | 245901 |
| All opt (block 64, 8 threads)        | 464259 |
| All opt (block 64, 16 threads)       | 1545584 |
| All opt (block 256, 1 thread)        | 103013 |
| All opt (block 256, 4 threads)       | 223799 |
| All opt (block 256, 8 threads)       | 470441 |
| All opt (block 256, 16 threads)      | 1146346 |

## Size: 10x10 ------ Sparsity: 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4699 |
| Threaded (1 thread)                  | 131657 |
| Threaded (4 threads)                 | 270236 |
| Threaded (8 threads)                 | 745555 |
| Threaded (16 threads)                | 1385433 |
| SIMD (1 thread)                      | 110166 |
| SIMD (4 threads)                     | 287067 |
| SIMD (8 threads)                     | 578603 |
| SIMD (16 threads)                    | 1362614 |
| Cache (block 4, 1 thread)            | 121053 |
| Cache (block 4, 4 threads)           | 258795 |
| Cache (block 4, 8 threads)           | 515155 |
| Cache (block 4, 16 threads)          | 1340820 |
| Cache (block 64, 1 thread)           | 101289 |
| Cache (block 64, 4 threads)          | 236913 |
| Cache (block 64, 8 threads)          | 465492 |
| Cache (block 64, 16 threads)         | 1172966 |
| Cache (block 256, 1 thread)          | 94317 |
| Cache (block 256, 4 threads)         | 228919 |
| Cache (block 256, 8 threads)         | 479257 |
| Cache (block 256, 16 threads)        | 1405240 |
| All opt (block 4, 1 thread)          | 100157 |
| All opt (block 4, 4 threads)         | 229290 |
| All opt (block 4, 8 threads)         | 455172 |
| All opt (block 4, 16 threads)        | 1135216 |
| All opt (block 64, 1 thread)         | 90710 |
| All opt (block 64, 4 threads)        | 233848 |
| All opt (block 64, 8 threads)        | 492482 |
| All opt (block 64, 16 threads)       | 1109297 |
| All opt (block 256, 1 thread)        | 114855 |
| All opt (block 256, 4 threads)       | 365664 |
| All opt (block 256, 8 threads)       | 466793 |
| All opt (block 256, 16 threads)      | 1091934 |

## Size: 10x10 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4609 |
| Threaded (1 thread)                  | 108072 |
| Threaded (4 threads)                 | 250660 |
| Threaded (8 threads)                 | 610523 |
| Threaded (16 threads)                | 1358350 |
| SIMD (1 thread)                      | 114273 |
| SIMD (4 threads)                     | 244909 |
| SIMD (8 threads)                     | 691434 |
| SIMD (16 threads)                    | 1757029 |
| Cache (block 4, 1 thread)            | 130016 |
| Cache (block 4, 4 threads)           | 345637 |
| Cache (block 4, 8 threads)           | 759452 |
| Cache (block 4, 16 threads)          | 1315453 |
| Cache (block 64, 1 thread)           | 114902 |
| Cache (block 64, 4 threads)          | 233698 |
| Cache (block 64, 8 threads)          | 509905 |
| Cache (block 64, 16 threads)         | 1383351 |
| Cache (block 256, 1 thread)          | 105017 |
| Cache (block 256, 4 threads)         | 218439 |
| Cache (block 256, 8 threads)         | 553857 |
| Cache (block 256, 16 threads)        | 1177825 |
| All opt (block 4, 1 thread)          | 111300 |
| All opt (block 4, 4 threads)         | 295536 |
| All opt (block 4, 8 threads)         | 477925 |
| All opt (block 4, 16 threads)        | 1224801 |
| All opt (block 64, 1 thread)         | 100117 |
| All opt (block 64, 4 threads)        | 274704 |
| All opt (block 64, 8 threads)        | 448931 |
| All opt (block 64, 16 threads)       | 1969568 |
| All opt (block 256, 1 thread)        | 115696 |
| All opt (block 256, 4 threads)       | 265236 |
| All opt (block 256, 8 threads)       | 562854 |
| All opt (block 256, 16 threads)      | 1550433 |

## Size: 100x100 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4404520 |
| Threaded (1 thread)                  | 4450358 |
| Threaded (4 threads)                 | 1390837 |
| Threaded (8 threads)                 | 1296136 |
| Threaded (16 threads)                | 1778757 |
| SIMD (1 thread)                      | 1822001 |
| SIMD (4 threads)                     | 684903 |
| SIMD (8 threads)                     | 709428 |
| SIMD (16 threads)                    | 1591703 |
| Cache (block 4, 1 thread)            | 6530466 |
| Cache (block 4, 4 threads)           | 1846338 |
| Cache (block 4, 8 threads)           | 1601479 |
| Cache (block 4, 16 threads)          | 1974505 |
| Cache (block 64, 1 thread)           | 6425882 |
| Cache (block 64, 4 threads)          | 1342567 |
| Cache (block 64, 8 threads)          | 1181753 |
| Cache (block 64, 16 threads)         | 1681848 |
| Cache (block 256, 1 thread)          | 4215001 |
| Cache (block 256, 4 threads)         | 1191237 |
| Cache (block 256, 8 threads)         | 1162489 |
| Cache (block 256, 16 threads)        | 2060415 |
| All opt (block 4, 1 thread)          | 3460692 |
| All opt (block 4, 4 threads)         | 985743 |
| All opt (block 4, 8 threads)         | 1063804 |
| All opt (block 4, 16 threads)        | 1518850 |
| All opt (block 64, 1 thread)         | 2241108 |
| All opt (block 64, 4 threads)        | 863159 |
| All opt (block 64, 8 threads)        | 889863 |
| All opt (block 64, 16 threads)       | 1468239 |
| All opt (block 256, 1 thread)        | 2103345 |
| All opt (block 256, 4 threads)       | 787735 |
| All opt (block 256, 8 threads)       | 858688 |
| All opt (block 256, 16 threads)      | 1579988 |

## Size: 100x100 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4446284 |
| Threaded (1 thread)                  | 5118854 |
| Threaded (4 threads)                 | 2012431 |
| Threaded (8 threads)                 | 1386594 |
| Threaded (16 threads)                | 1668664 |
| SIMD (1 thread)                      | 1746449 |
| SIMD (4 threads)                     | 659515 |
| SIMD (8 threads)                     | 683078 |
| SIMD (16 threads)                    | 1527669 |
| Cache (block 4, 1 thread)            | 7283749 |
| Cache (block 4, 4 threads)           | 1740897 |
| Cache (block 4, 8 threads)           | 1891434 |
| Cache (block 4, 16 threads)          | 2333486 |
| Cache (block 64, 1 thread)           | 4876483 |
| Cache (block 64, 4 threads)          | 1290613 |
| Cache (block 64, 8 threads)          | 1474931 |
| Cache (block 64, 16 threads)         | 1776406 |
| Cache (block 256, 1 thread)          | 4456848 |
| Cache (block 256, 4 threads)         | 1324948 |
| Cache (block 256, 8 threads)         | 1546486 |
| Cache (block 256, 16 threads)        | 2224466 |
| All opt (block 4, 1 thread)          | 3160561 |
| All opt (block 4, 4 threads)         | 1015379 |
| All opt (block 4, 8 threads)         | 994865 |
| All opt (block 4, 16 threads)        | 1528259 |
| All opt (block 64, 1 thread)         | 2292301 |
| All opt (block 64, 4 threads)        | 801761 |
| All opt (block 64, 8 threads)        | 1023466 |
| All opt (block 64, 16 threads)       | 1727105 |
| All opt (block 256, 1 thread)        | 2239371 |
| All opt (block 256, 4 threads)       | 771384 |
| All opt (block 256, 8 threads)       | 865771 |
| All opt (block 256, 16 threads)      | 1645752 |

## Size: 100x100 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4541693 |
| Threaded (1 thread)                  | 4797451 |
| Threaded (4 threads)                 | 1362234 |
| Threaded (8 threads)                 | 1161745 |
| Threaded (16 threads)                | 1609481 |
| SIMD (1 thread)                      | 1666293 |
| SIMD (4 threads)                     | 960569 |
| SIMD (8 threads)                     | 726428 |
| SIMD (16 threads)                    | 1810630 |
| Cache (block 4, 1 thread)            | 6119932 |
| Cache (block 4, 4 threads)           | 1680536 |
| Cache (block 4, 8 threads)           | 1628850 |
| Cache (block 4, 16 threads)          | 2226228 |
| Cache (block 64, 1 thread)           | 4668260 |
| Cache (block 64, 4 threads)          | 1300832 |
| Cache (block 64, 8 threads)          | 1404212 |
| Cache (block 64, 16 threads)         | 1790639 |
| Cache (block 256, 1 thread)          | 3994841 |
| Cache (block 256, 4 threads)         | 1213639 |
| Cache (block 256, 8 threads)         | 1183205 |
| Cache (block 256, 16 threads)        | 2093139 |
| All opt (block 4, 1 thread)          | 3645004 |
| All opt (block 4, 4 threads)         | 1004731 |
| All opt (block 4, 8 threads)         | 1259992 |
| All opt (block 4, 16 threads)        | 1656502 |
| All opt (block 64, 1 thread)         | 2433283 |
| All opt (block 64, 4 threads)        | 817871 |
| All opt (block 64, 8 threads)        | 913351 |
| All opt (block 64, 16 threads)       | 1386526 |
| All opt (block 256, 1 thread)        | 2446840 |
| All opt (block 256, 4 threads)       | 760263 |
| All opt (block 256, 8 threads)       | 872715 |
| All opt (block 256, 16 threads)      | 1514896 |

## Size: 100x100 ------ Sparsity: 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4298417 |
| Threaded (1 thread)                  | 4422467 |
| Threaded (4 threads)                 | 1876633 |
| Threaded (8 threads)                 | 1041941 |
| Threaded (16 threads)                | 2031547 |
| SIMD (1 thread)                      | 1769440 |
| SIMD (4 threads)                     | 618678 |
| SIMD (8 threads)                     | 729365 |
| SIMD (16 threads)                    | 1422514 |
| Cache (block 4, 1 thread)            | 6071150 |
| Cache (block 4, 4 threads)           | 1773491 |
| Cache (block 4, 8 threads)           | 1731028 |
| Cache (block 4, 16 threads)          | 1997151 |
| Cache (block 64, 1 thread)           | 4214491 |
| Cache (block 64, 4 threads)          | 1273103 |
| Cache (block 64, 8 threads)          | 1205737 |
| Cache (block 64, 16 threads)         | 1743715 |
| Cache (block 256, 1 thread)          | 4060034 |
| Cache (block 256, 4 threads)         | 1522528 |
| Cache (block 256, 8 threads)         | 1138742 |
| Cache (block 256, 16 threads)        | 1605476 |
| All opt (block 4, 1 thread)          | 3135804 |
| All opt (block 4, 4 threads)         | 1016002 |
| All opt (block 4, 8 threads)         | 1070642 |
| All opt (block 4, 16 threads)        | 1761598 |
| All opt (block 64, 1 thread)         | 2133254 |
| All opt (block 64, 4 threads)        | 757819 |
| All opt (block 64, 8 threads)        | 1020814 |
| All opt (block 64, 16 threads)       | 1672929 |
| All opt (block 256, 1 thread)        | 2059749 |
| All opt (block 256, 4 threads)       | 1134422 |
| All opt (block 256, 8 threads)       | 803525 |
| All opt (block 256, 16 threads)      | 1633900 |

## Size: 100x100 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4159297 |
| Threaded (1 thread)                  | 4786364 |
| Threaded (4 threads)                 | 1336168 |
| Threaded (8 threads)                 | 1101231 |
| Threaded (16 threads)                | 1682900 |
| SIMD (1 thread)                      | 2011114 |
| SIMD (4 threads)                     | 695923 |
| SIMD (8 threads)                     | 673562 |
| SIMD (16 threads)                    | 1249482 |
| Cache (block 4, 1 thread)            | 5870651 |
| Cache (block 4, 4 threads)           | 1854111 |
| Cache (block 4, 8 threads)           | 1986258 |
| Cache (block 4, 16 threads)          | 1827231 |
| Cache (block 64, 1 thread)           | 4552450 |
| Cache (block 64, 4 threads)          | 1343415 |
| Cache (block 64, 8 threads)          | 1197923 |
| Cache (block 64, 16 threads)         | 1824155 |
| Cache (block 256, 1 thread)          | 4281067 |
| Cache (block 256, 4 threads)         | 1274126 |
| Cache (block 256, 8 threads)         | 1191902 |
| Cache (block 256, 16 threads)        | 1785914 |
| All opt (block 4, 1 thread)          | 3101597 |
| All opt (block 4, 4 threads)         | 1342153 |
| All opt (block 4, 8 threads)         | 1003349 |
| All opt (block 4, 16 threads)        | 1811154 |
| All opt (block 64, 1 thread)         | 2418956 |
| All opt (block 64, 4 threads)        | 731760 |
| All opt (block 64, 8 threads)        | 779279 |
| All opt (block 64, 16 threads)       | 1489950 |
| All opt (block 256, 1 thread)        | 2042374 |
| All opt (block 256, 4 threads)       | 706052 |
| All opt (block 256, 8 threads)       | 764391 |
| All opt (block 256, 16 threads)      | 1320893 |

## Size: 500x500 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 510211472 |
| Threaded (1 thread)                  | 508969197 |
| Threaded (4 threads)                 | 158153603 |
| Threaded (8 threads)                 | 95030839 |
| Threaded (16 threads)                | 57561431 |
| SIMD (1 thread)                      | 195588170 |
| SIMD (4 threads)                     | 51233160 |
| SIMD (8 threads)                     | 40162167 |
| SIMD (16 threads)                    | 22721498 |
| Cache (block 4, 1 thread)            | 826499070 |
| Cache (block 4, 4 threads)           | 266923407 |
| Cache (block 4, 8 threads)           | 140026602 |
| Cache (block 4, 16 threads)          | 81954951 |
| Cache (block 64, 1 thread)           | 501633023 |
| Cache (block 64, 4 threads)          | 218058940 |
| Cache (block 64, 8 threads)          | 93283446 |
| Cache (block 64, 16 threads)         | 60509139 |
| Cache (block 256, 1 thread)          | 477387699 |
| Cache (block 256, 4 threads)         | 227414663 |
| Cache (block 256, 8 threads)         | 94139805 |
| Cache (block 256, 16 threads)        | 56740176 |
| All opt (block 4, 1 thread)          | 374167952 |
| All opt (block 4, 4 threads)         | 148456326 |
| All opt (block 4, 8 threads)         | 81453289 |
| All opt (block 4, 16 threads)        | 41249427 |
| All opt (block 64, 1 thread)         | 245866056 |
| All opt (block 64, 4 threads)        | 112244431 |
| All opt (block 64, 8 threads)        | 48544818 |
| All opt (block 64, 16 threads)       | 29564791 |
| All opt (block 256, 1 thread)        | 242219184 |
| All opt (block 256, 4 threads)       | 109953429 |
| All opt (block 256, 8 threads)       | 54250189 |
| All opt (block 256, 16 threads)      | 30226182 |

## Size: 500x500 ------ Sparsity: 0.01
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

## Size: 500x500 ------ Sparsity: 0.1
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

## Size: 500x500 ------ Sparsity: 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 509907479 |
| Threaded (1 thread)                  | 516985852 |
| Threaded (4 threads)                 | 155031611 |
| Threaded (8 threads)                 | 102727973 |
| Threaded (16 threads)                | 56140781 |
| SIMD (1 thread)                      | 208558005 |
| SIMD (4 threads)                     | 52462019 |
| SIMD (8 threads)                     | 43685983 |
| SIMD (16 threads)                    | 22408749 |
| Cache (block 4, 1 thread)            | 714175418 |
| Cache (block 4, 4 threads)           | 331196195 |
| Cache (block 4, 8 threads)           | 144981805 |
| Cache (block 4, 16 threads)          | 81737414 |
| Cache (block 64, 1 thread)           | 496357193 |
| Cache (block 64, 4 threads)          | 192609044 |
| Cache (block 64, 8 threads)          | 113641261 |
| Cache (block 64, 16 threads)         | 68965123 |
| Cache (block 256, 1 thread)          | 529742607 |
| Cache (block 256, 4 threads)         | 148811491 |
| Cache (block 256, 8 threads)         | 97691978 |
| Cache (block 256, 16 threads)        | 58864658 |
| All opt (block 4, 1 thread)          | 388331330 |
| All opt (block 4, 4 threads)         | 158190921 |
| All opt (block 4, 8 threads)         | 81936180 |
| All opt (block 4, 16 threads)        | 43382295 |
| All opt (block 64, 1 thread)         | 250265499 |
| All opt (block 64, 4 threads)        | 95561547 |
| All opt (block 64, 8 threads)        | 55734420 |
| All opt (block 64, 16 threads)       | 30919971 |
| All opt (block 256, 1 thread)        | 244613368 |
| All opt (block 256, 4 threads)       | 61234707 |
| All opt (block 256, 8 threads)       | 35274291 |
| All opt (block 256, 16 threads)      | 28626538 |

## Size: 500x500 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 546572073 |
| Threaded (1 thread)                  | 502356966 |
| Threaded (4 threads)                 | 132314825 |
| Threaded (8 threads)                 | 106228971 |
| Threaded (16 threads)                | 56131094 |
| SIMD (1 thread)                      | 194026354 |
| SIMD (4 threads)                     | 49488945 |
| SIMD (8 threads)                     | 36270078 |
| SIMD (16 threads)                    | 22463570 |
| Cache (block 4, 1 thread)            | 717996658 |
| Cache (block 4, 4 threads)           | 235621104 |
| Cache (block 4, 8 threads)           | 137033105 |
| Cache (block 4, 16 threads)          | 89434562 |
| Cache (block 64, 1 thread)           | 502314589 |
| Cache (block 64, 4 threads)          | 218251391 |
| Cache (block 64, 8 threads)          | 95657905 |
| Cache (block 64, 16 threads)         | 60016839 |
| Cache (block 256, 1 thread)          | 477177607 |
| Cache (block 256, 4 threads)         | 120071320 |
| Cache (block 256, 8 threads)         | 83011143 |
| Cache (block 256, 16 threads)        | 56754879 |
| All opt (block 4, 1 thread)          | 367844945 |
| All opt (block 4, 4 threads)         | 114631050 |
| All opt (block 4, 8 threads)         | 81729333 |
| All opt (block 4, 16 threads)        | 39841189 |
| All opt (block 64, 1 thread)         | 249468243 |
| All opt (block 64, 4 threads)        | 62787988 |
| All opt (block 64, 8 threads)        | 56957342 |
| All opt (block 64, 16 threads)       | 28662818 |
| All opt (block 256, 1 thread)        | 242955359 |
| All opt (block 256, 4 threads)       | 61220974 |
| All opt (block 256, 8 threads)       | 50762404 |
| All opt (block 256, 16 threads)      | 28854284 |

## Size: 1000x1000 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4212744302 |
| Threaded (1 thread)                  | 4193792649 |
| Threaded (4 threads)                 | 1400709193 |
| Threaded (8 threads)                 | 782867692 |
| Threaded (16 threads)                | 442822773 |
| SIMD (1 thread)                      | 1709857862 |
| SIMD (4 threads)                     | 540969819 |
| SIMD (8 threads)                     | 317839046 |
| SIMD (16 threads)                    | 170178283 |
| Cache (block 4, 1 thread)            | 5885572107 |
| Cache (block 4, 4 threads)           | 1771830078 |
| Cache (block 4, 8 threads)           | 1007779499 |
| Cache (block 4, 16 threads)          | 651167442 |
| Cache (block 64, 1 thread)           | 4111118130 |
| Cache (block 64, 4 threads)          | 1464868891 |
| Cache (block 64, 8 threads)          | 764614708 |
| Cache (block 64, 16 threads)         | 462044463 |
| Cache (block 256, 1 thread)          | 3948909548 |
| Cache (block 256, 4 threads)         | 1159276060 |
| Cache (block 256, 8 threads)         | 727205396 |
| Cache (block 256, 16 threads)        | 442804977 |
| All opt (block 4, 1 thread)          | 3084684156 |
| All opt (block 4, 4 threads)         | 865621400 |
| All opt (block 4, 8 threads)         | 578331109 |
| All opt (block 4, 16 threads)        | 322714099 |
| All opt (block 64, 1 thread)         | 2021282577 |
| All opt (block 64, 4 threads)        | 631012490 |
| All opt (block 64, 8 threads)        | 353256279 |
| All opt (block 64, 16 threads)       | 221382741 |
| All opt (block 256, 1 thread)        | 1984859620 |
| All opt (block 256, 4 threads)       | 624952077 |
| All opt (block 256, 8 threads)       | 364383696 |
| All opt (block 256, 16 threads)      | 216808521 |

## Size: 1000x1000 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4294656688 |
| Threaded (1 thread)                  | 4168935073 |
| Threaded (4 threads)                 | 1323717746 |
| Threaded (8 threads)                 | 763618678 |
| Threaded (16 threads)                | 436067229 |
| SIMD (1 thread)                      | 1602808823 |
| SIMD (4 threads)                     | 510687009 |
| SIMD (8 threads)                     | 274777387 |
| SIMD (16 threads)                    | 179863900 |
| Cache (block 4, 1 thread)            | 6058717574 |
| Cache (block 4, 4 threads)           | 1931580372 |
| Cache (block 4, 8 threads)           | 1074997458 |
| Cache (block 4, 16 threads)          | 656457557 |
| Cache (block 64, 1 thread)           | 4247919984 |
| Cache (block 64, 4 threads)          | 1082607430 |
| Cache (block 64, 8 threads)          | 742491679 |
| Cache (block 64, 16 threads)         | 491903457 |
| Cache (block 256, 1 thread)          | 3926975198 |
| Cache (block 256, 4 threads)         | 1073734989 |
| Cache (block 256, 8 threads)         | 669162474 |
| Cache (block 256, 16 threads)        | 460465625 |
| All opt (block 4, 1 thread)          | 3054710819 |
| All opt (block 4, 4 threads)         | 1003268126 |
| All opt (block 4, 8 threads)         | 520420059 |
| All opt (block 4, 16 threads)        | 307107482 |
| All opt (block 64, 1 thread)         | 2054399466 |
| All opt (block 64, 4 threads)        | 719062691 |
| All opt (block 64, 8 threads)        | 431874491 |
| All opt (block 64, 16 threads)       | 229214124 |
| All opt (block 256, 1 thread)        | 1978221226 |
| All opt (block 256, 4 threads)       | 773983056 |
| All opt (block 256, 8 threads)       | 381038927 |
| All opt (block 256, 16 threads)      | 237453871 |

## Size: 1000x1000 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4247069295 |
| Threaded (1 thread)                  | 4437568248 |
| Threaded (4 threads)                 | 1365448581 |
| Threaded (8 threads)                 | 734487091 |
| Threaded (16 threads)                | 452998151 |
| SIMD (1 thread)                      | 1554775584 |
| SIMD (4 threads)                     | 583428968 |
| SIMD (8 threads)                     | 310212482 |
| SIMD (16 threads)                    | 172193334 |
| Cache (block 4, 1 thread)            | 6116412685 |
| Cache (block 4, 4 threads)           | 1815496908 |
| Cache (block 4, 8 threads)           | 991837806 |
| Cache (block 4, 16 threads)          | 674101814 |
| Cache (block 64, 1 thread)           | 4236483971 |
| Cache (block 64, 4 threads)          | 1252752846 |
| Cache (block 64, 8 threads)          | 774325099 |
| Cache (block 64, 16 threads)         | 473953928 |
| Cache (block 256, 1 thread)          | 3912075215 |
| Cache (block 256, 4 threads)         | 1320484582 |
| Cache (block 256, 8 threads)         | 715259110 |
| Cache (block 256, 16 threads)        | 477097293 |
| All opt (block 4, 1 thread)          | 3133860379 |
| All opt (block 4, 4 threads)         | 849716878 |
| All opt (block 4, 8 threads)         | 515941006 |
| All opt (block 4, 16 threads)        | 319655248 |
| All opt (block 64, 1 thread)         | 2063478001 |
| All opt (block 64, 4 threads)        | 739072671 |
| All opt (block 64, 8 threads)        | 400877140 |
| All opt (block 64, 16 threads)       | 220912547 |
| All opt (block 256, 1 thread)        | 1975645724 |
| All opt (block 256, 4 threads)       | 712296863 |
| All opt (block 256, 8 threads)       | 358720264 |
| All opt (block 256, 16 threads)      | 223406011 |

## Size: 1000x1000 ------ Sparsity: 0.5
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4301761032 |
| Threaded (1 thread)                  | 4419887828 |
| Threaded (4 threads)                 | 1435621535 |
| Threaded (8 threads)                 | 751867140 |
| Threaded (16 threads)                | 464306239 |
| SIMD (1 thread)                      | 1695794044 |
| SIMD (4 threads)                     | 581766008 |
| SIMD (8 threads)                     | 303198997 |
| SIMD (16 threads)                    | 170979648 |
| Cache (block 4, 1 thread)            | 5831291818 |
| Cache (block 4, 4 threads)           | 1768384766 |
| Cache (block 4, 8 threads)           | 1134593068 |
| Cache (block 4, 16 threads)          | 661391735 |
| Cache (block 64, 1 thread)           | 4117528323 |
| Cache (block 64, 4 threads)          | 1268028487 |
| Cache (block 64, 8 threads)          | 702366984 |
| Cache (block 64, 16 threads)         | 477357216 |
| Cache (block 256, 1 thread)          | 3898525595 |
| Cache (block 256, 4 threads)         | 1374676201 |
| Cache (block 256, 8 threads)         | 742640656 |
| Cache (block 256, 16 threads)        | 460245753 |
| All opt (block 4, 1 thread)          | 3204278392 |
| All opt (block 4, 4 threads)         | 938818481 |
| All opt (block 4, 8 threads)         | 531928943 |
| All opt (block 4, 16 threads)        | 351956328 |
| All opt (block 64, 1 thread)         | 1989279749 |
| All opt (block 64, 4 threads)        | 661674624 |
| All opt (block 64, 8 threads)        | 389383776 |
| All opt (block 64, 16 threads)       | 221527454 |
| All opt (block 256, 1 thread)        | 1978687415 |
| All opt (block 256, 4 threads)       | 553341115 |
| All opt (block 256, 8 threads)       | 357792091 |
| All opt (block 256, 16 threads)      | 231984502 |

## Size: 1000x1000 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 4341844907 |
| Threaded (1 thread)                  | 4295070978 |
| Threaded (4 threads)                 | 1252358577 |
| Threaded (8 threads)                 | 784406031 |
| Threaded (16 threads)                | 441387030 |
| SIMD (1 thread)                      | 1594452112 |
| SIMD (4 threads)                     | 451673035 |
| SIMD (8 threads)                     | 286994102 |
| SIMD (16 threads)                    | 168056382 |
| Cache (block 4, 1 thread)            | 5865500194 |
| Cache (block 4, 4 threads)           | 1724550514 |
| Cache (block 4, 8 threads)           | 962059264 |
| Cache (block 4, 16 threads)          | 660186878 |
| Cache (block 64, 1 thread)           | 4105627152 |
| Cache (block 64, 4 threads)          | 1297229353 |
| Cache (block 64, 8 threads)          | 757471337 |
| Cache (block 64, 16 threads)         | 483753349 |
| Cache (block 256, 1 thread)          | 3898198169 |
| Cache (block 256, 4 threads)         | 1371690743 |
| Cache (block 256, 8 threads)         | 691795357 |
| Cache (block 256, 16 threads)        | 453625017 |
| All opt (block 4, 1 thread)          | 3138240407 |
| All opt (block 4, 4 threads)         | 982627303 |
| All opt (block 4, 8 threads)         | 562587345 |
| All opt (block 4, 16 threads)        | 318619597 |
| All opt (block 64, 1 thread)         | 2011699826 |
| All opt (block 64, 4 threads)        | 671653290 |
| All opt (block 64, 8 threads)        | 388275500 |
| All opt (block 64, 16 threads)       | 228220733 |
| All opt (block 256, 1 thread)        | 1950275996 |
| All opt (block 256, 4 threads)       | 559376660 |
| All opt (block 256, 8 threads)       | 359902520 |
| All opt (block 256, 16 threads)      | 231739888 |

## Size: 2500x2500 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 149964445868 |
| Threaded (1 thread)                  | 144438103914 |
| Threaded (8 threads)                 | 22925982180 |
| SIMD (1 thread)                      | 60596506907 |
| SIMD (8 threads)                     | 7609697453 |
| Cache (block 4, 1 thread)            | 98121880701 |
| Cache (block 4, 8 threads)           | 17504468518 |
| Cache (block 256, 1 thread)          | 64587949367 |
| Cache (block 256, 8 threads)         | 12220128504 |
| All opt (block 4, 1 thread)          | 57567459095 |
| All opt (block 4, 8 threads)         | 8562352975 |
| All opt (block 256, 1 thread)        | 31580755653 |
| All opt (block 256, 8 threads)       | 5714858197 |

## Size: 2500x2500 ------ Sparsity: 0.01
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

## Size: 2500x2500 ------ Sparsity: 0.1
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

## Size: 2500x2500 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 152476561898 |
| Threaded (1 thread)                  | 162118434307 |
| Threaded (8 threads)                 | 23278947044 |
| SIMD (1 thread)                      | 57678801470 |
| SIMD (8 threads)                     | 7734838620 |
| Cache (block 4, 1 thread)            | 97428711623 |
| Cache (block 4, 8 threads)           | 15743954575 |
| Cache (block 256, 1 thread)          | 63755349378 |
| Cache (block 256, 8 threads)         | 10716977040 |
| All opt (block 4, 1 thread)          | 55473905468 |
| All opt (block 4, 8 threads)         | 8637097753 |
| All opt (block 256, 1 thread)        | 31518941625 |
| All opt (block 256, 8 threads)       | 5306459310 |

## Size: 5000x5000 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 1371472345442 |
| Threaded (1 thread)                  | 1346110410814 |
| Threaded (8 threads)                 | 211782169653 |
| SIMD (1 thread)                      | 375478469343 |
| SIMD (8 threads)                     | 58737281669 |
| Cache (block 4, 1 thread)            | 780027213677 |
| Cache (block 4, 8 threads)           | 125758852994 |
| Cache (block 256, 1 thread)          | 511608275545 |
| Cache (block 256, 8 threads)         | 84685473856 |
| All opt (block 4, 1 thread)          | 440003565843 |
| All opt (block 4, 8 threads)         | 67949541944 |
| All opt (block 256, 1 thread)        | 249688313473 |
| All opt (block 256, 8 threads)       | 41338255368 |

## Size: 5000x5000 ------ Sparsity: 0.01
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 1400252387383 |
| Threaded (1 thread)                  | 1319309772289 |
| Threaded (8 threads)                 | 210601403926 |
| SIMD (1 thread)                      | 367854015317 |
| SIMD (8 threads)                     | 58781327164 |
| Cache (block 4, 1 thread)            | 779722525632 |
| Cache (block 4, 8 threads)           | 124795471487 |
| Cache (block 256, 1 thread)          | 512072705607 |
| Cache (block 256, 8 threads)         | 83870961449 |
| All opt (block 4, 1 thread)          | 439020416639 |
| All opt (block 4, 8 threads)         | 67611323475 |
| All opt (block 256, 1 thread)        | 249542481931 |
| All opt (block 256, 8 threads)       | 40592229588 |

## Size: 5000x5000 ------ Sparsity: 0.1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 1343046333237 |
| Threaded (1 thread)                  | 1320048643167 |
| Threaded (8 threads)                 | 210350823427 |
| SIMD (1 thread)                      | 372178284309 |
| SIMD (8 threads)                     | 56852831214 |
| Cache (block 4, 1 thread)            | 781523377655 |
| Cache (block 4, 8 threads)           | 126022372762 |
| Cache (block 256, 1 thread)          | 512923559254 |
| Cache (block 256, 8 threads)         | 84988889043 |
| All opt (block 4, 1 thread)          | 440216510715 |
| All opt (block 4, 8 threads)         | 67129787617 |
| All opt (block 256, 1 thread)        | 249749553201 |
| All opt (block 256, 8 threads)       | 41144247714 |

## Size: 5000x5000 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 1430880163363 |
| Threaded (1 thread)                  | 1324387183422 |
| Threaded (8 threads)                 | 211876149713 |
| SIMD (1 thread)                      | 366898119681 |
| SIMD (8 threads)                     | 56709213701 |
| Cache (block 4, 1 thread)            | 779280018999 |
| Cache (block 4, 8 threads)           | 125732449936 |
| Cache (block 256, 1 thread)          | 511575004381 |
| Cache (block 256, 8 threads)         | 84199395962 |
| All opt (block 4, 1 thread)          | 439279406746 |
| All opt (block 4, 8 threads)         | 68176254119 |
| All opt (block 256, 1 thread)        | 249144713854 |
| All opt (block 256, 8 threads)       | 41362833171 |


## Size: 1500x1500 ------ Sparsity: 0.001
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 18329511827 |
| Threaded (1 thread)                  | 18583408465 |
| Threaded (4 threads)                 | 5575850388 |
| Threaded (8 threads)                 | 3419374103 |
| Threaded (16 threads)                | 2254560222 |
| SIMD (1 thread)                      | 8493450178 |
| SIMD (4 threads)                     | 1949281620 |
| SIMD (8 threads)                     | 1128732464 |
| SIMD (16 threads)                    | 663667273 |
| Cache (block 4, 1 thread)            | 20540235109 |
| Cache (block 4, 4 threads)           | 6660398888 |
| Cache (block 4, 8 threads)           | 3663623313 |
| Cache (block 4, 16 threads)          | 2318903710 |
| Cache (block 64, 1 thread)           | 14291121873 |
| Cache (block 64, 4 threads)          | 4581064568 |
| Cache (block 64, 8 threads)          | 2457427908 |
| Cache (block 64, 16 threads)         | 1555444438 |
| Cache (block 256, 1 thread)          | 13162004613 |
| Cache (block 256, 4 threads)         | 4155295211 |
| Cache (block 256, 8 threads)         | 2382691491 |
| Cache (block 256, 16 threads)        | 1537721446 |
| All opt (block 4, 1 thread)          | 10812710782 |
| All opt (block 4, 4 threads)         | 2984167927 |
| All opt (block 4, 8 threads)         | 1836703237 |
| All opt (block 4, 16 threads)        | 1095735302 |
| All opt (block 64, 1 thread)         | 6833048365 |
| All opt (block 64, 4 threads)        | 2080425870 |
| All opt (block 64, 8 threads)        | 1360034114 |
| All opt (block 64, 16 threads)       | 788968111 |
| All opt (block 256, 1 thread)        | 6751063658 |
| All opt (block 256, 4 threads)       | 2201292179 |
| All opt (block 256, 8 threads)       | 1340225000 |
| All opt (block 256, 16 threads)      | 758069547 |

## Size: 1500x1500 ------ Sparsity: 1
| Method                               | Time (ns) |
|--------------------------------------|-----------|
| Unoptimized                          | 19152020992 |
| Threaded (1 thread)                  | 19164103908 |
| Threaded (4 threads)                 | 5684584017 |
| Threaded (8 threads)                 | 3600435452 |
| Threaded (16 threads)                | 2204224696 |
| SIMD (1 thread)                      | 8166334411 |
| SIMD (4 threads)                     | 1779175801 |
| SIMD (8 threads)                     | 1191627372 |
| SIMD (16 threads)                    | 625041829 |
| Cache (block 4, 1 thread)            | 20300634898 |
| Cache (block 4, 4 threads)           | 6386601375 |
| Cache (block 4, 8 threads)           | 3712936984 |
| Cache (block 4, 16 threads)          | 2302530229 |
| Cache (block 64, 1 thread)           | 14201716710 |
| Cache (block 64, 4 threads)          | 4519727880 |
| Cache (block 64, 8 threads)          | 2455732546 |
| Cache (block 64, 16 threads)         | 1616063442 |
| Cache (block 256, 1 thread)          | 13189234596 |
| Cache (block 256, 4 threads)         | 3844555463 |
| Cache (block 256, 8 threads)         | 2445090991 |
| Cache (block 256, 16 threads)        | 1517847163 |
| All opt (block 4, 1 thread)          | 10609443832 |
| All opt (block 4, 4 threads)         | 3020918619 |
| All opt (block 4, 8 threads)         | 1771642464 |
| All opt (block 4, 16 threads)        | 1112568429 |
| All opt (block 64, 1 thread)         | 6962445036 |
| All opt (block 64, 4 threads)        | 2054992694 |
| All opt (block 64, 8 threads)        | 1422904114 |
| All opt (block 64, 16 threads)       | 774708914 |
| All opt (block 256, 1 thread)        | 6633971572 |
| All opt (block 256, 4 threads)       | 1996348486 |
| All opt (block 256, 8 threads)       | 1214106681 |
| All opt (block 256, 16 threads)      | 728319030 |

## Size: 1000x1000 ------ Sparsity: 0.01 * 1
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

## Size: 1000x1000 ------ Sparsity: 0.05 * 0.5
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

## Size: 1000x1000 ------ Sparsity: 0.1 * 0.9
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

## Size: 1500x1500 ------ Sparsity: 0.01 * 1
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

## Size: 1500x1500 ------ Sparsity: 0.05 * 0.5
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

## Size: 1500x1500 ------ Sparsity: 0.1 * 0.9
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

## Size: 500x500 ------ Sparsity: 0.01 * 1
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

## Size: 500x500 ------ Sparsity: 0.05 * 0.5
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

## Size: 500x500 ------ Sparsity: 0.1 * 0.9
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
