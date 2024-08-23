#pragma once
#include <string>
#include <stack>
#include "tables.hpp"
#include "State.hpp"
#include "Move.hpp"

class Board{
    inline void update_bitboards(int piece, int source, int dest, int occup_index);
    inline int check_is_piece(char c);
public:
    Table& table;
    
    State st;
    std::stack<State> history;
    State* get_state() {return &st;};

    void save_state();

    Piece which_piece(const int, int);

    //sliders
    template<pawns p>
    uint64_t get_pawn_attack(square);

    uint64_t get_attack_bb(piece_type p, square s);
    
    void read_fen(const std::string&);

    //todo add check(the chess one) boolean for both white and black maybe?
    bool white_check;
    bool black_check;

    bool attacked(square, color);
    
    void unmake_move(Move m);
    bool make_move(Move m);

    void print();

    void debug(uint64_t); 

    Board(const std::string &s) : table(Table::get_instance()){read_fen(s);}
    Board() : table(Table::get_instance()) {}
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
};