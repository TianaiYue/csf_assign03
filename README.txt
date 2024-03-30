list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Cassie mainly implemented LRU, and Tiana mainly implemented FIFO. The rest is split amoung us.
Both Cassie and Tianai did relatively equal amounts of work and effort.

Best Cache Experiment:

Result: We chose a cache size of cache size of 16,384 bytes(16KB), and the best overall effectiveness
is  

To identify the cache configuration offering the highest overall effectiveness, we conducted a series 
of tests focusing on different aspects such as hit rates, miss penalties, total cache size, average 
access time and total cycles using the file gcc.trace. This file was selected for its substantial 
size and complexity, providing a robust dataset to mitigate and rule out outliers.

Our tests encompassed both direct-mapped and set-associative caches(2-way, 4-way, and 8-way set-associative 
configurations), coupled with variations in write policies, including write-allocate with write-back, 
write-allocate with write-through, and no-write-allocate with write-back, also coupled with eviction 
strategies between both FIFO and LRU.

With all other variables held equal, we preformed the below tests to find the optimal cache configuration:
During our tests, we made sure that there is only one variable change at a time to control variables.
We compared number of sets in cache between 256 and 512 and found that by increasing the number of sets
the hit rate increases, total cycle count decreases and average access time decreases.
We compared different ways of set-associative and found that by increasing the number of sets
the hit rate increases, total cycle count decreases and average access time decreases, but the cache size
also increases, so we chose to have a relatively small set-associative of 2 so that less hardware is needed
to preform a relatively same amount of hit rate, total cycle count and average access time.
We compared different number of bytes in block, and found that by increasing the number of sets
the hit rate increases, total cycle count decreases and average access time decreases, but the cache size
also increases, so we chose to have 8 bytes per block so that less hardware is needed to preform a 
relatively same amount of hit rate, total cycle count and average access time.
We compared different write policies and found that write-allocate with write-back yields higher hit rate,
smaller total cycle count and less average access time.
We compared LRU to FIFO, and concluded that LRU yields a higher hit rate, less total cycle count and less
average access time.

Taking into account of hit rates, miss penalties, total cache size, average access time and total cycles and
also concidering a smaller total cache size, we concluded that the combination of 512 2 8 write-allocate write-back lru
is an optimal cache configuration.

Tests preform:

Direct Mapping
FIFO and LRU yields the same result here since direct mapping does not use eviction.
./csim 256 1 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 22603961
Total Cache Size: 16384 bytes
Cache Associativity: 1
Hit Rate: 98.1923%
Miss Rate: 1.8077%
Miss Penalty: 1600 cycles
Average Access Time: 29.9051 cycles

./csim 256 1 64 write-allocate write-through lru < traces/gcc.trace
Total cycles: 34633897
Total Cache Size: 16384 bytes
Cache Associativity: 1
Hit Rate: 98.1923%
Miss Rate: 1.8077%
Miss Penalty: 1600 cycles
Average Access Time: 29.9051 cycles

./csim 256 1 64 no-write-allocate write-through lru < traces/gcc.trace
Total cycles: 31211827
Total Cache Size: 16384 bytes
Cache Associativity: 1
Hit Rate: 93.144%
Miss Rate: 6.85596%
Miss Penalty: 1600 cycles
Average Access Time: 110.627 cycles

From these tests we can see that "write-allocate write-back" have lower cycle counts and higher
hit rates than "write-allocate write-through" and "no-write-allocate write-through".
___________________________________________________________________

Fully Associative
./csim 1 256 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12415250
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.1404%
Miss Rate: 0.859637%
Miss Penalty: 1600 cycles
Average Access Time: 14.7456 cycles

./csim 1 256 64 write-allocate write-back fifo < traces/gcc.trace
Total cycles: 13958570
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.0085%
Miss Rate: 0.991501%
Miss Penalty: 1600 cycles
Average Access Time: 16.8541 cycles

./csim 1 256 64 write-allocate write-through lru < traces/gcc.trace
Total cycles: 26895883
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.1404%
Miss Rate: 0.859637%
Miss Penalty: 1600 cycles
Average Access Time: 14.7456 cycles

./csim 1 256 64 write-allocate write-through fifo < traces/gcc.trace
Total cycles: 27972907
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.0085%
Miss Rate: 0.991501%
Miss Penalty: 1600 cycles
Average Access Time: 16.8541 cycles

./csim 1 256 64 no-write-allocate write-through lru < traces/gcc.trace
Total cycles: 24715090
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 94.6834%
Miss Rate: 5.31664%
Miss Penalty: 1600 cycles
Average Access Time: 86.013 cycles

