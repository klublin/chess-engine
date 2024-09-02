#include "State.hpp"
#include "eval.hpp"
#include "MoveGenerator.hpp"
#include "search.hpp"

std::array<std::array<int, 12>, 12> Search::mva_table{{
   { 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605, },
   { 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604, },
   { 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603, },
   { 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602, },
   { 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601, },
   { 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600, },
   { 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605, },
   { 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604, },
   { 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603, },
   { 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602, },
   { 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601, },
   { 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600, },
}};


int Search::quiescence(Board& b, int alpha, int beta){
    nodes++;

    int evaluation = Evaluation::score_material(b.st);

    if(evaluation >= beta){
        return beta;
    }

    if(evaluation > alpha){
        alpha = evaluation;
    }

    for(const auto& m : generate_all(b)){
        ply++;

        if(!b.make_move(m)){
            ply--;
            continue;
        }

        int score = -quiescence(b, -beta, -alpha);
        
        ply--;

        b.unmake_move(m);

        if(score >= beta){
            return beta;
        }
        if(score > alpha){
            alpha = score;
        }
    }
    return alpha;
}   

int Search::negamax(Board& b, int alpha, int beta, int depth){
    std::cout << "depth " << depth << "\n";
    if(depth == 0){
        std::cout << alpha << " " << beta << "\n";
        return quiescence(b, alpha, beta);
    }
    State *st = b.get_state();
    nodes++;

    Move best_so_far;

    bool in_check = b.attacked(static_cast<Square>(get_lsb_index(st->bitboards[K + st->side])), ~st->side);
    int legal_moves = 0;

    int old_alpha = alpha;

    for(const auto& m : generate_all(b)){
        ply++;
        if(!b.make_move(m)){
            ply--;
            continue;
        }

        legal_moves++;

        int score = -negamax(b, -beta, -alpha, depth - 1);

        ply--;            
        b.unmake_move(m);

        if(score >= beta){
            return beta;
        }

        if(score > alpha){
            alpha = score;

            if(ply == 0){
                best_so_far = m;
            }
        }

    }

    if(legal_moves == 0){
        if(in_check){
            return -49000 + ply;
        }
        return 0;
    }

    if(old_alpha!= alpha){
        best_move = best_so_far;
    }
    return alpha;
}