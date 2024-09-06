#pragma once
#include "board.hpp"

class Search{
public:
    int ply;
    uint64_t nodes;
    int max_depth;
    std::array<std::array<Move, 64>, 64> pv_table;
    std::array<int, 64> pv_length;
    Search() : ply(0), nodes(0), max_depth(0), pv_table{}, pv_length{} {}
    
    int negamax(Board& b, int alpha, int beta, int depth);
    int quiescence(Board& b, int alpha, int beta);
    void begin_search(Board& board, int depth);
};
