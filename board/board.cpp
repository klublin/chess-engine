#include "board.hpp"
#include <iostream>
#include <cassert>

void print_bitboard(uint64_t board){
    for(int i = 0; i < 8; i++){
        std::cout << (8 - i) << "   ";
        for(int j = 0; j < 8; j++){
            uint64_t mask = 1ULL << (i*8+j);
            std::cout << ((board & mask) != 0 ? '1' : '0') << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n    ";
    for(char c = 'a'; c <= 'h'; c++){
        std::cout << c << ' ';
    }
    std::cout << "\n";
}

inline void pop_bit(uint64_t& board, int s){
    board &= ~(1ULL << s);
}

inline void set_bit(uint64_t& board, int s){
    board |= (1ULL << s);
}

template <color c>
inline uint64_t Board::get_pawn_attack(square s){
    return table.pawn_attack_table[c][s];
}

uint64_t Board::get_attack_bb(piece_type p, square s){
    uint64_t rook_attack;
    uint64_t attack;
    switch(p){
        case ROOK:
            rook_attack = table.rook_attack_table[s];
            rook_attack &= occup[OCCUP_ALL];
            rook_attack *= table.rook_magics[s];
            rook_attack >>= (64 - table.rook_occupancy_bits[s]);
            return table.rook_table[s][rook_attack];  
        case BISHOP:
            attack = table.bishop_attack_table[s]; 
            attack &= occup[OCCUP_ALL];
            attack *= table.bishop_magics[s];
            attack >>= (64 - table.bishop_occupancy_bits[s]);
            return table.bishop_table[s][attack];   
        case QUEEN:
            return get_attack_bb(ROOK, s) | get_attack_bb(BISHOP, s);
        case KNIGHT:
            return table.knight_attack_table[s];
        case KING:
            return table.king_attack_table[s];
        default:
            return 0;
    }
}

//checks if current square is attacked by given by the side 
bool Board::attacked(square s, color side){
    if((side == WHITE) && (get_pawn_attack<BLACK>(s) & bitboards[P])) return true;
    
    //we wonder if the current square is being attacked by a black pawn. White pawns attack looks something like:
    /*
        1 0 1
        0 P 0
        if we have a black pawn on any of those attack squares then it means that there is a black pawn attacking the current square
    */
    if((side == BLACK && (get_pawn_attack<WHITE>(s) & bitboards[p]))) return true;

    if(get_attack_bb(KNIGHT, s) & (side == WHITE ? bitboards[N] : bitboards[n])) return true;
    
    if(get_attack_bb(KING, s) & (side == WHITE ? bitboards[K] : bitboards[k])) return true;
    
    if(get_attack_bb(BISHOP, s) & (side == WHITE ? bitboards[B] : bitboards[b])) return true;

    if(get_attack_bb(ROOK, s) & (side == WHITE ? bitboards[R] : bitboards[r])) return true;

    if(get_attack_bb(QUEEN, s) & (side == WHITE ? bitboards[Q] : bitboards[q])) return true;

    return false;
}

inline int Board::check_is_piece(char c){
    for(int i = 0; i < 12; i++){
        if(table.pieces[i] == c){
            return i;
        }
    }
    return -1;
}
void Board::read_fen(const std::string& fen){
    //our enum square starts at a8, where the fen string starts
    std::cout << fen << "\n";
    int index = 0;

    for(int square = 0; square < 64; index++){
        int code = check_is_piece(fen[index]);
        
        if(code!= -1){
            bitboards[code] |= 1ULL << square;
            square++;
        }
        else if(fen[index] >= '1' && fen[index] <= '8'){
            square += (fen[index] - '0');
        }
    }
    //should be a space now
    assert(fen[index] == ' ');
    index++;

    side = fen[index] == 'w' ? WHITE : BLACK;
    index+=2;

    //we are now at the castling
    while(fen[index]!= ' '){
        switch(fen[index]){
            case 'K': castling_rights |= WK; break;
            case 'Q': castling_rights |= WQ; break;
            case 'k': castling_rights |= BK; break;
            case 'q': castling_rights |= BQ; break;
            default: break;
        }
        index++;
    }
    index++;

    //en passant square
    if(fen[index] == '-'){
        enpessant = none;
    }
    else{
        int file = fen[index++] - 'a';
        int rank = 8 - (fen[index] - '0');
        int s = rank * 8 + file;

        enpessant = static_cast<square>(s);
    }

    for(int i = 0; i < NUM_PIECES; i++){
        occup[OCCUP_WHITE] |= bitboards[i];
        occup[OCCUP_BLACK] |= bitboards[i + BLACK];
    }
    occup[OCCUP_ALL] = occup[OCCUP_WHITE] | occup[OCCUP_BLACK];
}

Piece Board::which_piece(const int s){
    uint64_t board = get_square(static_cast<square>(s));
    for(int i = 0; i < 12; i++){
        if((bitboards[i] & board) != 0)
            return static_cast<Piece>(i);
    }
    return no_piece;
}

void Board::print(){
    for(int i = 0; i < 8; i++){
        std::cout << (8 - i) << "   ";
        for(int j = 0; j < 8; j++){
            std::cout << table.symbol_map.at(which_piece(i*8+j)) << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n    ";
    for(char c = 'a'; c <= 'h'; c++){
        std::cout << c << ' ';
    }
    std::cout << "\n";

    if(castling_rights & WK){
        std::cout << 'K';
    }
    else{
        std::cout << '-';
    }

    if(castling_rights & WQ){
        std::cout << 'Q';
    }
    else{
        std::cout << '-';
    }

    if(castling_rights & BK){
        std::cout << 'k';
    }
    else{
        std::cout << '-';
    }

    if(castling_rights & BQ){
        std::cout << 'q';
    }
    else{
        std::cout << '-';
    }
    std::cout << "\n";
    if(enpessant!= none){
        std::cout << table.square_map[enpessant] << "\n";
    }
    else{
        std::cout << "-\n";
    }
    std::cout << "\n";
}

inline void Board::unmake_move(){
    bitboards = prev_bitboards;
    occup = prev_occup;
    enpessant = prev_enpessant;
    side = prev_side;
    castling_rights = prev_castling;
}

inline void Board::update_bitboards(int piece, int from, int to){
    pop_bit(bitboards[piece], from);
    pop_bit(occup[OCCUP_ALL], from);
    pop_bit(occup[OCCUP_WHITE], from);
    set_bit(bitboards[piece], to);
    set_bit(occup[OCCUP_ALL], to);
    set_bit(occup[OCCUP_WHITE], to);

}

void Board::make_move(int source, int dest, int piece, int promoted, int flag){
    prev_bitboards = bitboards;
    prev_occup = occup;
    prev_enpessant = enpessant;
    prev_side = side;
    prev_castling = castling_rights;

    update_bitboards(piece, source, dest);
    if(flag & CASTLING){
        switch(dest){
            case g1:
                update_bitboards(R, h1, f1);              
                break;
            case c1:
                update_bitboards(R, a1, d1);
                break;
            case g8:
                update_bitboards(r, h1, f1);
                break;
            case c8:
                update_bitboards(r, a8, d8);
                break;
        }
    }
    else if(flag & ENPASSANT){
        //clear piece from board
        side == WHITE ? update_bitboards(p, dest + 8, none): update_bitboards(P, dest - 8, none);
        enpessant = none;
    }
    else if(flag & CAPTURE){
        Piece captured = which_piece(dest);        
        update_bitboards(captured, dest, none);
    }
    else if(flag & DOUBLE){
        side == WHITE ? enpessant = static_cast<square>(dest + 8) : enpessant = static_cast<square>(dest - 8);
    }
    else if(promoted){
        //pawn gets "captured"
        update_bitboards(piece, source, none);
        update_bitboards(promoted, none, dest);
    }

    castling_rights &= table.castle_rights_table[source];
    castling_rights &= table.castle_rights_table[dest];

    side = side ^ BLACK;

    if(attacked((side == WHITE ? static_cast<square>(get_lsb_index(bitboards[K])) : static_cast<square>(get_lsb_index(bitboards[k]))), side)){
        unmake_move();
    }
}

void Board::debug(uint64_t b){
    //read_fen("8/8/8/3N4/8/8/8/8 w KQkq - 0 1 ");
    print_bitboard(b);
}

Board::Board() : table(Table::get_instance()),  
        bitboards{0}, occup{0}, side(WHITE) , enpessant(none){}