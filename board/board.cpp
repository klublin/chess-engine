#include <iostream>
#include <cassert>
#include "board.hpp"
#include "MoveGenerator.hpp"
#include "Move.hpp"

void print_bitboard(uint64_t board){
    for(int i = 0; i < 8; i++){
        std::cout << (8 - i) << "   ";
        for(int j = 0; j < 8; j++){
            uint64_t mask = get_square(static_cast<Square>(i*8+j));
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

inline void pop_bit(uint64_t& board, Square s){
    board &= ~(get_square(s));
}

inline void set_bit(uint64_t& board, Square s){
    board |= (get_square(s));
}


inline uint64_t Board::get_pawn_attack(color c, Square s){
    	return table.pawn_attack_table[c][s];
}

//checks if current Square is attacked by given by the side 
bool Board::attacked(Square s, color side){

    //we wonder if the current Square is being attacked by a black pawn. White pawns attack looks something like:
    /*
        1 0 1
        0 P 0
        if we have a black pawn on any of those attack squares then it means that there is a black pawn attacking the current Square
        vice versa for white
    */
    if(get_pawn_attack(~side, s) & st.bitboards[P+side]) return true;

    if(get_attack_bb<KNIGHT>(s) & st.bitboards[N+side]) return true;
    
    if(get_attack_bb<KING>(s) & st.bitboards[K+side]) return true;
    
    if(get_attack_bb<BISHOP>(s) & st.bitboards[B+side]) return true;

    if(get_attack_bb<ROOK>(s) & st.bitboards[R+side]) return true;

    if(get_attack_bb<QUEEN>(s) & st.bitboards[Q+side]) return true;

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
    //our enum Square starts at a8, where the fen string starts 
    st.clear();
    int index = 0;

    for(int square = 0; square < 64; index++){
        int code = check_is_piece(fen[index]);
        
        if(code!= -1){
            st.bitboards[code] |= get_square(static_cast<Square>(square));
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

    //en passant Square
    if(fen[index] == '-'){
        st.enpessant = none;
    }
    else{
        int file = fen[index++] - 'a';
        int rank = 8 - (fen[index] - '0');
        int s = rank * 8 + file;

        st.enpessant = static_cast<Square>(s);
    }

    for(Piece_type pt : {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING}){
        st.occup[WHITE] |= st.bitboards[pt];
        st.occup[BLACK] |= st.bitboards[pt+BLACK];
    }
    st.occup[OCCUP_ALL] = st.occup[WHITE] | st.occup[BLACK];

    st.generate_hash();
}



void Board::print(){
    for(int i = 0; i < 8; i++){
        std::cout << (8 - i) << "   ";
        for(int j = 0; j < 8; j++){
            std::cout << table.pieces[st.which_piece(static_cast<Square>(i*8+j))] << " ";
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
    std::cout << "side to play " << (st.side == WHITE ? 'W' : 'B') << "\n";
    std::cout << "\n";
}

void Board::unmake_move(Move m){
    st = history.top();
    history.pop();
}

inline void Board::update_bitboards(int piece, Square source, Square dest, color us){
    pop_bit(st.bitboards[piece], source);
    set_bit(st.bitboards[piece], dest);
    pop_bit(st.occup[us], source);
    set_bit(st.occup[us], dest);
    //remove from source square
    st.hash_key ^= table.piece_keys[piece][source];
    //place on dest square
    st.hash_key ^= table.piece_keys[piece][dest];
}

void Board::save_state(){
    history.push(st);
}

bool Board::make_move(Move m){
    save_state();
    color us = st.side;
    color them = ~us;

    Piece piece = static_cast<Piece>(m.piece());
    Square source = static_cast<Square>(m.source());
    Square dest = static_cast<Square>(m.target());

    if(m.flags() & CAPTURE){
		Square cap_sq = dest;
		if(m.flags() & ENPASSANT){
			us == WHITE ? cap_sq += 8 : cap_sq -= 8;
            st.hash_key ^= table.enpassant_keys[st.enpessant];
			st.enpessant = none;
		}
		Piece captured = st.which_piece(cap_sq);
        if(captured == no_piece){
            m.print();
            print();
            assert(false);
        }
		pop_bit(st.bitboards[captured], cap_sq);
        st.hash_key ^= table.piece_keys[captured][cap_sq];
		pop_bit(st.occup[~us], cap_sq);
    }

    if(m.promoted()){
        //pawn gets "captured"
        pop_bit(st.bitboards[piece], source);
        pop_bit(st.occup[us], source);
        //remove pawn 
        st.hash_key ^= table.piece_keys[piece][source];
        piece = static_cast<Piece>(m.promoted());
        //add the promoted piece into the hash key, it will be removed in the update_bitboards call
        st.hash_key ^= table.piece_keys[piece][source];
    }
    
    //the moves before rely on other processing first before updating the bitboards
    //we update certain variables to the correct state before moving the intended piece
    update_bitboards(piece, source, dest, us);

    if(m.flags() & CASTLING){
        switch(m.target()){
            case g1:
                update_bitboards(R, h1, f1, us);
                break;
            case c1:
                update_bitboards(R, a1, d1, us);
                break;
            case g8:
                update_bitboards(r, h8, f8, us);
                break;
            case c8:
                update_bitboards(r, a8, d8, us);
                break;
        }
    }
    st.enpessant = none;

    if(m.flags() & DOUBLE){
        if(us == WHITE){
            st.enpessant = static_cast<Square>(dest + 8);
            st.hash_key^= table.enpassant_keys[dest+8];
        }
        else{
            st.enpessant = static_cast<Square>(dest - 8);
            st.hash_key ^= table.enpassant_keys[dest - 8];

        }
    }

    st.hash_key ^= table.castling_keys[st.castling_rights];
    st.castling_rights &= castle_rights_table[source];
    st.castling_rights &= castle_rights_table[dest];
    st.hash_key ^= table.castling_keys[st.castling_rights];

    st.side = them;
    st.hash_key ^= table.side_key;
    
    st.occup[OCCUP_ALL] = st.occup[WHITE] | st.occup[BLACK];

    Square king_loc = static_cast<Square>(get_lsb_index(st.bitboards[K+us]));
    if(attacked(king_loc, st.side)){
        unmake_move(m);
        return false;
    }
    
    return true;
}

void Board::debug(uint64_t b){
    //read_fen("8/8/8/3N4/8/8/8/8 w KQkq - 0 1 ");
    
    print_bitboard(b);
}