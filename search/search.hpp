#pragma once
#include "Heuristics.hpp"
#include "board.hpp"
#include "Transposition.hpp"




class Search{
    Heuristics heuristics;
    enum{
        FULL_DEPTH_MOVES = 4,
        REDUCTION_LIMIT = 3,
    };
public:
    int ply;
    uint64_t nodes;
    int max_depth;

    Search() : heuristics(), ply(0), nodes(0), max_depth(0){}
    
    int negamax(Board& b, Transposition_table&, int alpha, int beta, int depth);
    int quiescence(Board& b, int alpha, int beta);
    Heuristics* get_heuristic() { return &heuristics;}
};


