#include "State.hpp"
#include "eval.hpp"
#include "MoveGenerator.hpp"
#include "search.hpp"
#include <cassert>
#include "types.hpp"

int Search::quiescence(Board& b, int alpha, int beta){
    State *st = b.get_state();
    nodes++;

    if(ply > (Extremes::MAX_PLY - 1)){
        return Evaluation::score_material(st);
    }

    int evaluation = Evaluation::score_material(st);
    if(evaluation >= beta){
        return beta;
    }
    if(evaluation > alpha){
        alpha = evaluation;
    }

    for(const auto& m : generate_all(b).sort(st, ply, heuristics)){
        ply++;

        if(!b.make_capture(m)){
            ply--;
            continue;
        }

        int score = -quiescence(b, -beta, -alpha);
        
        ply--;

        b.unmake_move(m);

        if(score > alpha){
            alpha = score;

            if(score >= beta){
                return beta;
            }
        }
    }
    return alpha;
}   

int Search::negamax(Board& b, Transposition_table& tt, int alpha, int beta, int depth){
    State *st = b.get_state();
    int score;
    Hash_Flags flag = Hash_Flags::ALPHA;
    bool pv_node = (beta - alpha) > 1;
    if(ply!=0 && (score = tt.read_hash(st->hash_key, alpha, beta, depth, ply))!= Hash_Flags::NO_HASH_ENTRY && !pv_node){
        return score;
    }

    heuristics.pv_length[ply] = ply;

    if(depth == 0){
        return quiescence(b, alpha, beta);
    }

    if(ply > (Extremes::MAX_PLY - 1)){
        return Evaluation::score_material(st);
    }

    nodes++;
    bool in_check = b.attacked(static_cast<Square>(get_lsb_index(st->bitboards[K + st->side])), ~st->side);
    if(in_check) depth++;

    //null move pruning
    if(depth >= 3 && !in_check && ply){
        b.save_state();
        ply++;

        st->side = ~st->side;
        st->hash_key ^= table.side_key;

        if(st->enpessant!= none) st->hash_key ^= table.enpassant_keys[st->enpessant];
        st->enpessant = none;

        score = -negamax(b, tt, -beta, -beta + 1, depth - 1 - 2);

        b.unmake_move(Move::none());
        ply--;

        if(score >= beta){
            return beta;
        }
    }

    int legal_moves = 0;
    int moves_searched = 0;

    for(const auto& m : generate_all(b).sort(st, ply, heuristics)){
        ply++;
        if(!b.make_move(m)){
            ply--;
            continue;
        }

        legal_moves++;
        
        if(moves_searched == 0){
            score = -negamax(b, tt, -beta, -alpha, depth - 1);
        }
        else{
            if(
                moves_searched >= FULL_DEPTH_MOVES && 
                depth >= REDUCTION_LIMIT && 
                !in_check && 
                m.capture() == 0 && m.promoted() == 0
            ){
                score = -negamax(b, tt, -alpha - 1, -alpha, depth - 2);
            }
            else{
                score = alpha + 1;
            }

            if(score > alpha)
            {
                score = -negamax(b, tt, -alpha - 1, -alpha, depth -1);

                if((score > alpha) && (score < beta)){
                    score = -negamax(b, tt, -beta, -alpha, depth - 1);
                }
            }
        }

        ply--;            
        b.unmake_move(m);
        moves_searched++;

        if(score > alpha){
            flag = Hash_Flags::EXACT;
            if(m.capture() == 0){
                heuristics.history_moves[m.piece()][m.target()] += depth;
            }
            alpha = score;

            heuristics.pv_table[ply][ply] = m;

            for(int next_ply = ply + 1; next_ply < heuristics.pv_length[ply + 1]; next_ply++){
                heuristics.pv_table[ply][next_ply] = heuristics.pv_table[ply + 1][next_ply];
            }

            heuristics.pv_length[ply] = heuristics.pv_length[ply+1];

            if(score >= beta){
                tt.write_hash(st->hash_key, beta, depth, ply, Hash_Flags::BETA);

                if(m.capture() == 0){
                    heuristics.killer_moves[1][ply] = heuristics.killer_moves[0][ply];
                    heuristics.killer_moves[0][ply] = m.get_data();
                }
                return beta;
            }
        }
    }

    if(legal_moves == 0){
        if(in_check){
            return -MATE_VALUE + ply;
        }
        return 0;
    }

    tt.write_hash(st->hash_key, alpha, depth, ply, flag);

    return alpha;
}