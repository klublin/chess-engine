#include "MoveGenerator.hpp"
#include <iostream>

//template on capture vs non capture
template<color c, uint64_t N>
inline void helper(uint64_t board, int incr, const std::string& s, std::array<std::string, N> square_map){
	while(board){
		int dest = get_lsb_index(board);
		int source = dest + incr;
		std::cout << s << square_map[source] << square_map[dest] << "\n";
		board &= (board - 1);
	}
}

template< color c, uint64_t N>
inline void helper_promo(uint64_t board, int incr, const std::string& s, std::array<std::string, N> square_map){
	while(board){
		int dest = get_lsb_index(board);
		int source = dest + incr;
		std::cout << s << square_map[source] << square_map[dest] << "r\n";
        std::cout << s << square_map[source] << square_map[dest] << "q\n";
		std::cout << s << square_map[source] << square_map[dest] << "n\n";
		std::cout << s << square_map[source] << square_map[dest] << "b\n";
		board &= (board - 1);
	}
}

void MoveGenerator::generate_pawn_moves(){
    //need to add each move to a movelist
    if(board.side == WHITE){
        uint64_t promote = board.bitboards[P] & t.mask_rank[RANK_7];
        uint64_t pawns = board.bitboards[P] & t.clear_rank[RANK_7];

        //quiet moves
        uint64_t push = (pawns >> 8) & ~board.occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_3]) >> 8) & ~board.occup[OCCUP_ALL];

        helper<WHITE>(push, 8, "pawn push ", t.square_map);
        helper<WHITE>(double_push, 16, "pawn double push ", t.square_map);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_H]) >> 7) & board.occup[OCCUP_BLACK];
        uint64_t b2 = ((promote & t.clear_file[FILE_A]) >> 9) & board.occup[OCCUP_BLACK];
        uint64_t b3 = promote >> 8 & ~board.occup[OCCUP_ALL];

        helper_promo<WHITE>(b1, 7, "promotion capture ", t.square_map);
        helper_promo<WHITE>(b2, 9, "promotion capture ", t.square_map);
        helper_promo<WHITE>(b3, 8, "promotion ", t.square_map);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & board.occup[OCCUP_BLACK];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & board.occup[OCCUP_BLACK];

        helper<WHITE>(cap1, 7, "pawn capture ", t.square_map);
        helper<WHITE>(cap2, 9, "pawn capture ", t.square_map);

        if(board.enpessant != none){
            cap1 = ((pawns & t.clear_file[FILE_H]) >> 7) & 1 << board.enpessant;
            cap2 = ((pawns & t.clear_file[FILE_A]) >> 9) & 1 << board.enpessant;
            
            helper<WHITE>(cap1, 7, "enpessant capture ", t.square_map);
            helper<WHITE>(cap2, 9, "enpessant capture ", t.square_map);
        }
    }
    else{
        uint64_t promote = board.bitboards[p] & t.mask_rank[RANK_2];
        uint64_t pawns = board.bitboards[p] & t.clear_rank[RANK_2];

        //quiet moves
        uint64_t push = (pawns << 8) & ~board.occup[OCCUP_ALL];
        uint64_t double_push = ((push & t.mask_rank[RANK_6]) << 8) & ~board.occup[OCCUP_ALL];

        helper<BLACK>(push, -8, "pawn push ", t.square_map);
        helper<BLACK>(double_push, -16, "pawn double push ", t.square_map);

        //promotion
        uint64_t b1 = ((promote & t.clear_file[FILE_A]) << 7) & board.occup[OCCUP_WHITE];
        uint64_t b2 = ((promote & t.clear_file[FILE_H]) << 9) & board.occup[OCCUP_WHITE];
        uint64_t b3 = promote << 8 & ~board.occup[OCCUP_ALL];

        helper_promo<BLACK>(b1, -7, "promotion capture ", t.square_map);
        helper_promo<BLACK>(b2, -9, "promotion capture ", t.square_map);
        helper_promo<BLACK>(b3, -8, "promotion ", t.square_map);

        uint64_t cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & board.occup[OCCUP_WHITE];
        uint64_t cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & board.occup[OCCUP_WHITE];

        helper<BLACK>(cap1, -7, "pawn capture ", t.square_map);
        helper<BLACK>(cap2, -9, "pawn capture ", t.square_map);

        if(board.enpessant != none){
            cap1 = ((pawns & t.clear_file[FILE_A]) << 7) & 1 << board.enpessant;
            cap2 = ((pawns & t.clear_file[FILE_H]) << 9) & 1 << board.enpessant;
            
            helper<BLACK>(cap1, -7, "enpessant capture ", t.square_map);
            helper<BLACK>(cap2, -9, "enpessant capture ", t.square_map);
        }
    }
}

