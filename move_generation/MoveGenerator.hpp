#pragma once
#include <string>
#include <iostream>
#include "board.hpp"


class MoveGenerator{
    Board board;
    Table& t;
public:
    void generate_pawn_moves();
    void generate_knight_moves();
    void generate_rook_moves();
    void generate_bishop_moves();
    void generate_king_moves();

    template <piece_type pt, color c>
    void generate_moves(uint64_t bb);

    MoveGenerator(Board b);
};

/*
encoding of moves list
          binary move bits                               hexidecimal constants
    
    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000
*/

struct move_list{
    int moves[256];
    int count;

    void add_move(int source, int target, int piece, int promoted, int capture, int double_push, int enpassant, int castling){
        moves[count++] = create_move(source, target, piece, promoted, capture, double_push, enpassant, castling);
    }

    template<uint64_t N>
    void print_move(int move, std::array<std::string, N>& square_map){
        std::cout << square_map[get_source(move)] << square_map[get_target(move)] << get_promoted(move) << "\n"; 
    }

    static inline int get_source(int move){
        return move & 0x3f;
    }

    static inline int get_target(int move){
        return (move & 0xfc0) >> 6;
    }

    static inline int get_piece(int move){
        return (move & 0xf000) >> 12;
    }

    static inline int get_promoted(int move){
        return (move & 0xf0000) >> 16;
    }

    static inline int get_capture(int move){
        return (move & 0x100000);
    }

    static inline int get_double(int move){
        return (move & 0x200000);
    }

    static inline int get_enpassant(int move){
        return (move & 0x400000);
    }

    static inline int get_castling(int move){
        return (move & 0x800000);
    }

    static inline int create_move(int source, int target, int piece, int promoted, int capture, int double_push, int enpassant, int castling){
        return  (source) | (target << 6) | (piece << 12) | (promoted << 16) | (capture << 20) | (double_push << 21) | (enpassant << 22) | (castling << 23);
    }
};
