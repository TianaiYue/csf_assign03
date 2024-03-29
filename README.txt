list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Both Cassie and Tianai did relatively equal amounts of work and effort.

In our cache simulation, getting the cycle counts spot-on boils down to how meticulously we handle 
the intricacies, especially for cache misses where we need to factor in the extra cycles for fetching 
and potentially evicting blocks. For hits, it's crucial that we count them precisely. It's really about 
us keeping an eye on these finer details to ensure our simulator reflects real-world cache performance accurately.

Experiment Description:
This experiment is to evaluate the effectiveness of two cache eviction policies, LRU and FIFO, across a diverse set of 
memory trace files. The objective was to determine which eviction policy provides better overall cache performance in 
terms of hit rates, miss penalties, and total execution cycles. 

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