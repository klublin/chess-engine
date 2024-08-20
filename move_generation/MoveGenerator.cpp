#include "MoveGenerator.hpp"
#include <iostream>

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

void generate_pawn_moves(Board& board, move_list& list, Table& t){
    //need to add each move to a movelist
    if(board.side == WHITE){
        uint64_t promote = board.bitboards[P] & t.mask_rank[RANK_7];
        uint64_t pawns = board.bitboards[P] & t.clear_rank[RANK_7];

        //quiet moves
        uint64_t push = (pawns >> 8) & ~board.occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_3]) >> 8) & ~board.occup[OCCUP_ALL];

        helper<WHITE>(push, 8, list, 0);
        helper<WHITE>(double_push, 16, list, DOUBLE);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_H]) >> 7) & board.occup[OCCUP_BLACK];
        uint64_t b2 = ((promote & t.clear_file[FILE_A]) >> 9) & board.occup[OCCUP_BLACK];
        uint64_t b3 = promote >> 8 & ~board.occup[OCCUP_ALL];

        helper_promo<WHITE>(b1, 7, list, CAPTURE);
        helper_promo<WHITE>(b2, 9, list, CAPTURE);
        helper_promo<WHITE>(b3, 8, list, 0);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & board.occup[OCCUP_BLACK];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & board.occup[OCCUP_BLACK];

        helper<WHITE>(cap1, 7, list, CAPTURE);
        helper<WHITE>(cap2, 9, list, CAPTURE);

        if(board.enpessant != none){
            cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & 1 << board.enpessant;
            cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & 1 << board.enpessant;
            
            helper<WHITE>(cap1, 7, list, ENPASSANT | CAPTURE);
            helper<WHITE>(cap2, 9, list, ENPASSANT | CAPTURE);
        }
    }
    else{
        uint64_t promote = board.bitboards[p] & t.mask_rank[RANK_2];
        uint64_t pawns = board.bitboards[p] & t.clear_rank[RANK_2];

        //quiet moves
        uint64_t push = (pawns << 8) & ~board.occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_6]) << 8) & ~board.occup[OCCUP_ALL];

        helper<BLACK>(push, -8, list, 0);
        helper<BLACK>(double_push, -16, list, DOUBLE);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_A]) << 7) & board.occup[OCCUP_WHITE];
        uint64_t b2 = ((promote & t.clear_file[FILE_H]) << 9) & board.occup[OCCUP_WHITE];
        uint64_t b3 = promote << 8 & ~board.occup[OCCUP_ALL];

        helper_promo<BLACK>(b1, -7, list, CAPTURE);
        helper_promo<BLACK>(b2, -9, list, CAPTURE);
        helper_promo<BLACK>(b3, -8, list, 0);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & board.occup[OCCUP_WHITE];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & board.occup[OCCUP_WHITE];

        helper<BLACK>(cap1, -7, list, CAPTURE);
        helper<BLACK>(cap2, -9, list, CAPTURE);

        if(board.enpessant != none){
            cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & 1 << board.enpessant;
            cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & 1 << board.enpessant;
            
            helper<BLACK>(cap1, -7, list, ENPASSANT | CAPTURE);
            helper<BLACK>(cap2, -9, list, ENPASSANT | CAPTURE);
        }
    }
}

void generate_castle_moves(Board& board, move_list& list){
    if(board.side == WHITE){
        if((board.castling_rights & WK)!=0){
            if((board.occup[OCCUP_ALL] & (1ULL << f1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << g1)) == 0){
                if(!board.attacked(f1, BLACK) && !board.attacked(g1, BLACK)){
                    list.add_move(e1, h1, K, 0, CASTLING);
                }
            }
        }

        if((board.castling_rights & WQ)!= 0){
            if((board.occup[OCCUP_ALL] & (1ULL << b1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << c1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << d1)) == 0){
                if(!board.attacked(c1, BLACK) && !board.attacked(d1, BLACK)){
                    list.add_move(e1, a1, K, 0, CASTLING);
                }
            }
        }
    }
    else{
        if((board.castling_rights & BK)!=0){
            if((board.occup[OCCUP_ALL] & (1ULL<< f8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << g8)) == 0){
                if(!board.attacked(f8, WHITE) && !board.attacked(g8, WHITE)){
                    list.add_move(e8, h8, k, 0, CASTLING);
                }
            }
        }

        if((board.castling_rights & BQ)!= 0){
            if((board.occup[OCCUP_ALL] & (1ULL << b8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << c8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << d8)) == 0){
                if(!board.attacked(c8, WHITE) && !board.attacked(d8, WHITE)){
                    list.add_move(e8, h8, k, 0, CASTLING);
                }
            }
        }
    }
}

template <piece_type pt>
void generate_moves(Board& b, move_list& list){
    uint64_t bb = b.bitboards[pt + b.side];

    while(bb){
        int source = get_lsb_index(bb);
        uint64_t moves = b.get_attack_bb(pt, static_cast<square>(source)) & ~(b.side == WHITE ? b.occup[OCCUP_WHITE] : b.occup[OCCUP_BLACK]); 

        while(moves){
            int dest_sq = get_lsb_index(moves);
            int capture = (1ULL << dest_sq) & (b.side == WHITE ? b.occup[OCCUP_BLACK] : b.occup[OCCUP_WHITE]);

            list.add_move(source, dest_sq, pt+b.side, 0, capture ? CAPTURE : 0);
            moves &= (moves - 1);
        }
        bb &= (bb - 1);
    }
}

move_list generate_all(Board& board){
    move_list list;
    generate_pawn_moves(board, list, board.table);
    generate_castle_moves(board, list);

    generate_moves<KING>(board, list);
    generate_moves<QUEEN>(board, list);
    generate_moves<ROOK>(board, list);
    generate_moves<BISHOP>(board, list);
    
    return list;
}

Table& move_list::t(Table::get_instance());