void MoveGenerator::generate_king_moves(){
    uint64_t kings = board.side == WHITE ? board.bitboards[K] : board.bitboards[k];
    board.side == WHITE ? generate_moves<KNIGHT, WHITE>(kings) : generate_moves<KNIGHT, BLACK>(kings);

    if(board.side == WHITE){
        if((board.castling_rights & WK)!=0){
            if((board.occup[OCCUP_ALL] & (1ULL << f1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << g1)) == 0){
                if(!board.attacked(f1, BLACK) && !board.attacked(g1, BLACK)){
                    std::cout << "king castle e1h1\n";
                }
            }
        }

        if((board.castling_rights & WQ)!= 0){
            if((board.occup[OCCUP_ALL] & (1ULL << b1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << c1)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << d1)) == 0){
                if(!board.attacked(c1, BLACK) && !board.attacked(d1, BLACK)){
                    std::cout << "king castle e1a1\n";
                }
            }
        }
    }
    else{
        if((board.castling_rights & BK)!=0){
            if((board.occup[OCCUP_ALL] & (1ULL<< f8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << g8)) == 0){
                if(!board.attacked(f8, WHITE) && !board.attacked(g8, WHITE)){
                    std::cout << "king castle e1h1\n";
                }
            }
        }

        if((board.castling_rights & BQ)!= 0){
            if((board.occup[OCCUP_ALL] & (1ULL << b8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << c8)) == 0 && (board.occup[OCCUP_ALL] & (1ULL << d8)) == 0){
                if(!board.attacked(c8, WHITE) && !board.attacked(d8, WHITE)){
                    std::cout << "king castle e1a1\n";
                }
            }
        }
    }
}

void MoveGenerator::generate_rook_moves(){
    uint64_t rooks = board.side == WHITE ? board.bitboards[R] : board.bitboards[r];

    board.side == WHITE ? generate_moves<KNIGHT, WHITE>(rooks) : generate_moves<KNIGHT, BLACK>(rooks);
}


void MoveGenerator::generate_bishop_moves(){
    uint64_t bishops = board.side == WHITE ? board.bitboards[B] : board.bitboards[b];

    board.side == WHITE ? generate_moves<KNIGHT, WHITE>(bishops) : generate_moves<KNIGHT, BLACK>(bishops);
}

void MoveGenerator::generate_knight_moves(){
    uint64_t knights = board.side == WHITE ? board.bitboards[N] : board.bitboards[n];

    board.side == WHITE ? generate_moves<KNIGHT, WHITE>(knights) : generate_moves<KNIGHT, BLACK>(knights);
}

//pt + c will give type of piece
template <piece_type pt, color c>
void MoveGenerator::generate_moves(uint64_t bb){
    while(bb){
        int source = get_lsb_index(bb);
        uint64_t moves = board.get_attack_bb<pt>(static_cast<square>(source), 
                        board.occup[OCCUP_ALL]) & ~((board.side == WHITE) ? board.occup[OCCUP_WHITE] : board.occup[OCCUP_BLACK]); 

        while(moves){
            int dest_sq = get_lsb_index(moves);
            int capture = (1ULL << dest_sq) & (board.side == WHITE ? board.occup[OCCUP_BLACK] : board.occup[OCCUP_WHITE]);
            
            if(capture){
                std::cout << "knight capture " << t.square_map[source] << t.square_map[dest_sq] << "\n";
            }
            else{
                std::cout << "knight move " << t.square_map[source] << t.square_map[dest_sq] << "\n";
            }

            moves &= (moves - 1);
        }
        bb &= (bb - 1);
    }
}


MoveGenerator::MoveGenerator(Board b) : board(b), t(Table::get_instance()){

}

int main(){
    Board b;
    b.read_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 ");
    b.print();
    MoveGenerator m(b);
    // m.generate_bishop_moves();
    // m.generate_rook_moves();
    // m.generate_king_moves();
    // m.generate_pawn_moves();
    m.generate_knight_moves();


}
