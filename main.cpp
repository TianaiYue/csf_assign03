/*
 * A3MS2
 * Initiates the cache simulator.
 * Cassie Zhang xzhan304
 * Tianai Yue tyue4
 */

#include "cache.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <chrono>
#include <limits>
#include <cmath>

using namespace std;

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
        cerr << "Not enough arguments." << endl;
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
    print_summary(my_cache);
    // print_cache_performance(my_cache);

    return 0;
}
