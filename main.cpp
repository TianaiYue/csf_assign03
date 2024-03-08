/** 
 * A1MS2
 * Cassie Zhang xzhan304
 * Tianai Yue
 */

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
    uint32_t load_ts, access_ts;
};

struct Set {
    vector<Slot> slots;
};

struct Cache { 
    vector<Set> sets;
};


// Parse from the string we read from the file
void parse_line(const std::string& access, int& type, std::uint64_t& address) {
    sscanf(access.c_str(), "%*c %lx %d", &address, &type);

}

void read_inputs_from_file(const char* filename, Cache& cache) {
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
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <trace_file_name>\n";
        return 1;
    }
    
    Cache my_cache;
    read_inputs_from_file(argv[1], my_cache);

    return 0;
}
