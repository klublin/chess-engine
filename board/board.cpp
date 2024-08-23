#include <iostream>
#include <cassert>
#include "board.hpp"
#include "MoveGenerator.hpp"
#include "Move.hpp"

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

template<pawns p>
inline uint64_t Board::get_pawn_attack(square s){
    	return table.pawn_attack_table[p][s];
}

uint64_t Board::get_attack_bb(piece_type p, square s){
    uint64_t rook_attack;
    uint64_t attack;
    switch(p){
        case ROOK:
            rook_attack = table.rook_attack_table[s];
            rook_attack &= st.occup[OCCUP_ALL];
            rook_attack *= table.rook_magics[s];
            rook_attack >>= (64 - table.rook_occupancy_bits[s]);
            return table.rook_table[s][rook_attack];  
        case BISHOP:
            attack = table.bishop_attack_table[s]; 
            attack &= st.occup[OCCUP_ALL];
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
	//todo: get rid of the pawn branch
    //if(get_pawn_attack(side ^ BLACK, s) & st.bitboards[P+side]) return true;

    if((side == WHITE) && (get_pawn_attack<BLACK_PAWNS>(s) & st.bitboards[P])) return true;
    //we wonder if the current square is being attacked by a black pawn. White pawns attack looks something like:
    /*
        1 0 1
        0 P 0
        if we have a black pawn on any of those attack squares then it means that there is a black pawn attacking the current square
    */
    if((side == BLACK && (get_pawn_attack<WHITE_PAWNS>(s) & st.bitboards[p]))) return true;

    if(get_attack_bb(KNIGHT, s) & st.bitboards[N+side]) return true;
    
    if(get_attack_bb(KING, s) & st.bitboards[K+side]) return true;
    
    if(get_attack_bb(BISHOP, s) & st.bitboards[B+side]) return true;

    if(get_attack_bb(ROOK, s) & st.bitboards[R+side]) return true;

    if(get_attack_bb(QUEEN, s) & st.bitboards[Q+side]) return true;

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
    int index = 0;

    for(int square = 0; square < 64; index++){
        int code = check_is_piece(fen[index]);
        
        if(code!= -1){
            st.bitboards[code] |= 1ULL << square;
            square++;
        }
        else if(fen[index] >= '1' && fen[index] <= '8'){
            square += (fen[index] - '0');
        }
    }
    //should be a space now
    assert(fen[index] == ' ');
    index++;

    st.side = fen[index] == 'w' ? WHITE : BLACK;
    index+=2;

    //we are now at the castling
    while(fen[index]!= ' '){
        switch(fen[index]){
            case 'K': st.castling_rights |= WK; break;
            case 'Q': st.castling_rights |= WQ; break;
            case 'k': st.castling_rights |= BK; break;
            case 'q': st.castling_rights |= BQ; break;
            default: break;
        }
        index++;
    }
    index++;

    //en passant square
    if(fen[index] == '-'){
        st.enpessant = none;
    }
    else{
        int file = fen[index++] - 'a';
        int rank = 8 - (fen[index] - '0');
        int s = rank * 8 + file;

        st.enpessant = static_cast<square>(s);
    }

    for(int i = 0; i < NUM_PIECES; i++){
        st.occup[OCCUP_WHITE] |= st.bitboards[i];
        st.occup[OCCUP_BLACK] |= st.bitboards[i + BLACK];
    }
    st.occup[OCCUP_ALL] = st.occup[OCCUP_WHITE] | st.occup[OCCUP_BLACK];
}

Piece Board::which_piece(const int s, int start=0){
    uint64_t board = get_square(static_cast<square>(s));
    for(int i = start; i < 12; i++){
        if((st.bitboards[i] & board) != 0)
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

    if(st.castling_rights & WK){
        std::cout << 'K';
    }
    else{
        std::cout << '-';
    }

    if(st.castling_rights & WQ){
        std::cout << 'Q';
    }
    else{
        std::cout << '-';
    }

    if(st.castling_rights & BK){
        std::cout << 'k';
    }
    else{
        std::cout << '-';
    }

    if(st.castling_rights & BQ){
        std::cout << 'q';
    }
    else{
        std::cout << '-';
    }
    std::cout << "\n";
    if(st.enpessant!= none){
        std::cout << table.square_map[st.enpessant] << "\n";
    }
    else{
        std::cout << "-\n";
    }
    std::cout << "\n";
}

void Board::unmake_move(Move m){
    st = history.top();
    history.pop();
}

inline void Board::update_bitboards(int piece, int source, int dest, int occup_index){
    pop_bit(st.bitboards[piece], source);
    set_bit(st.bitboards[piece], dest);
    pop_bit(st.occup[occup_index], source);
    set_bit(st.occup[occup_index], dest);
}

void Board::save_state(){
    history.push(st);
}

bool Board::make_move(Move m){
    save_state();
    color us = st.side;
    color them = us ^ BLACK;

    int piece = m.piece();
    int source = m.source();
    int dest = m.target();
    int occup_index = us == WHITE ? OCCUP_WHITE : OCCUP_BLACK;

    update_bitboards(piece, source, dest, occup_index);

    if(m.promoted()){
        //pawn gets "captured"
        pop_bit(st.bitboards[piece], dest);
        set_bit(st.bitboards[m.promoted()], dest);
        pop_bit(st.occup[occup_index], source);
        set_bit(st.occup[occup_index], dest);
    }

    if(m.flags() & CASTLING){
        switch(m.target()){
            case g1:
                update_bitboards(R, h1, f1, occup_index);
                break;
            case c1:
                update_bitboards(R, a1, d1, occup_index);
                break;
            case g8:
                update_bitboards(r, h8, f8, occup_index);
                break;
            case c8:
                update_bitboards(r, a8, d8, occup_index);
                break;
        }
    }

    if(m.flags() & CAPTURE){
        int cap_sq = dest;

        if(m.flags() & ENPASSANT){
            us == WHITE ? pop_bit(st.bitboards[p], cap_sq + 8), pop_bit(st.occup[occup_index], cap_sq + 8) 
                            : pop_bit(st.bitboards[P], cap_sq - 8), pop_bit(st.occup[occup_index], cap_sq - 8);
            st.enpessant = none;
        }
        Piece captured = which_piece(m.target(), them);
        //st.captured = captured;
        pop_bit(st.bitboards[captured], cap_sq);
        //occup_index is the current sides occup_index, need to xor by 1 to use other occup. 
        pop_bit(st.occup[occup_index^1], cap_sq);
    }

    st.enpessant = none;

    if(m.flags() & DOUBLE){
        us == WHITE ? st.enpessant = static_cast<square>(dest + 8) : st.enpessant = static_cast<square>(dest - 8);
    }


    st.castling_rights &= table.castle_rights_table[source];
    st.castling_rights &= table.castle_rights_table[dest];

    st.side = them;
    st.occup[OCCUP_ALL] = st.occup[OCCUP_WHITE] | st.occup[OCCUP_BLACK];

    int king_lsb = get_lsb_index(st.bitboards[K+us]);
    if(attacked(static_cast<square>(king_lsb), st.side)){
        unmake_move(m);
        return false;
    }
    
    return true;
}

void Board::debug(uint64_t b){
    //read_fen("8/8/8/3N4/8/8/8/8 w KQkq - 0 1 ");
    
    for(int i = a8; i <= h1; i++){
        std::cout << table.square_map[i] << "\n";
        print_bitboard(table.pawn_attack_table[BLACK_PAWNS][i]);
    }
}
