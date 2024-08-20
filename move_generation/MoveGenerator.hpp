#pragma once
#include <string>
#include <iostream>
#include "board.hpp"

struct move_list{
    Move moves[256];
    static Table& t;
    int count;
    
    move_list() : count(0){}

    void add_move(int source, int target, int piece, int promoted, int flags){
        moves[count++] = Move(source, target, piece, promoted, flags);
    }

    void print(){
        printf("\n     move    piece     capture   double    enpass    castling promoted\n\n");
        for(int i = 0; i < count; i++){
            printf("      %s%s   %c         %d         %d         %d         %d        %c\n", t.square_map[moves[i].source()].c_str(), 
                t.square_map[moves[i].target()].c_str(), 
                t.pieces[moves[i].piece()],
                moves[i].capture() ? 1 : 0,
                moves[i].double_push() ? 1 : 0,
                moves[i].enpassant() ? 1 : 0,
                moves[i].castling() ? 1 : 0,
                moves[i].promoted() ? t.pieces[moves[i].promoted()] : '-');
        }
        std::cout << "move count = " << count << "\n";
    }

    const Move* begin() const {return moves;}
    const Move* end() const {return &moves[count];};
};

move_list generate_all(Board& board);