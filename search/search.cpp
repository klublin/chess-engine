#include "State.hpp"
#include "eval.hpp"
#include "MoveGenerator.hpp"
#include "search.hpp"
#include <cassert>

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

    for(const auto& m : generate_all(b).sort(st, ply)){
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
    pv_length[ply] = ply;
    if(depth == 0){
        return quiescence(b, alpha, beta);
    }

    if(ply > (Extremes::MAX_PLY - 1)){
        return Evaluation::score_material(b.get_state());
    }

    State *st = b.get_state();
    nodes++;

    bool in_check = b.attacked(static_cast<Square>(get_lsb_index(st->bitboards[K + st->side])), ~st->side);

    if(in_check) depth++;
    int legal_moves = 0;


    for(const auto& m : generate_all(b).sort(st, ply)){
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
            if(m.capture() == 0){
                Table&t = b.table;
                t.killer_moves[1][ply] = t.killer_moves[0][ply];
                t.killer_moves[0][ply] = m.get_data();
            }

            return beta;
        }

        if(score > alpha){
            if(m.capture() == 0){
                Table&t = b.table;
                t.history_moves[m.piece()][m.target()] += depth;
            }
            alpha = score;

            pv_table[ply][ply] = m;

            for(int next_ply = ply + 1; next_ply < pv_length[ply + 1]; next_ply++){
                pv_table[ply][next_ply] = pv_table[ply + 1][next_ply];
            }

            pv_length[ply] = pv_length[ply+1];
        }

    }

    if(legal_moves == 0){
        if(in_check){
            return -49000 + ply;
        }
        return 0;
    }

    return alpha;
}


void Search::begin_search(Board& board, int depth){
    Table& t = Table::get_instance();
    t.history_moves.fill({0});
    t.killer_moves.fill({0});
    pv_length.fill(0);
    pv_table.fill({Move::none()});
    ply = 0;
    nodes = 0;
    
    for(int curr_depth = 1; curr_depth <= depth; curr_depth++){
        int score = negamax(board, Extremes::MIN, Extremes::MAX, curr_depth);
        std::cout << "info score cp " << score << " depth " << curr_depth << " nodes " << nodes << " ";

        for(int i = 0; i < pv_length[0]; i++){
            pv_table[0][i].print(t);
        }
        std::cout << "\n";
    }

    std::cout << "bestmove ";
    pv_table[0][0].print(Table::get_instance());
}