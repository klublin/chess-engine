#include "State.hpp"
#include "tables.hpp"

void State::generate_hash(){
    for(int p = P; p < no_piece; p++){
        uint64_t board = bitboards[p];

        while(board){
            Square square = static_cast<Square>(get_lsb_index(board));

            hash_key ^= table.piece_keys[p][square];
            board &= (board - 1);
        }
    }

    if(enpessant!= none){
        hash_key ^= table.enpassant_keys[enpessant];
    }

    hash_key ^= table.castling_keys[castling_rights];
    
    if(side == BLACK) hash_key ^= table.side_key;
}