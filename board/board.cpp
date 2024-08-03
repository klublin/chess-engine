#include "board.hpp"
#include <iostream>

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

const std::unordered_map<std::string, square> Board::square_map{
    {"a1",a1}, {"a2",a2}, {"a3",a3}, {"a4",a4}, {"a5",a5}, {"a6",a6}, {"a7",a7}, {"a8",a8}, 
    {"b1",b1}, {"b2",b2}, {"b3",b3}, {"b4",b4}, {"b5",b5}, {"b6",b6}, {"b7",b7}, {"b8",b8}, 
    {"c1",c1}, {"c2",c2}, {"c3",c3}, {"c4",c4}, {"c5",c5}, {"c6",c6}, {"c7",c7}, {"c8",c8}, 
    {"d1",d1}, {"d2",d2}, {"d3",d3}, {"d4",d4}, {"d5",d5}, {"d6",d6}, {"d7",d7}, {"d8",d8}, 
    {"e1",e1}, {"e2",e2}, {"e3",e3}, {"e4",e4}, {"e5",e5}, {"e6",e6}, {"e7",e7}, {"e8",e8}, 
    {"f1",f1}, {"f2",f2}, {"f3",f3}, {"f4",f4}, {"f5",f5}, {"f6",f6}, {"f7",f7}, {"f8",f8}, 
    {"g1",g1}, {"g2",g2}, {"g3",g3}, {"g4",g4}, {"g5",g5}, {"g6",g6}, {"g7",g7}, {"g8",g8}, 
    {"h1",h1}, {"h2",h2}, {"h3",h3}, {"h4",h4}, {"h5",h5}, {"h6",h6}, {"h7",h7}, {"h8",h8}, 
};

const std::unordered_map<int, char> Board::symbol_map = {
    {PAWNS, 'P'},
    {KNIGHTS, 'N'},
    {BISHOPS, 'B'},
    {QUEEN, 'Q'},
    {KING, 'K'},
    {ROOKS, 'R'},
    {PAWNS + BLACK, 'P'},
    {KNIGHTS + BLACK, 'N'},
    {BISHOPS + BLACK, 'B'},
    {QUEEN + BLACK, 'Q'},
    {KING + BLACK, 'K'},
    {ROOKS + BLACK, 'R'},
    {2*NUM_PIECES, ' '}
};

