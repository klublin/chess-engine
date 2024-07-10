#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>


/*
    TODOS: look into how to move pieces from the bitboard point of view. 
    

*/

class Board{
    enum color{
        WHITE = 0, 
        BLACK = 5
    };
    color side;

    enum pieces{
        PAWNS,
        KNIGHTS,
        BISHOPS,
        QUEEN,
        KING,
        ROOKS
    };

    uint64_t board[12];

    const static std::unordered_map<std::string, uint64_t> square_to_num;
    const static std::unordered_map<uint64_t, std::string> num_to_square;

public:
    void print();
    Board();

    void update(const std::string&);
    
};