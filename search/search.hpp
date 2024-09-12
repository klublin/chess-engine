#pragma once
#include "Heuristics.hpp"
#include "board.hpp"




class Search{
    Heuristics heuristics;
public:
    int ply;
    uint64_t nodes;
    int max_depth;

    Search() : heuristics(), ply(0), nodes(0), max_depth(0){}
    
    int negamax(Board& b, int alpha, int beta, int depth);
    int quiescence(Board& b, int alpha, int beta);
    Heuristics* get_heuristic() { return &heuristics;}
};


