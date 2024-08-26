#pragma once
#include <string>
#include <stack>
#include "tables.hpp"
#include "State.hpp"
#include "Move.hpp"

class Board{
    inline void update_bitboards(int piece, square source, square dest, color);
    inline int check_is_piece(char c);
public:
    Table& table;
    
    State st;
    std::stack<State> history;
    State* get_state() {return &st;};

    void save_state();

    Piece which_piece(const int);

    //sliders
    uint64_t get_pawn_attack(color, square);

    template<Piece_type pt>
    uint64_t Board::get_attack_bb(square s){
        uint64_t rook_attack;
        uint64_t attack;
        switch(pt){
            case ROOK:
                rook_attack = table.rook_attack_table[s];
                rook_attack &= st.occup[OCCUP_ALL];
                rook_attack *= table.rook_magics[s];
                rook_attack >>= (64 - table.rook_occupancy_bits[s]);
                return table.rook_table[s][rook_attack];  
            case BISHOP:
                attack = table.bishop_attack_table[s]; 
                attack &= st.occup[OCCUP_ALL];
                attack *= table.bishop_magics[s];
                attack >>= (64 - table.bishop_occupancy_bits[s]);
                return table.bishop_table[s][attack];   
            case QUEEN:
                return get_attack_bb<ROOK>(s) | get_attack_bb<BISHOP>(s);
            case KNIGHT:
                return table.knight_attack_table[s];
            case KING:
                return table.king_attack_table[s];
            default:
                return 0;
        }
    } 
    
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