const std::unordered_map<char, Board::piece> Board::reverse_symbol_map = {
    {'P', PAWNS},
    {'N', KNIGHTS},
    {'B', BISHOPS},
    {'R', ROOKS},
    {'K', KING},
    {'Q', QUEEN}
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

Board::Board() : side(WHITE), table(Table::get_instance()){
    bitboards[ROOKS + WHITE] = get_square(a1) | get_square(h1);
    bitboards[ROOKS + BLACK] = get_square(a8) | get_square(h8);

    bitboards[BISHOPS + WHITE] = get_square(c1) | get_square(f1);
    bitboards[BISHOPS + BLACK] = get_square(c8) | get_square(f8);

    bitboards[PAWNS + WHITE] = get_square(a2) | get_square(b2) | get_square(c2) | get_square(d2) | 
                            get_square(e2) | get_square(f2) | get_square(g2) | get_square(h2);
    bitboards[PAWNS + BLACK] = get_square(a7) | get_square(b7) | get_square(c7) | get_square(d7) | 
                            get_square(e7) | get_square(f7) | get_square(g7) | get_square(h7);

    bitboards[QUEEN + WHITE] = get_square(d1);
    bitboards[QUEEN + BLACK] = get_square(d8);

    bitboards[KING + WHITE] = get_square(e1);
    bitboards[KING + BLACK] = get_square(e8);

    bitboards[KNIGHTS + WHITE] = get_square(b1) | get_square(g1); 
    bitboards[KNIGHTS + BLACK] = get_square(b8) | get_square(g8);

    bitboards[ALL] = 0;
    for(int i = 0; i < 12; i++){
        bitboards[ALL] |= bitboards[i];
    }
}

uint64_t Board::check_pawn_move_white(uint64_t curr_board, uint64_t own_side, uint64_t other_side){
    uint64_t all_pieces = own_side | other_side;

    uint64_t move_forward = (curr_board << 8) & ~all_pieces;
    uint64_t second_move = ((move_forward & table.get_mask_rank(RANK_3)) << 8) & ~all_pieces;

    uint64_t left_pawn_attack = curr_board & table.get_clear_file(FILE_A) << 7;
    uint64_t right_pawn_attack = curr_board & table.get_clear_file(FILE_H) << 9;

    uint64_t all_pawn_attacks = left_pawn_attack | right_pawn_attack;

    uint64_t valid_moves = move_forward | second_move | (all_pawn_attacks & other_side);

    return valid_moves;

}

uint64_t Board::check_pawn_move_black(uint64_t curr_board, uint64_t own_side, uint64_t other_side){
    uint64_t all_pieces = own_side | other_side;

    uint64_t move_forward = (curr_board >> 8) & ~all_pieces;
    uint64_t second_move = ((move_forward & table.get_mask_rank(RANK_6)) >> 8) & ~all_pieces;

    uint64_t left_pawn_attack = curr_board & table.get_clear_file(FILE_A) >> 9;
    uint64_t right_pawn_attack = curr_board & table.get_clear_file(FILE_H) >> 7;

    uint64_t all_pawn_attacks = left_pawn_attack | right_pawn_attack;

    uint64_t valid_moves = move_forward | second_move | (all_pawn_attacks & other_side);

    return valid_moves;
}

uint64_t Board::check_knight_move(uint64_t curr_board, uint64_t own_side){
    /*
        knight has 8 spots to move to
            x1x2x  
            3xxx4  
            xxNxx
            5xxx6
            x7x8x    
    */
    uint64_t mask_a = table.get_mask_file(FILE_A);
    uint64_t mask_h = table.get_mask_file(FILE_H);

    uint64_t mask_a_b = table.get_mask_file(FILE_A) & table.get_mask_file(FILE_B);
    uint64_t mask_g_h = table.get_mask_file(FILE_B) & table.get_mask_file(FILE_H);

    uint64_t spot1 = mask_a << 15;
    uint64_t spot2 = mask_h << 17;
    uint64_t spot3 = mask_a_b << 6;
    uint64_t spot4 = mask_g_h << 10;

    uint64_t spot5 = mask_a_b >> 10;
    uint64_t spot6 = mask_g_h >> 6;
    uint64_t spot7 = mask_a >> 17;
    uint64_t spot8 = mask_h >> 15;

    uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;

    return (valid_spots & ~own_side);
}

uint64_t Board::check_king_move(uint64_t curr_board, uint64_t own_side){
    /*
        king has 8 spots to move to
        1 2 3 
        4 k 5
        6 7 8
    */
    // uint64_t clear_file_h = curr_board & table.get_clear_file(FILE_H);
    // uint64_t clear_file_a = curr_board & table.get_clear_file(FILE_A);

    // uint64_t spot1 = clear_file_a << 7;
    // uint64_t spot2 = curr_board << 8;
    // uint64_t spot3 = clear_file_h << 9;
    // uint64_t spot5 = clear_file_h << 1;
    
    // uint64_t spot4 = clear_file_a >> 1;
    // uint64_t spot6 = clear_file_a >> 9;
    // uint64_t spot7 = curr_board >> 8;
    // uint64_t spot8 = clear_file_h >> 7;

    // uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;
    // return (valid_spots & ~own_side);

    return (table.king_attack_table[curr_board] & ~own_side);
}

uint64_t Board::check_bishop_move(square s){
    uint64_t attack = table.bishop_attack_table[s];
    uint64_t occup = bitboards[ALL];

    attack &= occup;
    attack *= table.bishop_magics[s];
    attack >>= (64 - table.bishop_occupancy_bits[s]);

    return table.bishop_table[s][attack];   
}

uint64_t Board::check_queen_move(square s){
    return check_bishop_move(s) | check_rook_move(s);
}

uint64_t Board::check_rook_move(square s){
    uint64_t attack = table.rook_attack_table[s];
    print_bitboard(attack);
    uint64_t occup = bitboards[ALL];
    attack &= occup;
    attack *= table.rook_magics[s];
    attack >>= (64 - table.rook_occupancy_bits[s]);
    return table.rook_table[s][attack];   
}

void capture(){

}

void Board::update(const std::string &from, const std::string& target){
    piece curr;
    color opp;
    
    square from_square = square_map.at(from);
    square t = square_map.at(target);

    curr = reverse_symbol_map.at(symbol_map.at(which_piece(1 << from_square)));

    uint64_t target_square = 1 << t;
    uint64_t source_square = 1 << from_square;

    uint64_t own_side = 0;
    uint64_t other_side = 0;

    if(side == WHITE){
        opp = BLACK;
    }
    else{
        opp = WHITE;
    }

    uint64_t curr_board = bitboards[curr + side];

    if((curr_board & source_square) == 0){
        //the piece isn't even there!
        //need error code. 
        return;
    }

    for(int i = WHITE; i < NUM_PIECES; i++){
       own_side |= bitboards[i + side];
       other_side |= bitboards[i + opp];
    }

    uint64_t validate = 0;
    
    switch(curr){
        case PAWNS:
            if(side == WHITE){
                validate = check_pawn_move_white(source_square, own_side, other_side);
            }
            else{
                validate = check_pawn_move_black(source_square, own_side, other_side);
            }
            break;
        case BISHOPS:
            validate = check_bishop_move(from_square);
            break;
        case KNIGHTS:
            validate = check_knight_move(source_square, own_side);
            break;
        case KING:
            validate = check_king_move(source_square, own_side);
            break;
        case QUEEN:
            validate = check_queen_move(from_square);
            break;
        case ROOKS:
            validate = check_rook_move(from_square);
            break;
        case NUM_PIECES:
            //maybe just throw error...
            break;
    }

    //TODO: change to error code so user knows to input again
    if((validate & target_square) == 0){
        std::cout << "error\n";
        return;
    }

    //todo figure out captures(probably easy), need checks as well
    if((target_square & other_side)!= 0){
        capture();
    }
    else{
        //pop bit of source square and set bit for target square
        bitboards[curr + side] &= ~(source_square);
        bitboards[curr + side] |= target_square;

        bitboards[ALL] &= ~(source_square);
        bitboards[ALL] |= target_square;
    }
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
        for(int j = 0; j < 8; j++){
            uint64_t mask = 1ULL << (i*8+j);
            std::cout << symbol_map.at(which_piece(all_pieces & mask)) << " ";
        }
        std::cout << "\n";
    }
}

void Board::debug(const std::string& square){
    
    // uint64_t rook = mask_rook_attack(a1);
    // print_bitboard(rook);
    // for(int i = 0; i < 2; i++){
    //     uint64_t t = occupancy(i, rook);
    //     print_bitboard(t);
    // }

    print_bitboard(check_rook_move(a1));
}


int main(){
    Board b;
    std::string square;

    b.debug(square);

}