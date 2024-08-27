#include "eval.hpp"
#include "board.hpp"
#include <iostream>

template<color c>
inline int score_board(uint64_t board, int piece){
    int score = 0;

    while(board){
        int square = get_lsb_index(board);
        if(c == BLACK)
            score -= positional_scores[piece][square];
        else{
            score += positional_scores[piece][square];
        }
        score += material_score[piece];
        board &= (board - 1);
    }
    return score;
}

int score_material(State& st){

    int score = 0;

    for(Piece_type pt : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING}){
        uint64_t white = st.bitboards[pt];
        uint64_t black = st.bitboards[pt + BLACK];

        score += score_board<WHITE>(white, pt);
        score += score_board<BLACK>(black, pt + BLACK);
    }

    return st.side == WHITE ? score : -score;
}

int main(){
    Board b(start_position);

    std::cout << score_material(b.st) << "\n";
}