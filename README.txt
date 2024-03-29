list team members, document who did what, discuss
anything interesting about your implementation.

Team members: Cassie Zhang xzhan304, Tianai Yue tyue4

Cassie mainly implemented LRU, and Tiana mainly implemented FIFO. The rest is split amoung us.
Both Cassie and Tianai did relatively equal amounts of work and effort.

Best Cache Experiment:
Result: We think that the optimal cache configuration for achieving the best overall effectiveness 
with 512 2 8 write-allocate write-back lru.

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

Fully Associative
./csim 1 64 4 no-write-allocate write-through lru < traces/gcc.trace
Total cycles: 23820877
Hit Rate: 82.9556%
Miss Rate: 17.0444%
Miss Penalty: 100 cycles
Average Access Time: 17.8739 cycles
Cache Associativity: 64
Total Cache Size: 2048 bytes

./csim 1 64 4 no-write-allocate write-through fifo < traces/gcc.trace
Total cycles: 24909580
Hit Rate: 79.8584%
Miss Rate: 20.1416%
Miss Penalty: 100 cycles
Average Access Time: 20.9402 cycles
Cache Associativity: 64
Total Cache Size: 2048 bytes

./csim 1 1 4 no-write-allocate write-through lru < traces/gcc.trace
Total cycles: 50539096
Hit Rate: 5.16655%
Miss Rate: 94.8335%
Miss Penalty: 100 cycles
Average Access Time: 94.8851 cycles
Cache Associativity: 1
Total Cache Size: 32 bytes

./csim 1 1 4 no-write-allocate write-through fifo < traces/gcc.trace
Total cycles: 50539096
Hit Rate: 5.16655%
Miss Rate: 94.8335%
Miss Penalty: 100 cycles
Average Access Time: 94.8851 cycles
Cache Associativity: 1
Total Cache Size: 32 bytes

Number of sets in the cache: 256 
number of bytes in each block: 16

Direct Mapping
FIFO and LRU yields the same result here since direct mapping does not use eviction.
write-allocate and write-back
./csim 256 1 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 20280865
Hit Rate: 93.8687%
Miss Rate: 6.13129%
Miss Penalty: 400 cycles
Average Access Time: 25.4638 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes

write-allocate and write-through
./csim 256 1 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 31466263
Hit Rate: 93.8687%
Miss Rate: 6.13129%
Miss Penalty: 400 cycles
Average Access Time: 25.4638 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes

no-write-allocate and write-back
./csim 256 1 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 20280865
Hit Rate: 93.8687%
Miss Rate: 6.13129%
Miss Penalty: 400 cycles
Average Access Time: 25.4638 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes
___________________________________________________________________

Set-Associative Caches:

With LRU
2-way set-associative cache:
write-allocate and write-back
./csim 256 2 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 10704438
Hit Rate: 97.1213%
Miss Rate: 2.87871%
Miss Penalty: 400 cycles
Average Access Time: 12.486 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 256 2 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 25028959
Hit Rate: 97.1213%
Miss Rate: 2.87871%
Miss Penalty: 400 cycles
Average Access Time: 12.486 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 256 2 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 23313859
Hit Rate: 91.9169%
Miss Rate: 8.08307%
Miss Penalty: 400 cycles
Average Access Time: 33.2514 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 256 4 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 9331848
Hit Rate: 97.5499%
Miss Rate: 2.45015%
Miss Penalty: 400 cycles
Average Access Time: 10.7761 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

write-allocate and write-through
./csim 256 4 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 24193798
Hit Rate: 97.5499%
Miss Rate: 2.45015%
Miss Penalty: 400 cycles
Average Access Time: 10.7761 cycles
Cache Associativity: 4

no-write-allocate and write-through
./csim 256 4 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22693813
Hit Rate: 92.3885%
Miss Rate: 7.61146%
Miss Penalty: 400 cycles
Average Access Time: 31.3697 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 256 8 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 8550574
Hit Rate: 97.6906%
Miss Rate: 2.30936%
Miss Penalty: 400 cycles
Average Access Time: 10.2144 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

write-allocate and write-through
./csim 256 8 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 23930161
Hit Rate: 97.6906%
Miss Rate: 2.30936%
Miss Penalty: 400 cycles
Average Access Time: 10.2144 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