./csim 1 256 64 no-write-allocate write-through fifo < traces/gcc.trace
Total cycles: 25600936
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 94.2963%
Miss Rate: 5.7037%
Miss Penalty: 1600 cycles
Average Access Time: 92.2021 cycles

Fully Associative
./csim 1 256 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12415250
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.1404%
Miss Rate: 0.859637%
Miss Penalty: 1600 cycles
Average Access Time: 14.7456 cycles

From these tests we can see that "lru" has a smaller total cycle count, higher hit
rate, and less average access time than "fifo".
___________________________________________________________________
Set-Associative Caches:
2-way set-associative cache:
./csim 128 2 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 14809325
Total Cache Size: 16384 bytes
Cache Associativity: 2
Hit Rate: 98.9222%
Miss Rate: 1.07779%
Miss Penalty: 1600 cycles
Average Access Time: 18.2339 cycles

4-way set-associative cache:
./csim 64 4 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 13045378
Total Cache Size: 16384 bytes
Cache Associativity: 4
Hit Rate: 99.0876%
Miss Rate: 0.912382%
Miss Penalty: 1600 cycles
Average Access Time: 15.589 cycles

8-way set-associative cache:
./csim 32 8 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12568778
Total Cache Size: 16384 bytes
Cache Associativity: 8
Hit Rate: 99.1264%
Miss Rate: 0.873599%
Miss Penalty: 1600 cycles
Average Access Time: 14.9688 cycles

16-way set-associative cache:
./csim 16 16 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12492015
Total Cache Size: 16384 bytes
Cache Associativity: 16
Hit Rate: 99.1336%
Miss Rate: 0.866424%
Miss Penalty: 1600 cycles
Average Access Time: 14.8541 cycles

32-way set-associative cache:
./csim 8 32 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12500016
Total Cache Size: 16384 bytes
Cache Associativity: 32
Hit Rate: 99.1338%
Miss Rate: 0.86623%
Miss Penalty: 1600 cycles
Average Access Time: 14.851 cycles

From theses tests we can see that fully associative cache has
the least total cycle count, the highest hit rate and the least
average access time.
___________________________________________________________________

./csim 1 16 1024 write-allocate write-back lru < traces/gcc.trace
Total cycles: 342572689
Total Cache Size: 16384 bytes
Cache Associativity: 16
Hit Rate: 98.0232%
Miss Rate: 1.9768%
Miss Penalty: 25600 cycles
Average Access Time: 507.04 cycles

./csim 1 32 512 write-allocate write-back lru < traces/gcc.trace
Total cycles: 82149295
Total Cache Size: 16384 bytes
Cache Associativity: 32
Hit Rate: 99.0715%
Miss Rate: 0.928477%
Miss Penalty: 12800 cycles
Average Access Time: 119.836 cycles

./csim 1 64 256 write-allocate write-back lru < traces/gcc.trace
Total cycles: 26605831
Total Cache Size: 16384 bytes
Cache Associativity: 64
Hit Rate: 99.4857%
Miss Rate: 0.514269%
Miss Penalty: 6400 cycles
Average Access Time: 33.9081 cycles

./csim 1 128 128 write-allocate write-back lru < traces/gcc.trace
Total cycles: 16877315
Total Cache Size: 16384 bytes
Cache Associativity: 128
Hit Rate: 99.3857%
Miss Rate: 0.614331%
Miss Penalty: 3200 cycles
Average Access Time: 20.6524 cycles

./csim 1 256 64 write-allocate write-back lru < traces/gcc.trace
Total cycles: 12415250
Total Cache Size: 16384 bytes
Cache Associativity: 256
Hit Rate: 99.1404%
Miss Rate: 0.859637%
Miss Penalty: 1600 cycles
Average Access Time: 14.7456 cycles

./csim 1 512 32 write-allocate write-back lru < traces/gcc.trace
Total cycles: 10337387
Total Cache Size: 16384 bytes
Cache Associativity: 512
Hit Rate: 98.624%
Miss Rate: 1.37604%
Miss Penalty: 800 cycles
Average Access Time: 11.9946 cycles

./csim 1 1024 16 write-allocate write-back lru < traces/gcc.trace
Total cycles: 9214473
Total Cache Size: 16384 bytes
Cache Associativity: 1024
Hit Rate: 97.5935%
Miss Rate: 2.40652%
Miss Penalty: 400 cycles
Average Access Time: 10.602 cycles


From these tests we can see that the best the performance of the cache, 
is characterized by 1 64 256 write-allocate write-back lru, compared to
other combinations, this has a lower total cycle counts, higher hit rate, 
and less average access time.
___________________________________________________________________