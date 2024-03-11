/** 
 * A3MS2
 * Cassie Zhang xzhan304
 * Tianai Yue
 */
 
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <chrono>
#include <limits>
#include <cmath>


using namespace std;

struct Slot {
    uint32_t tag;
    bool valid;
    bool dirty;
    uint64_t load_ts, access_ts;
    uint64_t operationCounter;

    Slot() : tag(0), valid(false), dirty(false), load_ts(0), access_ts(0), operationCounter(0) {}
};

struct Set {
    vector<Slot> slots;

    explicit Set(int blocks_per_set) : slots(blocks_per_set) {}
};

struct Cache {
    vector<Set> sets;
    int blocks_per_set;
    int num_bytes_per_block;
    bool write_allocate;
    bool write_back;
    string eviction_policy;
    unsigned block_offset;
    unsigned num_bits;

    int total_loads = 0;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    long long total_cycles = 0;
    uint64_t operationCounter;

    Cache(int num_sets, int blocks_per_set, int num_bytes_per_block, bool write_allocate, bool write_back, string eviction_policy, unsigned block_offset, unsigned num_bits)
        : sets(num_sets, Set(blocks_per_set)), blocks_per_set(blocks_per_set),
          num_bytes_per_block(num_bytes_per_block), write_allocate(write_allocate), write_back(write_back), eviction_policy(eviction_policy),
          block_offset(block_offset), num_bits(num_bits), operationCounter(0){}
};

uint64_t getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
    return static_cast<uint64_t>(millis);
}

size_t findIndex(const Set& set, const string& eviction_policy) {
    if (eviction_policy == "lru") {
        uint64_t oldestAccessTime = numeric_limits<uint64_t>::max();
        size_t candidateIndex = 0;

        for (size_t i = 0; i < set.slots.size(); ++i) {
            if (!set.slots[i].valid) {
                return i; // Prefer using an empty slot
            }
            if (set.slots[i].access_ts < oldestAccessTime) {
                oldestAccessTime = set.slots[i].access_ts;
                candidateIndex = i;
            }
        }
        return candidateIndex;
    }
    // Handle other policies like "fifo" as needed
    return 0;
}


void accessCache(Cache& cache, uint32_t address, bool isStore) {
    unsigned index = (address >> cache.block_offset) & ((1 << cache.num_bits) - 1);
    unsigned tag = address >> (cache.num_bits + cache.block_offset);
    Set& set = cache.sets[index];
    bool hit = false;

    // Loop over slots to find a hit
    for (Slot& slot : set.slots) {
        if (slot.valid && slot.tag == tag) {
            hit = true;
            slot.access_ts = cache.operationCounter++; // Update access timestamp
            if (isStore) {
                cache.store_hits++;
                if (cache.write_back) {
                    // Mark slot as dirty if write-back cache and storing
                    slot.dirty = true;
                } else {
                    // For write-through, write penalty because data is written to the next level of memory
                    cache.total_cycles += 100;
                }
            } else {
                cache.load_hits++;
            }
            // Increment for cache access time
            cache.total_cycles++;
            break;
        }
    }

    // If it is a miss
    if (!hit) {
        cache.total_cycles++; // Increment for miss detection
        if (isStore) {
            cache.store_misses++;
        } else {
            cache.load_misses++;
        }
        // Miss penalty for transferring the block
        cache.total_cycles += (cache.num_bytes_per_block / 4) * 100;

        // Find replacement slot index
        size_t slotIndex = findIndex(set, cache.eviction_policy);

        // If the cache policy is write-allocate or it's a read miss
        if (cache.write_allocate || !isStore) {
            // For write-back, check if we need to write back the dirty block
            if (cache.write_back && set.slots[slotIndex].valid && set.slots[slotIndex].dirty) {
                // Write-back penalty for transferring the dirty block
                cache.total_cycles += (cache.num_bytes_per_block / 4) * 100;
            }
            
            // Update the slot information
            set.slots[slotIndex].tag = tag;
            set.slots[slotIndex].valid = true;
            set.slots[slotIndex].dirty = false; // Fresh block is not dirty
            set.slots[slotIndex].load_ts = cache.operationCounter; // Update load timestamp
            set.slots[slotIndex].access_ts = cache.operationCounter++; // Update access timestamp

            // If write-through and a store, add the write penalty
            if (!cache.write_back && isStore) {
                cache.total_cycles += 100;
            }
        } else if (cache.write_back && isStore && !cache.write_allocate) {
            // If it's write-back and no-write-allocate, we don't load the block into the cache on a store miss
            // Instead, we write directly to the lower memory level, so add the write penalty
            cache.total_cycles += 100;
        }
    }

    // Increment total stores or loads regardless of hit or miss
    if (isStore) {
        cache.total_stores++;
    } else {
        cache.total_loads++;
    }
}



void readFromCache(Cache& cache, uint32_t address) {
    accessCache(cache, address, false); // false indicates a load operation
}

void writeToCache(Cache& cache, uint32_t address) {
    accessCache(cache, address, true); // true indicates a store operation
}

void read_inputs_from_stdin(Cache& cache) {
    string line;
    while (getline(cin, line)) {
        char operation;
        uint64_t address;
        sscanf(line.c_str(), "%c %lx", &operation, &address);

        if (operation == 'l') {
            readFromCache(cache, static_cast<uint32_t>(address));
        } else if (operation == 's') {
            writeToCache(cache, static_cast<uint32_t>(address));
        }
    }
}

void printSummary(const Cache& cache) {
    cout << "Total loads: " << cache.total_loads << endl;
    cout << "Total stores: " << cache.total_stores << endl;
    cout << "Load hits: " << cache.load_hits << endl;
    cout << "Load misses: " << cache.load_misses << endl;
    cout << "Store hits: " << cache.store_hits << endl;
    cout << "Store misses: " << cache.store_misses << endl;
    cout << "Total cycles: " << cache.total_cycles << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <num_sets> <blocks_per_set> <block_size> <write_allocate> <write_back> <eviction_policy>" << endl;
        return 1;
    }

    int num_sets = stoi(argv[1]);
    int num_blocks_per_set = stoi(argv[2]);
    int num_bytes_per_block = stoi(argv[3]);
    bool write_allocate = string(argv[4]) == "write-allocate";
    bool write_back = string(argv[5]) == "write-back";
    string eviction_policy = argv[6];

    unsigned block_offset = round(log2(num_bytes_per_block)); // number of bits used to identify byte within cache block
    unsigned num_bits = round(log2(num_sets)); // number of bits used to index

    Cache my_cache(num_sets, num_blocks_per_set, num_bytes_per_block, write_allocate, write_back, eviction_policy, block_offset, num_bits);

    cerr << "num_sets: " << num_sets << ", num_blocks_per_set: " << num_blocks_per_set << ", num_bytes_per_block: " << num_bytes_per_block << ", write_allocate: " << write_allocate << ", write_back: " << write_back << ", eviction_policy: " << eviction_policy << ", block_offset: " << block_offset << ", num_bits: " << num_bits <<"\n";

    read_inputs_from_stdin(my_cache);

    printSummary(my_cache);
    return 0;
}
