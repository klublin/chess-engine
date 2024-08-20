#pragma once
#include <string>
#include <iostream>
#include "board.hpp"

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
    
    move_list() : count(0){};

    void add_move(int source, int target, int piece, int promoted, int flags){
        moves[count++] = create_move(source, target, piece, promoted, flags);
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

    static inline int get_flags(int move){
        return (move & 0xF00000) >> 20;
    }

    static inline int create_move(int source, int target, int piece, int promoted, int flags){
        return  (source) | (target << 6) | (piece << 12) | (promoted << 16) | (flags << 20);
    }

    void print(Table& t){
        printf("\n     move    piece     capture   double    enpass    castling promoted\n\n");
        for(int i = 0; i < count; i++){
            printf("      %s%s   %c         %d         %d         %d         %d        %c\n", t.square_map[get_source(moves[i])].c_str(), 
                t.square_map[get_target(moves[i])].c_str(), 
                t.pieces[get_piece(moves[i])],
                get_capture(moves[i]) ? 1 : 0,
                get_double(moves[i]) ? 1 : 0,
                get_enpassant(moves[i]) ? 1 : 0,
                get_castling(moves[i]) ? 1 : 0,
                get_promoted(moves[i]) ? t.pieces[get_promoted(moves[i])] : '-');
        }
        std::cout << "move count = " << count << "\n";
    }
};

class MoveGenerator{
    Board board;
    static Table& t;
    template<color c>
    inline void helper_promo(uint64_t, int, move_list&, int);
    
    template<color c>
    inline void helper(uint64_t, int, move_list&, int);
public:
    void generate_pawn_moves(move_list& list);
    void generate_castle_moves(move_list& list);

    void generate_moves(piece_type, color c, uint64_t bb, move_list& list);
    void generate_all();   

    MoveGenerator(Board b);
};
