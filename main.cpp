#include <stdio.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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

    Cache(int num_sets, int blocks_per_set, int block_size, bool write_allocate, bool write_back)
        : sets(num_sets, Set(blocks_per_set)), blocks_per_set(blocks_per_set),
          block_size(block_size), write_allocate(write_allocate), write_back(write_back) {}
};

// Parse from the string we read from the file
void parse_line(const std::string& access, int& type, std::uint64_t& address) {
    sscanf(access.c_str(), "%*c %lx %d", &address, &type);
}

void read_inputs_from_file(const char* filename, Cache& cache) {
    (void)cache; // Suppress unused parameter warning

    ifstream trace_file(filename);
    if (!trace_file.is_open()) {
        cerr << "Failed to open trace file: " << filename << endl;
        return;
    }

    std::string line;
    while (getline(trace_file, line)) {
        int type;
        std::uint64_t address;
        parse_line(line, type, address);
        std::cout << "Type: " << type << ", Address: " << std::hex << address << std::endl;
    }
    
    trace_file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <num_sets> <blocks_per_set> <block_size> <write_allocate> <write_back> <trace_file_name>\n";
        return 1;
    }
    
    int num_sets = stoi(argv[1]);
    int blocks_per_set = stoi(argv[2]);
    int block_size = stoi(argv[3]);
    bool write_allocate = string(argv[4]) == "write-allocate";
    bool write_back = string(argv[5]) == "write-back";
    const char* trace_file_name = argv[6];

    Cache my_cache(num_sets, blocks_per_set, block_size, write_allocate, write_back);
    read_inputs_from_file(trace_file_name, my_cache);

    return 0;
}
