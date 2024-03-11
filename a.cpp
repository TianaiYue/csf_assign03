void accessCache(Cache& cache, uint32_t address, bool isStore) {
    unsigned index = (address >> cache.block_offset) & ((1 << cache.num_bits) - 1);
    unsigned tag = address >> (cache.num_bits + cache.block_offset);
    Set& set = cache.sets[index];
    bool hit = false;

    for (Slot& slot : set.slots) {
        if (slot.valid && slot.tag == tag) {
            hit = true;
            slot.access_ts = cache.operationCounter++; // Update access timestamp
            if (isStore) {
                // Mark slot as dirty if it's a write-back cache and it's a store operation
                slot.dirty = cache.write_back;
                cache.store_hits++;
                // In case of a write-back cache, we don't add the write penalty here
            } else {
                cache.load_hits++;
            }
            // Increment for cache access time
            cache.total_cycles++; 
            break;
        }
    }

    if (!hit) {
        cache.total_cycles++; // Increment for miss detection
        cache.total_cycles += (cache.num_bytes_per_block / 4) * 100; // Miss penalty for transferring the block

        if (isStore) {
            cache.store_misses++;
        } else {
            cache.load_misses++;
        }

        // Find replacement slot index for loading the block into the cache
        size_t slotIndex = findIndex(set, cache.eviction_policy);

        // For a write-back cache, if the slot to be replaced is dirty, write back to lower memory
        if (cache.write_back && set.slots[slotIndex].valid && set.slots[slotIndex].dirty) {
            cache.total_cycles += (cache.num_bytes_per_block / 4) * 100; // Write-back penalty
        }

        // Load the block into the cache if it's a write-allocate or a load
        if (cache.write_allocate || !isStore) {
            set.slots[slotIndex].tag = tag;
            set.slots[slotIndex].valid = true;
            // For write-back, set dirty on stores; for write-through, blocks are always clean
            set.slots[slotIndex].dirty = cache.write_back && isStore;
            set.slots[slotIndex].load_ts = cache.operationCounter;
            set.slots[slotIndex].access_ts = cache.operationCounter++;
        } else if (isStore && !cache.write_allocate) {
            // For a store miss without write-allocate, write directly to lower memory only for write-through
            if (!cache.write_back) {
                cache.total_cycles += 100;
            }
            // No block is loaded into the cache
        }
    }

    // Increment total stores or loads regardless of hit or miss
    if (isStore) {
        cache.total_stores++;
    } else {
        cache.total_loads++;
    }
}
