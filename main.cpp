/*
 * A3MS2
 * Cassie Zhang xzhan304
 * Tianai Yue tyue4
 */
 
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <chrono>
#include <limits>
#include <cmath>


using namespace std;

/*
 * Slot constructor initializes cache slot attributes.
 */
struct Slot {
    uint32_t tag;
    bool valid;
    bool dirty;
    uint64_t load_ts, access_ts;
    uint64_t operation_counter;

    Slot() : tag(0), valid(false), dirty(false), load_ts(0), access_ts(0), operation_counter(0) {}
};

/*
 * Set constructor initializes a set with the specified number of slots.
 *
 * Parameters:
 *   blocks_per_set - The number of blocks (slots) within this set.
 *
 */
struct Set {
    vector<Slot> slots;

    explicit Set(int blocks_per_set) : slots(blocks_per_set) {}
};

/*
 * Cache constructor initializes cache with given parameters, sets up its structure and configuration.
 *
 * Parameters:
 *   num_sets - Number of sets in the cache.
 *   blocks_per_set - Number of blocks per set.
 *   num_bytes_per_block - Size of each block in bytes.
 *   write_allocate - Write allocate policy flag.
 *   write_back - Write back policy flag.
 *   eviction_policy - Eviction policy (e.g., LRU, FIFO).
 *   block_offset - Number of bits for block offset.
 *   num_bits - Number of bits for indexing sets.
 *
 */
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
    uint64_t operation_counter;

    Cache(int num_sets, int blocks_per_set, int num_bytes_per_block, bool write_allocate, bool write_back, string eviction_policy, unsigned block_offset, unsigned num_bits)
        : sets(num_sets, Set(blocks_per_set)), blocks_per_set(blocks_per_set),
          num_bytes_per_block(num_bytes_per_block), write_allocate(write_allocate), write_back(write_back), eviction_policy(eviction_policy),
          block_offset(block_offset), num_bits(num_bits), operation_counter(0){}
};

/*
 * Gets the current time in milliseconds since the epoch. This function is used for timestamping cache operations to implement policies.
 *
 * Returns:
 *   The current time in milliseconds as a 64-bit unsigned integer.
 */
uint64_t getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
    return static_cast<uint64_t>(millis);
}

/*
 * Finds an index for a new cache block in a set according to the specified eviction policy. 
 * For LRU, it returns the index of the least recently used slot.
 *
 * Parameters:
 *   set - The set in which to find an eviction candidate.
 *   eviction_policy - The eviction policy to use.
 *
 * Returns:
 *   The index of the slot in the set that should be used/replaced according to the eviction policy.
 */
