#include "board.hpp"
#include <iostream>
#include <cassert>

// const std::unordered_map<std::string, uint64_t> Board::square_to_num = {
//     {"A1", 1}, {"B1", 2}, {"C1", 4}, {"D1", 8}, {"E1", 16}, {"F1", 32}, {"G1", 64}, {"H1", 128},
//     {"A2", 256}, {"B2", 512}, {"C2", 1024}, {"D2", 2048}, {"E2", 4096}, {"F2", 8192}, {"G2", 16384}, {"H2", 32768},
//     {"A3", 65536}, {"B3", 131072}, {"C3", 262144}, {"D3", 524288}, {"E3", 1048576}, {"F3", 2097152}, {"G3", 4194304}, {"H3", 8388608},
//     {"A4", 16777216}, {"B4", 33554432}, {"C4", 67108864}, {"D4", 134217728}, {"E4", 268435456}, {"F4", 536870912}, {"G4", 1073741824}, {"H4", 2147483648},
//     {"A5", 4294967296}, {"B5", 8589934592}, {"C5", 17179869184}, {"D5", 34359738368}, {"E5", 68719476736}, {"F5", 137438953472}, {"G5", 274877906944}, {"H5", 549755813888},
//     {"A6", 1099511627776}, {"B6", 2199023255552},{"C6", 4398046511104}, {"D6", 8796093022208}, {"E6", 17592186044416}, {"F6", 35184372088832}, {"G6", 70368744177664}, {"H6", 140737488355328},
//     {"A7", 281474976710656},{"B7", 562949953421312}, {"C7", 1125899906842624}, {"D7", 2251799813685248}, {"E7", 4503599627370496}, {"F7", 9007199254740992}, {"G7", 18014398509481984}, {"H7", 36028797018963968}, 
//     {"A8", 72057594037927936}, {"B8", 144115188075855872}, {"C8", 288230376151711744}, {"D8", 576460752303423488}, {"E8", 1152921504606846976}, {"F8", 2305843009213693952}, {"G8", 4611686018427387904},{"H8", 9223372036854775808ULL},
// };

// const std::unordered_map<uint64_t, std::string> Board::num_to_square = {
//     {1, "A1"}, {2, "B1"}, {4, "C1"}, {8, "D1"}, {16, "E1"}, {32, "F1"}, {64, "G1"}, {128, "H1"},
//     {256, "A2"}, {512, "B2"}, {1024, "C2"}, {2048, "D2"}, {4096, "E2"}, {8192, "F2"}, {16384, "G2"}, {32768, "H2"},
//     {65536, "A3"}, {131072, "B3"}, {262144, "C3"}, {524288, "D3"}, {1048576, "E3"}, {2097152, "F3"}, {4194304, "G3"}, {8388608, "H3"},
//     {16777216, "A4"}, {33554432, "B4"}, {67108864, "C4"}, {134217728, "D4"}, {268435456, "E4"}, {536870912, "F4"}, {1073741824, "G4"}, {2147483648, "H4"},
//     {4294967296, "A5"}, {8589934592, "B5"}, {17179869184, "C5"}, {34359738368, "D5"}, {68719476736, "E5"}, {137438953472, "F5"}, {274877906944, "G5"}, {549755813888, "H5"},
//     {1099511627776, "A6"}, {2199023255552, "B6"}, {4398046511104, "C6"}, {8796093022208, "D6"}, {17592186044416, "E6"}, {35184372088832, "F6"}, {70368744177664, "G6"}, {140737488355328, "H6"},
//     {281474976710656, "A7"}, {562949953421312, "B7"}, {1125899906842624, "C7"}, {2251799813685248, "D7"}, {4503599627370496, "E7"}, {9007199254740992, "F7"}, {18014398509481984, "G7"}, {36028797018963968, "H7"},
//     {72057594037927936, "A8"}, {144115188075855872, "B8"}, {288230376151711744, "C8"}, {576460752303423488, "D8"}, {1152921504606846976, "E8"}, {2305843009213693952, "F8"}, {4611686018427387904, "G8"}, {9223372036854775808ULL, "H8"}
// };

const std::unordered_map<int, char> Board::symbol_map = {
    {P, 'P'},
    {N, 'N'},
    {B, 'B'},
    {Q, 'Q'},
    {K, 'K'},
    {R, 'R'},
    {p, 'p'},
    {n, 'n'},
    {b, 'b'},
    {q, 'q'},
    {k, 'k'},
    {r, 'r'},
    {no_piece, '.'}
};

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

