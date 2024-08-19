#pragma once
#include <string>
#include <unordered_map>
#include "tables.hpp"
#include "types.hpp"

class Board{
public:
    color side;
    Table& table;
    square enpessant;
    int castling_rights;

    //12 for all pieces
    std::array<uint64_t, 12> bitboards;
    std::array<uint64_t, 3> occup;

    //these maps may be better suited as arrays? Maybe cahnge for later when runtime becomes an issue
    // const static std::unordered_map<std::string, uint64_t> square_to_num;
    // const static std::unordered_map<uint64_t, std::string> num_to_square;
    static const std::unordered_map<int, char> symbol_map;

    int which_piece(const uint64_t board);

    //sliders
    template<color c>
    uint64_t get_pawn_attack(square);

    uint64_t get_attack_bb(piece_type p, square s, uint64_t occup=0);

    
    void read_fen(const std::string&);
    inline int check_is_piece(char c);

    //todo add check(the chess one) boolean for both white and black maybe?
    bool white_check;
    bool black_check;

    bool attacked(square, color);
    
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
    void print();
    Board();
    void debug(uint64_t); 
};