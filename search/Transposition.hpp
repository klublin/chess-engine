#pragma once
#include "types.hpp"
#include "Move.hpp"
#include <algorithm>

class Transposition_table{
    struct Transposition_node{
        uint64_t key;
        int depth;
        Hash_Flags flags;
        int score;

        Transposition_node() : key(0), depth(0), flags(Hash_Flags::EXACT), score(0) {}
        void clear(){
            key = 0;
            depth = 0;
            flags = Hash_Flags::EXACT;
            score = 0;
        }
    };
    std::array<Transposition_node, Hash_Flags::HASH_SIZE> tt;
public:
    void write_hash(uint64_t hash_key, int score, int depth, Hash_Flags flags);
    int read_hash(uint64_t hash_key, int alpha, int beta, int depth);
    inline void clear_table(){
        std::for_each(tt.begin(), tt.end(), [](Transposition_node& e) {
            e.clear();
        });
    }
};