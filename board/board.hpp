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
        BLACK = 6
    };
    color side;

    enum pieces{
        PAWNS,
        KNIGHTS,
        BISHOPS,
        QUEEN,
        KING,
        ROOKS,
        NUM_PIECES
    };
    


    uint64_t bitboards[12];

    const static std::unordered_map<std::string, uint64_t> square_to_num;
    const static std::unordered_map<uint64_t, std::string> num_to_square;
    const static std::unordered_map<int, char> symbol_map;

    char which_piece(const uint64_t board);
public:
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
    void print();
    Board();

    void update(const std::string&);
    
};