Board::Board() : side(WHITE), table(Table::get_instance()), enpessant(none){
    // bitboards[ROOKS + WHITE] = get_square(a1) | get_square(h1);
    // bitboards[ROOKS + BLACK] = get_square(a8) | get_square(h8);

    // bitboards[BISHOPS + WHITE] = get_square(c1) | get_square(f1);
    // bitboards[BISHOPS + BLACK] = get_square(c8) | get_square(f8);

    // bitboards[PAWNS + WHITE] = get_square(a2) | get_square(b2) | get_square(c2) | get_square(d2) | 
    //                         get_square(e2) | get_square(f2) | get_square(g2) | get_square(h2);
    // bitboards[PAWNS + BLACK] = get_square(a7) | get_square(b7) | get_square(c7) | get_square(d7) | 
    //                         get_square(e7) | get_square(f7) | get_square(g7) | get_square(h7);

    // bitboards[QUEEN + WHITE] = get_square(d1);
    // bitboards[QUEEN + BLACK] = get_square(d8);

    // bitboards[KING + WHITE] = get_square(e1);
    // bitboards[KING + BLACK] = get_square(e8);

    // bitboards[KNIGHTS + WHITE] = get_square(b1) | get_square(g1); 
    // bitboards[KNIGHTS + BLACK] = get_square(b8) | get_square(g8);

    // bitboards[ALL] = 0;
    // for(int i = 0; i < 12; i++){
    //     bitboards[ALL] |= bitboards[i];
    // }

    for(int i = 0; i < 12; i++){
        bitboards[i] = 0;
    }
    
    for(int i = 0; i < 3; i++){
        occup[i] = 0;
    }
}

template <color c>
inline uint64_t Board::get_pawn_attack(square s){
    return table.pawn_attack_table[c][s];
}

uint64_t Board::get_attack_bb(piece_type p, square s, uint64_t occup){
    uint64_t rook_attack;
    uint64_t attack;
    switch(p){
        case ROOK:
            rook_attack = table.rook_attack_table[s];
            rook_attack &= occup;
            rook_attack *= table.rook_magics[s];
            rook_attack >>= (64 - table.rook_occupancy_bits[s]);
            return table.rook_table[s][rook_attack];  
        case BISHOP:
            attack = table.bishop_attack_table[s]; 
            attack &= occup;
            attack *= table.bishop_magics[s];
            attack >>= (64 - table.bishop_occupancy_bits[s]);
            return table.bishop_table[s][attack];   
        case QUEEN:
            return get_attack_bb(ROOK, s, occup) | get_attack_bb(BISHOP, s, occup);
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

    if(get_attack_bb(KNIGHT, s, 0) & (side == WHITE ? bitboards[N] : bitboards[n])) return true;
    
    if(get_attack_bb(KING, s, 0) & (side == WHITE ? bitboards[K] : bitboards[k])) return true;
    
    if(get_attack_bb(BISHOP, s, occup[OCCUP_ALL]) & (side == WHITE ? bitboards[B] : bitboards[b])) return true;

    if(get_attack_bb(ROOK, s, occup[OCCUP_ALL]) & (side == WHITE ? bitboards[R] : bitboards[r])) return true;

    if(get_attack_bb(QUEEN, s, occup[OCCUP_ALL]) & (side == WHITE ? bitboards[Q] : bitboards[q])) return true;

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

int Board::which_piece(const uint64_t square){
    for(int i = 0; i < 12; i++){
        if((bitboards[i] & square) != 0)
            return i;
    }
    return 12;
}

void Board::print(){
    uint64_t all_pieces = 0;

    for(int i = WHITE; i < NUM_PIECES; i++){
        all_pieces |= (bitboards[i] | bitboards[i + BLACK]);
    }

    for(int i = 0; i < 8; i++){
        std::cout << (8 - i) << "   ";
        for(int j = 0; j < 8; j++){
            uint64_t mask = 1ULL << (i*8+j);
            std::cout << symbol_map.at(which_piece(all_pieces & mask)) << " ";
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

void Board::debug(uint64_t b){
    //read_fen("8/8/8/3N4/8/8/8/8 w KQkq - 0 1 ");
    print_bitboard(b);
}