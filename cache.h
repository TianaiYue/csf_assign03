/*
 * A3MS2
 * Defines the structures and function prototypes for a cache simulator
 * Cassie Zhang xzhan304
 * Tianai Yue tyue4
 */

#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>
#include <string>

struct Slot {
    uint32_t tag;
    bool valid;
    bool dirty;
    uint64_t load_ts, access_ts;
    uint64_t operation_counter;

    Slot();
};

struct Set {
    std::vector<Slot> slots;

    explicit Set(int blocks_per_set);
};

struct Cache {
    std::vector<Set> sets;
    int blocks_per_set;
    int num_bytes_per_block;
    bool write_allocate;
    bool write_back;
    std::string eviction_policy;
    unsigned block_offset;
    unsigned num_bits;

    int total_loads;
    int total_stores;
    int load_hits;
    int load_misses;
    int store_hits;
    int store_misses;
    long long total_cycles;
    uint64_t operation_counter;

    Cache(int num_sets, int blocks_per_set, int num_bytes_per_block, bool write_allocate, bool write_back, std::string eviction_policy, unsigned block_offset, unsigned num_bits);
};

size_t find_index(const Set& set, const std::string& eviction_policy);
void update_slot(Set& set, size_t slotIndex, uint32_t tag, bool isStore, Cache& cache);
bool determine_hit_or_miss(Cache& cache, uint32_t address, bool is_store);
void handle_cache_miss(Cache& cache, uint32_t address, bool is_store);
void access_cache(Cache& cache, uint32_t address, bool is_store);
void read_from_cache(Cache& cache, uint32_t address);
void write_to_cache(Cache& cache, uint32_t address);
void read_inputs_from_stdin(Cache& cache);
void print_summary(const Cache& cache);
void print_properties(const Cache& cache);
bool is_power_of_two(int x);
void validate_parameters(int num_sets, int num_bytes_per_block, bool write_allocate, bool write_back);

#endif
