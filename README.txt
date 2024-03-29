list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Cassie mainly implemented LRU, and Tiana mainly implemented FIFO. The rest is split amoung us.
Both Cassie and Tianai did relatively equal amounts of work and effort.

Best Cache Experiment:
To identify the cache configuration offering the highest overall effectiveness, we conducted a series 
of tests focusing on different aspects such as hit rates, miss penalties, and total cache size using 
the file gcc.trace. This file was selected for its substantial size and complexity, providing a robust
dataset to mitigate and rule out outliers.

Our tests encompassed both direct-mapped and set-associative caches, with the latter further 
divided into 2-way, 4-way, and 8-way set-associative configurations. For the direct-mapped cache analysis, 
we explored variations in write policies, including write-allocate with write-back, write-allocate with 
write-through, and no-write-allocate with write-back. Given that direct-mapped caches do not employ eviction 
strategies, both FIFO and LRU replacement policies yielded the same outcomes for these tests.

For the set-associative caches, we assessed performance impacts under different replacement 
policies (LRU and FIFO) and write policies (write-allocate and write-back, write-allocate and write-through, 
no-write-allocate and write-back). This maintains that there is only one variable change at a time to 
control variables.

When comparing different results across the tests, we have found that write-allocate combined with 
write-back policy consistently resulted in lower total cycle counts compared to the alternatives, indicating 
superior efficiency in handling writes to the cache. In addition, increasing the level of associativity (number of ways) 
tends to reduce total cycle counts, supporting the premise that higher associativity can enhance cache 
performance by reducing conflict misses. However, it's important to note that while increased associativity 
can lower cycle counts by improving hit rates, it also introduces greater hardware complexity and potential 
access time penalties due to more extensive search and comparison operations within a set. The comparison 
between LRU and FIFO demonstrated that LRU typically results in fewer total cycles, suggesting it is more 
effective at managing cache evictions to preserve useful data.

In conclusion, the optimal cache configuration for achieving the best overall effectiveness in our tests, 
characterized by reduced cycle counts and improved performance, was found with higher associativity levels, 
employing a write-allocate plus write-back policy, and utilizing the LRU replacement strategy.

Direct Mapping
FIFO and LRU yields the same result here since direct mapping does not use eviction.
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 298863
Load misses: 19334
Store hits: 185202
Store misses: 12284
Total cycles: 20280865

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 298863
Load misses: 19334
Store hits: 185202
Store misses: 12284
Total cycles: 31466263

no-write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 296251
Load misses: 21946
Store hits: 158894
Store misses: 38592
Total cycles: 28823251
___________________________________________________________________

Set-Associative Caches:

With LRU
2-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 313059
Load misses: 5138
Store hits: 187779
Store misses: 9707
Total cycles: 10704438

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 313059
Load misses: 5138
Store hits: 187779
Store misses: 9707
Total cycles: 25028959

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 310059
Load misses: 8138
Store hits: 163941
Store misses: 33545
Total cycles: 23313859
______________________________________

4-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 9331848

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 24193798

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 311613
Load misses: 6584
Store hits: 164819
Store misses: 32667
Total cycles: 22693813
______________________________________

8-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 315261
Load misses: 2936
Store hits: 188513
Store misses: 8973
Total cycles: 8550574

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 315261
Load misses: 2936
Store hits: 188513
Store misses: 8973
Total cycles: 23930161

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 311937
Load misses: 6260
Store hits: 165155
Store misses: 32331
Total cycles: 22564537
______________________________________
___________________________________________________

With FIFO
2-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 312298
Load misses: 5899
Store hits: 187483
Store misses: 10003
Total cycles: 11367381

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 312298
Load misses: 5899
Store hits: 187483
Store misses: 10003
Total cycles: 25421398

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 309320
Load misses: 8877
Store hits: 162878
Store misses: 34608
Total cycles: 23608720
______________________________________

4-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 9831818

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 24504871

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 311017
Load misses: 7180
Store hits: 163705
Store misses: 33781
Total cycles: 22931617
______________________________________

