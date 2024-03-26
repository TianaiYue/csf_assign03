/*
 * A3MS2
 * Implements a cache simulator to analyze different cache configurations. 
 * Cassie Zhang xzhan304
 * Tianai Yue tyue4
 */

#include "cache.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

/*
 * Slot constructor initializes cache slot attributes.
 */
Slot::Slot() : tag(0), valid(false), dirty(false), load_ts(0), access_ts(0), operation_counter(0) {}

/*
 * Set constructor initializes a set with the specified number of slots.
 *
 * Parameters:
 *   blocks_per_set - The number of blocks (slots) within this set.
 */
Set::Set(int blocks_per_set) : slots(blocks_per_set) {}

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
 */
Cache::Cache(int num_sets, int blocks_per_set, int num_bytes_per_block, bool write_allocate, bool write_back, string eviction_policy, unsigned block_offset, unsigned num_bits)
    : sets(num_sets, Set(blocks_per_set)), blocks_per_set(blocks_per_set),
      num_bytes_per_block(num_bytes_per_block), write_allocate(write_allocate), write_back(write_back), eviction_policy(eviction_policy),
      block_offset(block_offset), num_bits(num_bits), operation_counter(0) {
    total_loads = 0;
    total_stores = 0;
    load_hits = 0;
    load_misses = 0;
    store_hits = 0;
    store_misses = 0;
    total_cycles = 0;
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
size_t find_index(const Set& set, const string& eviction_policy) {
    // if using LRU policy, find the least recently used slot
    if (eviction_policy == "lru") {
        uint64_t oldest_access_time = numeric_limits<uint64_t>::max();
        size_t candidate_index = 0;
        // iterate over slots to find the LRU slot
        for (size_t i = 0; i < set.slots.size(); ++i) {
            // check if first empty slot found
            if (!set.slots[i].valid) {
                return i;
            }
            // update oldest accessed slot
            if (set.slots[i].access_ts < oldest_access_time) {
                oldest_access_time = set.slots[i].access_ts;
                candidate_index = i;
            }
        }
        return candidate_index;
    }else if (eviction_policy == "fifo") {
        uint64_t earliest_load_time = numeric_limits<uint64_t>::max();
        size_t candidate_index = 0;
        for (size_t i = 0; i < set.slots.size(); ++i) {
            if (!set.slots[i].valid) return i; // Empty slot found
            if (set.slots[i].load_ts < earliest_load_time) {
                earliest_load_time = set.slots[i].load_ts;
                candidate_index = i;
            }
        }
        return candidate_index;
    }
    // Default to 0 if policy not recognized (consider throwing an error or handling invalid policy)
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
void update_slot(Set& set, size_t slot_index, uint32_t tag, bool isStore, Cache& cache) {
    // update the slot information
    set.slots[slot_index].tag = tag;
    set.slots[slot_index].valid = true;
    // set timestamps for load and access
    set.slots[slot_index].dirty = cache.write_back && isStore;
    set.slots[slot_index].load_ts = cache.operation_counter;
    set.slots[slot_index].access_ts = cache.operation_counter++;
}

/*
 * Determines if a cache access is a hit or miss and updates the relevant cache statistics.
 *
 * Parameters:
 *   cache - Reference to the cache being accessed.
 *   address - The memory address being accessed.
 *   is_store - Boolean flag indicating whether the access is a store operation.
 *
 * Returns:
 *   A boolean indicating whether the access was a hit (true) or miss (false).
 */
bool determine_hit_or_miss(Cache& cache, uint32_t address, bool is_store) {
    // calculate set index and tag from address
    unsigned index = (address >> cache.block_offset) & ((1 << cache.num_bits) - 1);
    unsigned tag = address >> (cache.num_bits + cache.block_offset);
    Set& set = cache.sets[index];
    bool hit = false;
    for (Slot& slot : set.slots) {
        // increment total stores or loads regardless of hit or miss
        if (slot.valid && slot.tag == tag) {
            hit = true;
            slot.access_ts = cache.operation_counter++;
            // update hit counts
            if (is_store) {
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
        if (is_store) {
            cache.store_misses++;
        } else {
            cache.load_misses++;
        }
    }
    return hit;
}


/*
 * Handles cache misses by finding a slot for eviction if necessary, and updates the cache block.
 * Applies the cache's write policy and eviction policy during this process.
 *
 * Parameters:
 *   cache - Reference to the cache being accessed.
 *   address - The memory address being accessed.
 *   is_store - Boolean flag indicating whether the access is a store operation.
 */
void handle_cache_miss(Cache& cache, uint32_t address, bool is_store) {
    // calculate set index and tag from address
    unsigned index = (address >> cache.block_offset) & ((1 << cache.num_bits) - 1);
    unsigned tag = address >> (cache.num_bits + cache.block_offset);
    Set& set = cache.sets[index];
    // if no-write-allocate and store operations, write directly to memory
    if (is_store && !cache.write_allocate) {
        cache.total_cycles += 100;
    } else {
        // Write-allocate or a load: bring the block into the cache
        size_t slotIndex = find_index(set, cache.eviction_policy); // Pass cache for FIFO
        // Evict if necessary (check for dirty block if write-back)
        if (cache.write_back && set.slots[slotIndex].valid && set.slots[slotIndex].dirty) {
            cache.total_cycles += (cache.num_bytes_per_block / 4) * 100; // Write-back dirty block
        }
        // Update the slot with new block data
        update_slot(set, slotIndex, tag, is_store, cache);
        // Account for the cycles taken to load the block into the cache
        cache.total_cycles += (cache.num_bytes_per_block / 4) * 100;
    }
}

/*
 * Handles load or store operations for a given address in the cache, updating access statistics and managing hits or
 * misses. Calls `determine_hit_or_miss` to check access status and `handle_cache_miss` for miss management.
 *
 * Parameters:
 *   cache - The cache to access.
 *   address - Memory address for the operation.
 *   is_store - True for store operations, false for load operations.
 */
 void access_cache(Cache& cache, uint32_t address, bool is_store) {
    // determine hit or miss status for the access
    bool hit = determine_hit_or_miss(cache, address, is_store);
    // if miss, handle it based on cache configuration
    if (!hit) {
        handle_cache_miss(cache, address, is_store);
    }
    // increment the total number of loads or stores after determining hit or miss
    if (is_store) {
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

void read_from_cache(Cache& cache, uint32_t address) {
    access_cache(cache, address, false); // false indicates a load operation
}

/*
 * Simulates a cache write operation for a given memory address.
 *
 * Parameters:
 *   cache - Reference to the cache to which to write.
 *   address - The memory address to write to.
 */
void write_to_cache(Cache& cache, uint32_t address) {
    access_cache(cache, address, true); // true indicates a store operation
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
            read_from_cache(cache, static_cast<uint32_t>(address));
        } else if (operation == 's') {
            write_to_cache(cache, static_cast<uint32_t>(address));
        }
    }
}

/*
 * Prints summary statistics to standard output.
 *
 * Parameters:
 *   cache - The cache for which to print the summary.
 */
void print_summary(const Cache& cache) {
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