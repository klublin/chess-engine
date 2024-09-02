#pragma once
#include "board.hpp"
#include <vector>
#include <sstream>
#include "search.hpp"

class UCI{
    Board board;
    Search s;
    static Table& t;

    std::string str_move(const Move& m);
    Move to_move(std::string&);
public:
    UCI() {}
    UCI(Board& b) : board(b) {}
    void loop();
    void parse_position(std::istringstream& is);
    void set_position(std::string& fen, std::vector<std::string>& moves);
    void parse_go(std::istringstream& is);
    void print();
};