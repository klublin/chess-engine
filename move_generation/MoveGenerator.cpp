#include <iostream>
#include <cassert>
#include "MoveGenerator.hpp"

template<color c>
inline void helper(uint64_t board, int incr, move_list& list, int flags){
	while(board){
		int dest = get_lsb_index(board);
		int source = dest + incr;
		list.add_move(source, dest, P + c, 0, flags);
		board &= (board - 1);
	}
}

template<color c>
inline void helper_promo(uint64_t board, int incr, move_list& list, int flags){
	while(board){
		int dest = get_lsb_index(board);
		int source = dest + incr;
        list.add_move(source, dest, P + c, Q + c, flags);
        list.add_move(source, dest, P + c, R + c, flags);
        list.add_move(source, dest, P + c, B + c, flags);
        list.add_move(source, dest, P + c, N + c, flags);
		board &= (board - 1);
	}
}

void generate_pawn_moves(State* st, move_list& list, Table& t){
    //need to add each move to a movelist
    if(st->side == WHITE){
        uint64_t promote = st->bitboards[P] & t.mask_rank[RANK_7];
        uint64_t pawns = st->bitboards[P] & t.clear_rank[RANK_7];

        //quiet moves
        uint64_t push = (pawns >> 8) & ~st->occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_3]) >> 8) & ~st->occup[OCCUP_ALL];

        helper<WHITE>(push, 8, list, 0);
        helper<WHITE>(double_push, 16, list, DOUBLE);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_H]) >> 7) & st->occup[OCCUP_BLACK];
        uint64_t b2 = ((promote & t.clear_file[FILE_A]) >> 9) & st->occup[OCCUP_BLACK];
        uint64_t b3 = promote >> 8 & ~st->occup[OCCUP_ALL];

        helper_promo<WHITE>(b1, 7, list, CAPTURE);
        helper_promo<WHITE>(b2, 9, list, CAPTURE);
        helper_promo<WHITE>(b3, 8, list, 0);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & st->occup[OCCUP_BLACK];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & st->occup[OCCUP_BLACK];

        helper<WHITE>(cap1, 7, list, CAPTURE);
        helper<WHITE>(cap2, 9, list, CAPTURE);
        
        if(st->enpessant != none){  
            cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & get_square(st->enpessant);
            cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & get_square(st->enpessant);
            
            helper<WHITE>(cap1, 7, list, ENPASSANT | CAPTURE);
            helper<WHITE>(cap2, 9, list, ENPASSANT | CAPTURE);
        }
    }
    else{
        uint64_t promote = st->bitboards[p] & t.mask_rank[RANK_2];
        uint64_t pawns = st->bitboards[p] & t.clear_rank[RANK_2];

        //quiet moves
        uint64_t push = (pawns << 8) & ~st->occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_6]) << 8) & ~st->occup[OCCUP_ALL];

        helper<BLACK>(push, -8, list, 0);
        helper<BLACK>(double_push, -16, list, DOUBLE);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_A]) << 7) & st->occup[OCCUP_WHITE];
        uint64_t b2 = ((promote & t.clear_file[FILE_H]) << 9) & st->occup[OCCUP_WHITE];
        uint64_t b3 = promote << 8 & ~st->occup[OCCUP_ALL];

        helper_promo<BLACK>(b1, -7, list, CAPTURE);
        helper_promo<BLACK>(b2, -9, list, CAPTURE);
        helper_promo<BLACK>(b3, -8, list, 0);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & st->occup[OCCUP_WHITE];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & st->occup[OCCUP_WHITE];

        helper<BLACK>(cap1, -7, list, CAPTURE);
        helper<BLACK>(cap2, -9, list, CAPTURE);

        if(st->enpessant != none){
            cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & get_square(st->enpessant);
            cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & get_square(st->enpessant);
            helper<BLACK>(cap1, -7, list, ENPASSANT | CAPTURE);
            helper<BLACK>(cap2, -9, list, ENPASSANT | CAPTURE);
        }
    }
}

void generate_castle_moves(Board& board, move_list& list){
    State *st = &board.st;
    if(st->side == WHITE){
        if((st->castling_rights & WK)!=0){
            if((st->occup[OCCUP_ALL] & get_square(f1)) == 0 && (st->occup[OCCUP_ALL] & get_square(g1)) == 0){
                if(!board.attacked(f1, BLACK) && !board.attacked(e1, BLACK)){
                    list.add_move(e1, g1, K, 0, CASTLING);
                }
            }
        }

        if((st->castling_rights & WQ)!= 0){
            if((st->occup[OCCUP_ALL] & get_square(b1)) == 0 && (st->occup[OCCUP_ALL] & get_square(c1)) == 0 && (st->occup[OCCUP_ALL] & get_square(d1)) == 0){
                if(!board.attacked(e1, BLACK) && !board.attacked(d1, BLACK)){
                    list.add_move(e1, c1, K, 0, CASTLING);
                }
            }
        }
    }
    else{
        if((st->castling_rights & BK)!=0){
            if((st->occup[OCCUP_ALL] & get_square(f8)) == 0 && (st->occup[OCCUP_ALL] & get_square(g8)) == 0){
                if(!board.attacked(e8, WHITE) && !board.attacked(f8, WHITE)){
                    list.add_move(e8, g8, k, 0, CASTLING);
                }
            }
        }

        if((st->castling_rights & BQ)!= 0){
            if((st->occup[OCCUP_ALL] & get_square(b8)) == 0 && (st->occup[OCCUP_ALL] & get_square(c8)) == 0 && (st->occup[OCCUP_ALL] & get_square(d8)) == 0){
                if(!board.attacked(e8, WHITE) && !board.attacked(d8, WHITE)){
                    list.add_move(e8, c8, k, 0, CASTLING);
                }
            }
        }
    }
}

template <Piece_type pt>
void generate_moves(Board& b, move_list& list){
    State *st = &b.st;
    uint64_t bb = st->bitboards[pt + st->side];
    color us = st->side;
    color them = ~us;

    while(bb){
        Square source = static_cast<Square>(get_lsb_index(bb));
        uint64_t moves = b.get_attack_bb<pt>(source) & ~(st->occup[us]);

        while(moves){
            Square dest_sq = static_cast<Square>(get_lsb_index(moves));
            uint64_t capture = get_square(dest_sq) & (st->occup[them]);
           
            list.add_move(source, dest_sq, pt+st->side, 0, capture ? CAPTURE : 0);
            moves &= (moves - 1);
        }
        bb &= (bb - 1);
    }
}

move_list generate_all(Board& board){
    move_list list;
    State *st = board.get_state();
    generate_pawn_moves(st, list, board.table);
    generate_castle_moves(board, list);

    generate_moves<KING>(board, list);
    generate_moves<QUEEN>(board, list);
    generate_moves<ROOK>(board, list);
    generate_moves<BISHOP>(board, list);
    generate_moves<KNIGHT>(board, list);
    
    return list;
}

Table& move_list::t(Table::get_instance());