size_t findIndex(const Set& set, const string& eviction_policy) {
    // if using LRU policy, find the least recently used slot
    if (eviction_policy == "lru") {
        uint64_t oldestAccessTime = numeric_limits<uint64_t>::max();
        size_t candidateIndex = 0;
        // iterate over slots to find the LRU slot
        for (size_t i = 0; i < set.slots.size(); ++i) {
            // check if first empty slot found
            if (!set.slots[i].valid) {
                return i;
            }
            // update oldest accessed slot
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

/*
 * Updates a cache slot at a specific index within a set with new cache block information. Marks the slot as valid, 
 * sets the tag, and updates the load and access timestamps. The dirty flag is set according to the cache's 
 * write policy and whether the operation is a store.
 *
 * Parameters:
 *   set - The cache set containing the slot to be updated.
 *   slotIndex - The index of the slot within the set to update.
 *   tag - The tag to store in the slot.
 *   isStore - Boolean flag indicating whether the operation causing the update is a store operation.
 *   cache - Reference to the cache to access global properties like write policy.
 *
 */
void update_slot(Set& set, size_t slotIndex, uint32_t tag, bool isStore, Cache& cache) {
    // update the slot information
    set.slots[slotIndex].tag = tag;
    set.slots[slotIndex].valid = true;
    // set timestamps for load and access
    set.slots[slotIndex].dirty = cache.write_back && isStore;
    set.slots[slotIndex].load_ts = cache.operation_counter;
    set.slots[slotIndex].access_ts = cache.operation_counter++;
}

/*
 * Handles access to the cache for both load and store operations. Determines whether the access is a hit or miss
 * and updates cache statistics accordingly. In case of a miss, it may also handle block evictions and replacements
 * according to the cache's configuration.
 *
 * Parameters:
 *   cache - Reference to the cache being accessed.
 *   address - The memory address being accessed.
 *   isStore - Boolean flag indicating whether the access is a store operation.
 *
 */
void accessCache(Cache& cache, uint32_t address, bool isStore) {
    // calculate set index and tag from address
    unsigned index = (address >> cache.block_offset) & ((1 << cache.num_bits) - 1);
    unsigned tag = address >> (cache.num_bits + cache.block_offset);
    Set& set = cache.sets[index];
    bool hit = false;

    // check for hit or miss in the set
    for (Slot& slot : set.slots) {
        // increment total stores or loads regardless of hit or miss
        if (slot.valid && slot.tag == tag) {
            hit = true;
            slot.access_ts = cache.operation_counter++;
            // update hit counts
            if (isStore) {
                cache.store_hits++;
                if (cache.write_back) {
                    // write-back cache: increment cycles by 1 and set the slot as dirty
                    cache.total_cycles++;
                    slot.dirty = true;
                } else {
                    // write-through cache: increment cycles by the write penalty
                    cache.total_cycles += 100;
                }
            } else {
                cache.load_hits++;
                cache.total_cycles++;
            }
            break;
        }
    }
    // cache miss handling: increment appropriate miss counters based on operation type
    if (!hit) {
        // handle cache miss
        if (isStore) {
            cache.store_misses++;
        } else {
            cache.load_misses++;
        }
        // no-write-allocate: handle store miss by writing directly to memory
        if (isStore && !cache.write_allocate) {
            cache.total_stores++;
            cache.total_cycles +=100;
            return;
        }
        // common miss penalty for transferring data into cache
        cache.total_cycles += (cache.num_bytes_per_block / 4) * 100;

        // If no write-allocate and it's a store, write directly to memory
        if (isStore && !cache.write_allocate) {
            // no-write-allocate
        } else {
            // write-allocate or load miss: find slot to update or evict
            size_t slotIndex = findIndex(set, cache.eviction_policy);
            // write-back: add penalty for evicting dirty block
            if (cache.write_back && set.slots[slotIndex].valid && set.slots[slotIndex].dirty) {
                cache.total_cycles += (cache.num_bytes_per_block / 4) * 100;
            }
            update_slot(set, slotIndex, tag, isStore, cache);
        }
    }
    // increment total stores or loads regardless of hit or miss
    if (isStore) {
        cache.total_stores++;
    } else {
        cache.total_loads++;
    }
}

/*
 * Simulates a cache read operation for a given memory address.
 *
 * Parameters:
 *   cache - Reference to the cache from which to read.
 *   address - The memory address to read from.
 */

void readFromCache(Cache& cache, uint32_t address) {
    accessCache(cache, address, false); // false indicates a load operation
}

/*
 * Simulates a cache write operation for a given memory address.
 *
 * Parameters:
 *   cache - Reference to the cache to which to write.
 *   address - The memory address to write to.
 */
void writeToCache(Cache& cache, uint32_t address) {
    accessCache(cache, address, true); // true indicates a store operation
}

/*
 * Processes memory access traces from standard input, applying each to the cache.
 *
 * Parameters:
 *   cache - Reference to the cache that the operations will be applied to.
 */

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

/*
 * Prints summary statistics to standard output.
 *
 * Parameters:
 *   cache - The cache for which to print the summary.
 */
void printSummary(const Cache& cache) {
    cout << "Total loads: " << cache.total_loads << endl;
    cout << "Total stores: " << cache.total_stores << endl;
    cout << "Load hits: " << cache.load_hits << endl;
    cout << "Load misses: " << cache.load_misses << endl;
    cout << "Store hits: " << cache.store_hits << endl;
    cout << "Store misses: " << cache.store_misses << endl;
    cout << "Total cycles: " << cache.total_cycles << endl;
}

/*
 * Checks if a number is a power of two, used for validating cache configuration parameters.
 *
 * Parameters:
 *   x - The integer to check.
 *
 * Returns:
 *   True if x is a power of two, false otherwise.
 */
bool is_power_of_two(int x) {
    return x && !(x & (x - 1));
}

/*
 * Validates that cache configuration parameters are valid before starting the simulation.
 *
 * Parameters:
 *   num_sets - Number of sets in the cache.
 *   num_blocks_per_set - Number of blocks per set.
 *   num_bytes_per_block - Size of each block in bytes.
 *   write_allocate - Write allocate policy flag.
 *   write_back - Write back policy flag.
 */
void validate_parameters(int num_sets, int num_bytes_per_block, bool write_allocate, bool write_back) {
    if (!is_power_of_two(num_bytes_per_block) || !is_power_of_two(num_sets) || num_bytes_per_block < 4 || (write_back && !write_allocate)) {
        cerr << "Invalid cache configuration parameters:" << endl;
        if (!is_power_of_two(num_bytes_per_block)) {
            cerr << "Block size is not a power of 2." << endl;
        }
        if (!is_power_of_two(num_sets)) {
            cerr << "Number of sets is not a power of 2." << endl;
        }
        if (num_bytes_per_block < 4) {
            cerr << "Block size is less than 4." << endl;
        }
        if (write_back && !write_allocate) {
            cerr << "Write-back and no-write-allocate combination is not allowed." << endl;
        }
        exit(EXIT_FAILURE);
    }
}

/*
 * Run the cache simulator with parameters provided via command-line arguments.
 *
 * Parameters:
 *   argc - The number of command-line arguments.
 *   argv - The array of command-line arguments.
 *
 * Returns:
 *   An integer indicating the exit status of the program. Returns 0 on successful execution and 1 if the incorrect
 *   number of arguments are provided.
 */
int main(int argc, char *argv[]) {
    // check for correct number of arguments
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <num_sets> <blocks_per_set> <block_size> <write_allocate> <write_back> <eviction_policy>" << endl;
        return 1;
    }
    // parse arguments and set up cache configuration
    int num_sets = stoi(argv[1]);
    int num_blocks_per_set = stoi(argv[2]);
    int num_bytes_per_block = stoi(argv[3]);
    bool write_allocate = string(argv[4]) == "write-allocate";
    bool write_back = string(argv[5]) == "write-back";
    string eviction_policy = argv[6];
    // validate parameters and initialize cache
    validate_parameters(num_sets, num_bytes_per_block, write_allocate, write_back);
    unsigned block_offset = round(log2(num_bytes_per_block));
    unsigned num_bits = round(log2(num_sets));
    Cache my_cache(num_sets, num_blocks_per_set, num_bytes_per_block, write_allocate, write_back, eviction_policy, block_offset, num_bits);
    // process memory accesses and output summary
    read_inputs_from_stdin(my_cache);
    printSummary(my_cache);
    return 0;
}