8-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 314928
Load misses: 3269
Store hits: 188417
Store misses: 9069
Total cycles: 8817745

write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 314928
Load misses: 3269
Store hits: 188417
Store misses: 9069
Total cycles: 24091828

no-write-allocate and write-through
Total loads: 318197
Total stores: 197486
Load hits: 311649
Load misses: 6548
Store hits: 164824
Store misses: 32662
Total cycles: 22679449
______________________________________
___________________________________________________
___________________________________________________________________


Set-Associative Caches:

With LRU
2-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.971213
Miss Penalties: 267610900 cycles
Average Access Time: 7.70373e+06 cycles
Total Cache Size (including overhead): 19456 bits

write-allocate and write-through
Hit Rates: 0.971213
Miss Penalties: 625723900 cycles
Average Access Time: 1.80128e+07 cycles
Total Cache Size (including overhead): 19456 bits

no-write-allocate and write-through
Hit Rates: 0.919169
Miss Penalties: 582846400 cycles
Average Access Time: 4.71119e+07 cycles
Total Cache Size (including overhead): 19456 bits
______________________________________

4-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.975499
Miss Penalties: 233296200 cycles
Average Access Time: 5.7161e+06 cycles
Total Cache Size (including overhead): 38912 bits

write-allocate and write-through
Hit Rates: 0.975499
Miss Penalties: 604844900 cycles
Average Access Time: 1.48196e+07 cycles
Total Cache Size (including overhead): 38912 bits

no-write-allocate and write-through
Hit Rates: 0.923885
Miss Penalties: 567345300 cycles
Average Access Time: 4.31833e+07 cycles
Total Cache Size (including overhead): 38912 bits
______________________________________

8-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.976906
Miss Penalties: 213764300 cycles
Average Access Time: 4.9366e+06 cycles
Total Cache Size (including overhead): 77824 bits

write-allocate and write-through
Hit Rates: 0.976906
Miss Penalties: 598254000 cycles
Average Access Time: 1.38159e+07 cycles
Total Cache Size (including overhead): 77824 bits

no-write-allocate and write-through
Hit Rates: 0.925165
Miss Penalties: 564113400 cycles
Average Access Time: 4.22153e+07 cycles
Total Cache Size (including overhead): 77824 bits
______________________________________
___________________________________________________

With FIFO
2-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.969163
Miss Penalties: 284184500 cycles
Average Access Time: 8.76333e+06 cycles
Total Cache Size (including overhead): 19456 bits

write-allocate and write-through
Hit Rates: 0.969163
Miss Penalties: 635534900 cycles
Average Access Time: 1.95978e+07 cycles
Total Cache Size (including overhead): 19456 bits

no-write-allocate and write-through
Hit Rates: 0.915675
Miss Penalties: 590218000 cycles
Average Access Time: 4.97702e+07 cycles
Total Cache Size (including overhead): 19456 bits
______________________________________

4-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.973889
Miss Penalties: 245795400 cycles
Average Access Time: 6.41797e+06 cycles
Total Cache Size (including overhead): 38912 bits

write-allocate and write-through
Hit Rates: 0.973889
Miss Penalties: 612621700 cycles
Average Access Time: 1.59962e+07 cycles
Total Cache Size (including overhead): 38912 bits

no-write-allocate and write-through
Hit Rates: 0.920569
Miss Penalties: 573290400 cycles
Average Access Time: 4.55368e+07 cycles
Total Cache Size (including overhead): 38912 bits
______________________________________

8-way set-associative cache:
write-allocate and write-back
Hit Rates: 0.976074
Miss Penalties: 220443600 cycles
Average Access Time: 5.27424e+06 cycles
Total Cache Size (including overhead): 77824 bits

write-allocate and write-through
Hit Rates: 0.976074
Miss Penalties: 602295700 cycles
Average Access Time: 1.44103e+07 cycles
Total Cache Size (including overhead): 77824 bits

no-write-allocate and write-through
Hit Rates: 0.923965
Miss Penalties: 566986200 cycles
Average Access Time: 4.31108e+07 cycles
Total Cache Size (including overhead): 77824 bits
______________________________________