no-write-allocate and write-through
./csim 256 8 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22564537
Hit Rate: 92.5165%
Miss Rate: 7.48347%
Miss Penalty: 400 cycles
Average Access Time: 30.8591 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes
______________________________________
___________________________________________________

With FIFO
2-way set-associative cache:
write-allocate and write-back
./csim 256 2 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 11367381
Hit Rate: 96.9163%
Miss Rate: 3.08368%
Miss Penalty: 400 cycles
Average Access Time: 13.3039 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 256 2 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 25421398
Hit Rate: 96.9163%
Miss Rate: 3.08368%
Miss Penalty: 400 cycles
Average Access Time: 13.3039 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 256 2 16 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 23608720
Hit Rate: 91.5675%
Miss Rate: 8.43251%
Miss Penalty: 400 cycles
Average Access Time: 34.6457 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 256 4 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 9831818
Hit Rate: 97.3889%
Miss Rate: 2.6111%
Miss Penalty: 400 cycles
Average Access Time: 11.4183 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

write-allocate and write-through
./csim 256 4 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 24504871
Hit Rate: 97.3889%
Miss Rate: 2.6111%
Miss Penalty: 400 cycles
Average Access Time: 11.4183 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

no-write-allocate and write-through
./csim 256 4 16 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 22931617
Hit Rate: 92.0569%
Miss Rate: 7.94306%
Miss Penalty: 400 cycles
Average Access Time: 32.6928 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 256 8 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 8817745
Hit Rate: 97.6074%
Miss Rate: 2.39256%
Miss Penalty: 400 cycles
Average Access Time: 10.5463 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

write-allocate and write-through
./csim 256 8 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 24091828
Hit Rate: 97.6074%
Miss Rate: 2.39256%
Miss Penalty: 400 cycles
Average Access Time: 10.5463 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

no-write-allocate and write-through
./csim 256 8 16 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 22679449
Hit Rate: 92.3965%
Miss Rate: 7.60351%
Miss Penalty: 400 cycles
Average Access Time: 31.338 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes
______________________________________
___________________________________________________
___________________________________________________________________

Number of sets in the cache: 256 
number of bytes in each block: 4

Direct Mapping
FIFO and LRU yields the same result here since direct mapping does not use eviction.

write-allocate and write-back
./csim 256 1 4 write-allocate write-back lru <traces/gcc.trace
Total cycles: 15949698
Hit Rate: 80.9214%
Miss Rate: 19.0786%
Miss Penalty: 100 cycles
Average Access Time: 19.8878 cycles
Cache Associativity: 1
Total Cache Size: 32 bytes

write-allocate and write-through
./csim 256 1 4 write-allocate write-through lru <traces/gcc.trace
Total cycles: 25463287
Hit Rate: 80.9214%
Miss Rate: 19.0786%
Miss Penalty: 100 cycles
Average Access Time: 19.8878 cycles
Cache Associativity: 1
Total Cache Size: 32 bytes

no-write-allocate and write-back
./csim 256 1 4 write-allocate write-back lru <traces/gcc.trace
Total cycles: 15949698
Hit Rate: 80.9214%
Miss Rate: 19.0786%
Miss Penalty: 100 cycles
Average Access Time: 19.8878 cycles
Cache Associativity: 1
Total Cache Size: 32 bytes
___________________________________________________________________

Set-Associative Caches:

With LRU
2-way set-associative cache:
write-allocate and write-back
./csim 256 2 4 write-allocate write-back lru <traces/gcc.trace
Total cycles: 8734821
Hit Rate: 90.6218%
Miss Rate: 9.37824%
Miss Penalty: 100 cycles
Average Access Time: 10.2845 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes

write-allocate and write-through
./csim 256 2 4 write-allocate write-through lru <traces/gcc.trace
Total cycles: 21760489
Hit Rate: 90.6218%
Miss Rate: 9.37824%
Miss Penalty: 100 cycles
Average Access Time: 10.2845 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes

no-write-allocate and write-through
./csim 256 2 4 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22082041
Hit Rate: 87.7803%
Miss Rate: 12.2197%
Miss Penalty: 100 cycles
Average Access Time: 13.0975 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 256 4 4 write-allocate write-back lru <traces/gcc.trace
Total cycles: 7150535
Hit Rate: 92.8739%
Miss Rate: 7.12608%
Miss Penalty: 100 cycles
Average Access Time: 8.05482 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes

