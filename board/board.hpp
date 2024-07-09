#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>


class Board{
    enum color{WHITE, BLACK};

    color side;

    uint64_t rooks[2];
    uint64_t bishops[2];
    uint64_t pawns[2];
    uint64_t queens[2];
    uint64_t kings[2];
    uint64_t knights[2];

public:
    uint64_t update(const std::string& s){
        return 0;
    };
};