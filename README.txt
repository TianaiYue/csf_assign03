list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Cassie mainly implemented LRU, and Tiana mainly implemented FIFO. Both Cassie and Tianai did relatively equal amounts of work and effort.
In our cache simulation, getting the cycle counts spot-on boils down to how meticulously we handle 
the intricacies, especially for cache misses where we need to factor in the extra cycles for fetching 
and potentially evicting blocks. For hits, it's crucial that we count them precisely. It's really about 
us keeping an eye on these finer details to ensure our simulator reflects real-world cache performance accurately.

Experiment Description:
This experiment is to evaluate the effectiveness of two cache eviction policies, LRU and FIFO, across a diverse set of 
memory trace files. The objective was to determine which eviction policy provides better overall cache performance in 
terms of hit rates, miss penalties, and total execution cycles. 

Analysis:
LRU generally outperforms FIFO in complex traces like gcc.trace and swim.trace, evidenced by higher load hits and lower total cycles. 
This suggests LRU's effectiveness in managing temporal locality in access patterns. But for simpler traces(like read01 and others), 
the difference between LRU and FIFO is minimal, indicating that both policies perform comparably under straightforward access patterns.
Load operations exhibit high hit rates under both policies across all traces, indicating efficient data caching. Store operations, however, 
show more variability, with a noticeable number of misses in complex traces, suggesting potential areas for optimization in write policies.
The total cycles metric, indicative of cache efficiency, favors LRU for complex traces due to its ability to minimize unnecessary cache 
replacements, thereby enhancing performance.

Summary:
LRU slightly edges out FIFO in handling complex memory access patterns, as demonstrated in gcc.trace and swim.trace, by improving hit rates 
and reducing total cycles. For less complex workloads, both LRU and FIFO are viable, with negligible performance differences.


We ran gcc.trace and swim.trace across all variety of properties since they are the largest files and will show the result in a less biased way.
We also ran read01.trace, read02.trace and write01.trace, write02.trace across all files to compare the results when the input is short.


Experiment Result in LRU:
1. gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 9331848

2. read01.trace
Total loads: 5
Total stores: 0
Load hits: 2
Load misses: 3
Store hits: 0
Store misses: 0
Total cycles: 1202

3. read02.trace
Total loads: 10
Total stores: 0
Load hits: 9
Load misses: 1
Store hits: 0
Store misses: 0
Total cycles: 409

4. read03.trace
Total loads: 9
Total stores: 0
Load hits: 5
Load misses: 4
Store hits: 0
Store misses: 0
Total cycles: 1605

5. swim.trace
Total loads: 220668
Total stores: 82525
Load hits: 219507
Load misses: 1161
Store hits: 71956
Store misses: 10569
Total cycles: 8997863

6. write01.trace
Total loads: 0
Total stores: 5
Load hits: 0
Load misses: 0
Store hits: 2
Store misses: 3
Total cycles: 1202

7. write02.trace
Total loads: 0
Total stores: 10
Load hits: 0
Load misses: 0
Store hits: 9
Store misses: 1
Total cycles: 409


Experiment Result in FIFO:
1. gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 9831818

2. read01.trace
Total loads: 5
Total stores: 0
Load hits: 2
Load misses: 3
Store hits: 0
Store misses: 0
Total cycles: 1202

3. read02.trace
Total loads: 10
Total stores: 0
Load hits: 9
Load misses: 1
Store hits: 0
Store misses: 0
Total cycles: 409

4. read03.trace
Total loads: 9
Total stores: 0
Load hits: 5
Load misses: 4
Store hits: 0
Store misses: 0
Total cycles: 1605

5. swim.trace
Total loads: 220668
Total stores: 82525
Load hits: 218357
Load misses: 2311
Store hits: 71787
Store misses: 10738
Total cycles: 9642544

6. write01.trace
Total loads: 0
Total stores: 5
Load hits: 0
Load misses: 0
Store hits: 2
Store misses: 3
Total cycles: 1202

7. write02.trace
Total loads: 0
Total stores: 10
Load hits: 0
Load misses: 0
Store hits: 9
Store misses: 1
Total cycles: 409




gcc.trace

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

4-way set-associative cache:
write-allocate and write-back
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 9331848

##### write-allocate and write-through
./csim 256 4 16 write-allocate write-through lru <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 24193798

##### no-write-allocate and write-through
./csim 256 4 16 no-write-allocate write-through lru <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 311613
Load misses: 6584
Store hits: 164819
Store misses: 32667
Total cycles: 22693813

#### 8-way set-associative cache:
##### write-allocate and write-back
./csim 256 8 16 write-allocate write-back lru <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 315261
Load misses: 2936
Store hits: 188513
Store misses: 8973
Total cycles: 8550574

##### write-allocate and write-through
./csim 256 8 16 write-allocate write-through lru <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 315261
Load misses: 2936
Store hits: 188513
Store misses: 8973
Total cycles: 23930161

##### no-write-allocate and write-through
./csim 256 8 16 no-write-allocate write-through lru <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 311937
Load misses: 6260
Store hits: 165155
Store misses: 32331
Total cycles: 22564537

#### With FIFO
#### 2-way set-associative cache:
##### write-allocate and write-back
./csim 256 2 16 write-allocate write-back fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 312298
Load misses: 5899
Store hits: 187483
Store misses: 10003
Total cycles: 11367381

##### write-allocate and write-through
./csim 256 2 16 write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 312298
Load misses: 5899
Store hits: 187483
Store misses: 10003
Total cycles: 25421398

##### no-write-allocate and write-through
./csim 256 2 16 no-write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 309320
Load misses: 8877
Store hits: 162878
Store misses: 34608
Total cycles: 23608720

#### 4-way set-associative cache:
##### write-allocate and write-back
./csim 256 4 16 write-allocate write-back fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 9831818

##### write-allocate and write-through
./csim 256 4 16 write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 24504871

##### no-write-allocate and write-through
./csim 256 4 16 no-write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 311017
Load misses: 7180
Store hits: 163705
Store misses: 33781
Total cycles: 22931617

#### 8-way set-associative cache:
##### write-allocate and write-back
./csim 256 8 16 write-allocate write-back fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314928
Load misses: 3269
Store hits: 188417
Store misses: 9069
Total cycles: 8817745

##### write-allocate and write-through
./csim 256 8 16 write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 314928
Load misses: 3269
Store hits: 188417
Store misses: 9069
Total cycles: 24091828

##### no-write-allocate and write-through
./csim 256 8 16 no-write-allocate write-through fifo <traces/gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 311649
Load misses: 6548
Store hits: 164824
Store misses: 32662
Total cycles: 22679449
