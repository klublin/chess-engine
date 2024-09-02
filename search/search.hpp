#pragma once
#include "board.hpp"

class Search{
public:
    static std::array<std::array<int, 12>, 12> mva_table;
    int ply;
    uint64_t nodes;
    int max_depth;
    Move best_move;
    Search() : ply(0), nodes(0), max_depth(0), best_move(Move::none()){}
    
    int negamax(Board& b, int alpha, int beta, int depth);
    int quiescence(Board& b, int alpha, int beta);

};