write-allocate and write-through
./csim 256 4 4 write-allocate write-through lru <traces/gcc.trace
Total cycles: 20853847
Hit Rate: 92.8739%
Miss Rate: 7.12608%
Miss Penalty: 100 cycles
Average Access Time: 8.05482 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes

no-write-allocate and write-through
./csim 256 4 4 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 21234205
Hit Rate: 90.2318%
Miss Rate: 9.76821%
Miss Penalty: 100 cycles
Average Access Time: 10.6705 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 256 8 4 write-allocate write-back lru <traces/gcc.trace
Total cycles: 6727015
Hit Rate: 93.3548%
Miss Rate: 6.64517%
Miss Penalty: 100 cycles
Average Access Time: 7.57872 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 256 8 4 write-allocate write-through lru <traces/gcc.trace
Total cycles: 20683072
Hit Rate: 93.3548%
Miss Rate: 6.64517%
Miss Penalty: 100 cycles
Average Access Time: 7.57872 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 256 8 4 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 21079072
Hit Rate: 90.6805%
Miss Rate: 9.31949%
Miss Penalty: 100 cycles
Average Access Time: 10.2263 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes
______________________________________
___________________________________________________

With FIFO
2-way set-associative cache:
write-allocate and write-back
./csim 256 2 4 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 9286075
Hit Rate: 89.9729%
Miss Rate: 10.0271%
Miss Penalty: 100 cycles
Average Access Time: 10.9268 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes

write-allocate and write-through
./csim 256 2 4 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 21987793
Hit Rate: 89.9729%
Miss Rate: 10.0271%
Miss Penalty: 100 cycles
Average Access Time: 10.9268 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes

no-write-allocate and write-through
./csim 256 2 4 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 22270141
Hit Rate: 87.0139%
Miss Rate: 12.9861%
Miss Penalty: 100 cycles
Average Access Time: 13.8562 cycles
Cache Associativity: 2
Total Cache Size: 64 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 256 4 4 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 7628611
Hit Rate: 92.2875%
Miss Rate: 7.71249%
Miss Penalty: 100 cycles
Average Access Time: 8.63537 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes

write-allocate and write-through
./csim 256 4 4 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 21056203
Hit Rate: 92.2875%
Miss Rate: 7.71249%
Miss Penalty: 100 cycles
Average Access Time: 8.63537 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes

no-write-allocate and write-through
./csim 256 4 4 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 21390526
Hit Rate: 89.6345%
Miss Rate: 10.3655%
Miss Penalty: 100 cycles
Average Access Time: 11.2618 cycles
Cache Associativity: 4
Total Cache Size: 128 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 256 8 4 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 7006549
Hit Rate: 93.0124%
Miss Rate: 6.98763%
Miss Penalty: 100 cycles
Average Access Time: 7.91775 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 256 8 4 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 20799595
Hit Rate: 93.0124%
Miss Rate: 6.98763%
Miss Penalty: 100 cycles
Average Access Time: 7.91775 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 256 8 4 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 21173617
Hit Rate: 90.3359%
Miss Rate: 9.66408%
Miss Penalty: 100 cycles
Average Access Time: 10.5674 cycles
Cache Associativity: 8
Total Cache Size: 256 bytes
______________________________________
___________________________________________________
___________________________________________________________________


Number of sets in the cache: 512
number of bytes in each block: 16


Direct Mapping
FIFO and LRU yields the same result here since direct mapping does not use eviction.
write-allocate and write-back
./csim 512 1 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 14447824
Hit Rate: 95.8387%
Miss Rate: 4.16128%
Miss Penalty: 400 cycles
Average Access Time: 17.6035 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes

write-allocate and write-through
./csim 512 1 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 27512218
Hit Rate: 95.8387%
Miss Rate: 4.16128%
Miss Penalty: 400 cycles
Average Access Time: 17.6035 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes

no-write-allocate and write-back
./csim 512 1 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 14447824

Hit Rate: 95.8387%
Miss Rate: 4.16128%
Miss Penalty: 400 cycles
Average Access Time: 17.6035 cycles
Cache Associativity: 1
Total Cache Size: 128 bytes
___________________________________________________________________

Set-Associative Caches:

