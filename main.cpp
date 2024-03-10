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

using namespace std;

struct Slot {
    uint32_t tag;
    bool valid;
    bool dirty;
    uint64_t load_ts, access_ts;

    Slot() : tag(0), valid(false), dirty(false), load_ts(0), access_ts(0) {}
};

struct Set {
    vector<Slot> slots;

    explicit Set(int blocks_per_set) : slots(blocks_per_set) {}
};

struct Cache {
    vector<Set> sets;
    int blocks_per_set;
    int block_size;
    bool write_allocate;
    bool write_back;
    string eviction_policy;

    int total_loads = 0;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    long long total_cycles = 0;

    Cache(int num_sets, int blocks_per_set, int block_size, bool write_allocate, bool write_back, string eviction_policy)
        : sets(num_sets, Set(blocks_per_set)), blocks_per_set(blocks_per_set),
          block_size(block_size), write_allocate(write_allocate), write_back(write_back), eviction_policy(eviction_policy) {}
};

uint64_t getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
    return static_cast<uint64_t>(millis);
}

size_t findEvictionCandidate(const Set& set, const string& eviction_policy) {
    if (eviction_policy == "lru") {
        uint64_t oldestAccessTime = numeric_limits<uint64_t>::max();
        size_t candidateIndex = 0;

        for (size_t i = 0; i < set.slots.size(); ++i) {
            if (!set.slots[i].valid) {
                return i;
            }
            if (set.slots[i].access_ts < oldestAccessTime) {
                oldestAccessTime = set.slots[i].access_ts;
                candidateIndex = i;
            }
        }

        return candidateIndex;
    }
    // Add other eviction policies for fifo
}

void accessCache(Cache& cache, uint32_t address, bool isStore) {
    uint32_t set_index = (address / cache.block_size) % cache.sets.size();
    uint32_t tag = address / (cache.block_size * cache.sets.size());
    Set& set = cache.sets[set_index];
    bool hit = false;

    for (Slot& slot : set.slots) {
        if (slot.valid && slot.tag == tag) {
            hit = true;
            slot.access_ts = getCurrentTime();

            if (isStore) {
                slot.dirty = cache.write_back;
                cache.store_hits++;
            } else {
                cache.load_hits++;
            }

            cache.total_cycles++;
            break;
        }
    }

    if (!hit) {
        if (isStore) {
            cache.store_misses++;
        } else {
            cache.load_misses++;
        }

        cache.total_cycles += 100; // simulating the miss penalty

        if (cache.write_allocate || !isStore) {
            size_t slotIndex = findEvictionCandidate(set, cache.eviction_policy);

            if (set.slots[slotIndex].valid && set.slots[slotIndex].dirty && cache.write_back) {
                // simulating the write-back delay if the block is dirty
                cache.total_cycles += 100;
            }

        
            set.slots[slotIndex].tag = tag;
            set.slots[slotIndex].valid = true;
            set.slots[slotIndex].dirty = isStore; 
            set.slots[slotIndex].load_ts = getCurrentTime();
            set.slots[slotIndex].access_ts = getCurrentTime(); 
        }
    }

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
    int blocks_per_set = stoi(argv[2]);
    int block_size = stoi(argv[3]);
    bool write_allocate = string(argv[4]) == "write-allocate";
    bool write_back = string(argv[5]) == "write-back";
    string eviction_policy = argv[6];

    Cache my_cache(num_sets, blocks_per_set, block_size, write_allocate, write_back, eviction_policy);
    read_inputs_from_stdin(my_cache);

    printSummary(my_cache);
    return 0;
}
