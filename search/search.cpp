#include "State.hpp"
#include "eval.hpp"
#include "MoveGenerator.hpp"
#include "search.hpp"
#include <cassert>

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
    State *st = b.get_state();
    int evaluation = Evaluation::score_material(st);

    if(evaluation >= beta){
        return beta;
    }

    if(evaluation > alpha){
        alpha = evaluation;
    }

    move_list l = generate_all(b);

    // for(const auto& m : l){
    //     if(m.source() == d5 && m.target() == c6 && m.capture()){
    //         std::cout << Table::get_instance().pieces[m.piece()] << " " << m.capture() << "\n";
    //         b.print();
    //         assert(false);
    //     }
    // }
    l.sort(st, ply);

    for(const auto& m : l){
        ply++;

        if(!b.make_capture(m)){
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
    if(depth == 0){
        return quiescence(b, alpha, beta);
    }
    State *st = b.get_state();
    nodes++;

    Move best_so_far;

    bool in_check = b.attacked(static_cast<Square>(get_lsb_index(st->bitboards[K + st->side])), ~st->side);
    int legal_moves = 0;

    int old_alpha = alpha;

    move_list l = generate_all(b);

    
    // for(const auto& m : l){
    //     if(m.source() == d5 && m.target() == c6 && m.capture()){
    //         b.print();
    //         assert(false);
    //     }
    // }
    l.sort(st, ply);


    for(const auto& m : l){
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