With LRU
2-way set-associative cache:
write-allocate and write-back
./csim 512 2 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 9575777
Hit Rate: 97.4585%
Miss Rate: 2.54148%
Miss Penalty: 400 cycles
Average Access Time: 11.1405 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 512 2 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 24369253
Hit Rate: 97.4585%
Miss Rate: 2.54148%
Miss Penalty: 400 cycles
Average Access Time: 11.1405 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 512 2 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22845034
Hit Rate: 92.239%
Miss Rate: 7.76097%
Miss Penalty: 400 cycles
Average Access Time: 31.9663 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 512 4 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 8595679
Hit Rate: 97.6722%
Miss Rate: 2.32779%
Miss Penalty: 400 cycles
Average Access Time: 10.2879 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

write-allocate and write-through
./csim 512 4 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 23963611
Hit Rate: 97.6722%
Miss Rate: 2.32779%
Miss Penalty: 400 cycles
Average Access Time: 10.2879 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

no-write-allocate and write-through
./csim 512 4 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22583290
Hit Rate: 92.4892%
Miss Rate: 7.51082%
Miss Penalty: 400 cycles
Average Access Time: 30.9682 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 512 8 16 write-allocate write-back lru <traces/gcc.trace
Total cycles: 7598100
Hit Rate: 97.7539%
Miss Rate: 2.24615%
Miss Penalty: 400 cycles
Average Access Time: 9.96213 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

write-allocate and write-through
./csim 512 8 16 write-allocate write-through lru <traces/gcc.trace
Total cycles: 23805037
Hit Rate: 97.7539%
Miss Rate: 2.24615%
Miss Penalty: 400 cycles
Average Access Time: 9.96213 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

no-write-allocate and write-through
./csim 512 8 16 no-write-allocate write-through lru <traces/gcc.trace
Total cycles: 22486333
Hit Rate: 92.5644%
Miss Rate: 7.43558%
Miss Penalty: 400 cycles
Average Access Time: 30.6679 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes
______________________________________
___________________________________________________

With FIFO
2-way set-associative cache:
write-allocate and write-back
./csim 512 2 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 10009078
Hit Rate: 97.323%
Miss Rate: 2.67703%
Miss Penalty: 400 cycles
Average Access Time: 11.6814 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

write-allocate and write-through
./csim 512 2 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 24629443
Hit Rate: 97.323%
Miss Rate: 2.67703%
Miss Penalty: 400 cycles
Average Access Time: 11.6814 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes

no-write-allocate and write-through
./csim 512 2 16 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 23030569
Hit Rate: 91.9689%
Miss Rate: 8.0311%
Miss Penalty: 400 cycles
Average Access Time: 33.0441 cycles
Cache Associativity: 2
Total Cache Size: 256 bytes
______________________________________

4-way set-associative cache:
write-allocate and write-back
./csim 512 4 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 8862842
Hit Rate: 97.5875%
Miss Rate: 2.41253%
Miss Penalty: 400 cycles
Average Access Time: 10.626 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

write-allocate and write-through
./csim 512 4 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 24127876
Hit Rate: 97.5875%
Miss Rate: 2.41253%
Miss Penalty: 400 cycles
Average Access Time: 10.626 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes

no-write-allocate and write-through
./csim 512 4 16 no-write-allocate write-through fifo <traces/gcc.trace
Total cycles: 22706980
Hit Rate: 92.3575%
Miss Rate: 7.64249%
Miss Penalty: 400 cycles
Average Access Time: 31.4935 cycles
Cache Associativity: 4
Total Cache Size: 512 bytes
______________________________________

8-way set-associative cache:
write-allocate and write-back
./csim 512 8 16 write-allocate write-back fifo <traces/gcc.trace
Total cycles: 7754661
Hit Rate: 97.7075%
Miss Rate: 2.29249%
Miss Penalty: 400 cycles
Average Access Time: 10.147 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

write-allocate and write-through
./csim 512 8 16 write-allocate write-through fifo <traces/gcc.trace
Total cycles: 23894854
Hit Rate: 97.7075%
Miss Rate: 2.29249%
Miss Penalty: 400 cycles
Average Access Time: 10.147 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes

no-write-allocate and write-through
Total cycles: 22544986
Hit Rate: 92.5148%
Miss Rate: 7.48522%
Miss Penalty: 400 cycles
Average Access Time: 30.866 cycles
Cache Associativity: 8
Total Cache Size: 1024 bytes
______________________________________
___________________________________________________
___________________________________________________________________

