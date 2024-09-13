#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include "board.hpp"
#include "Move.hpp"

struct move_list{
    Move moves[256];
    int count;
    
    move_list() : count(0){}

    void add_move(int source, int target, int piece, int promoted, int flags){
        moves[count++] = Move(source, target, piece, promoted, flags);
    }

    void print(State *st, int ply, Heuristics& h){
        printf("\n     move    piece     capture   double    enpass    castling promoted  score\n\n");
        for(int i = 0; i < count; i++){
            printf("      %s%s   %c         %d         %d         %d         %d        %c         %d\n", table.square_map[moves[i].source()].c_str(), 
                table.square_map[moves[i].target()].c_str(), 
                table.pieces[moves[i].piece()],
                moves[i].capture() ? 1 : 0,
                moves[i].double_push() ? 1 : 0,
                moves[i].enpassant() ? 1 : 0,
                moves[i].castling() ? 1 : 0,
                moves[i].promoted() ? table.pieces[moves[i].promoted()] : '-',
                moves[i].score(st, ply, h));
        }
        std::cout << "move count = " << count << "\n";
    }

    Move* begin() {return moves;}
    Move* end() {return &moves[count];};

    inline move_list sort(State *st, int ply, Heuristics& h){
        std::sort(begin(), end(), [st, ply, &h](Move& a, Move& b){
            return a.score(st, ply, h) > b.score(st, ply, h);
        });
        return *this;
    }
};

move_list generate_all(Board& board);