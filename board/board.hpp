#pragma once
#include <string>
#include "tables.hpp"
#include "types.hpp"

class Board{
    inline void update_bitboards(int piece, int from, int to);
    inline int check_is_piece(char c);
public:
    Table& table;
    
    //12 for all pieces
    std::array<uint64_t, 12> bitboards;
    std::array<uint64_t, 3> occup;
    color side;
    square enpessant;
    uint8_t castling_rights;

    //for ease of use, it might be better to just keep a stack and restore on a pop
    //each time make move is invoked, maybe we just push to the stack
    std::array<uint64_t, 12> prev_bitboards;
    std::array<uint64_t, 3> prev_occup;
    color prev_side;
    square prev_enpessant;
    uint8_t prev_castling;

    Piece which_piece(const int);

    //sliders
    template<color c>
    uint64_t get_pawn_attack(square);

    uint64_t get_attack_bb(piece_type p, square s);
    
    void read_fen(const std::string&);

    //todo add check(the chess one) boolean for both white and black maybe?
    bool white_check;
    bool black_check;

    bool attacked(square, color);
    
    void unmake_move();
    bool make_move(Move m);

    void print();

    void debug(uint64_t); 

    Board(const std::string &s) : table(Table::get_instance()),  
        bitboards{0}, occup{0}, side(WHITE) , enpessant(none){read_fen(s);}
    Board() : table(Table::get_instance()),  
    bitboards{0}, occup{0}, side(WHITE) , enpessant(none){}
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
};