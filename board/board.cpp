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

const std::unordered_map<std::string, Board::square> Board::square_map{
    {"a1",a1}, {"a2",a2}, {"a3",a3}, {"a4",a4}, {"a5",a5}, {"a6",a6}, {"a7",a7}, {"a8",a8}, 
    {"b1",b1}, {"b2",b2}, {"b3",b3}, {"b4",b4}, {"b5",b5}, {"b6",b6}, {"b7",b7}, {"b8",b8}, 
    {"c1",c1}, {"c2",c2}, {"c3",c3}, {"c4",c4}, {"c5",c5}, {"c6",c6}, {"c7",c7}, {"c8",c8}, 
    {"d1",d1}, {"d2",d2}, {"d3",d3}, {"d4",d4}, {"d5",d5}, {"d6",d6}, {"d7",d7}, {"d8",d8}, 
    {"e1",e1}, {"e2",e2}, {"e3",e3}, {"e4",e4}, {"e5",e5}, {"e6",e6}, {"e7",e7}, {"e8",e8}, 
    {"f1",f1}, {"f2",f2}, {"f3",f3}, {"f4",f4}, {"f5",f5}, {"f6",f6}, {"f7",f7}, {"f8",f8}, 
    {"g1",g1}, {"g2",g2}, {"g3",g3}, {"g4",g4}, {"g5",g5}, {"g6",g6}, {"g7",g7}, {"g8",g8}, 
    {"h1",h1}, {"h2",h2}, {"h3",h3}, {"h4",h4}, {"h5",h5}, {"h6",h6}, {"h7",h7}, {"h8",h8}, 
};

const std::unordered_map<int, uint64_t> Board::clear_rank{
    {1,18446744073709551360ULL},
    {2,18446744073709486335ULL},
    {3,18446744073692839935ULL},
    {4,18446744069431361535ULL},
    {5,18446742978492891135ULL},
    {6,18446463698244468735ULL},
    {7,18374967954648334335ULL},
    {8,72057594037927935ULL},
};
const std::unordered_map<int, uint64_t> Board::mask_rank{
    {1,255ULL},
    {2,65280ULL},
    {3,16711680ULL},
    {4,4278190080ULL},
    {5,1095216660480ULL},
    {6,280375465082880ULL},
    {7,71776119061217280ULL},
    {8,18374686479671623680ULL},
};
const std::unordered_map<char, uint64_t> Board::clear_file{
    {'a',18374403900871474942ULL},
    {'b',18302063728033398269ULL},
    {'c',18157383382357244923ULL},
    {'d',17868022691004938231ULL},
    {'e',17289301308300324847ULL},
    {'f',16131858542891098079ULL},
    {'g',13816973012072644543ULL},
    {'h',9187201950435737471ULL},
};
const std::unordered_map<char, uint64_t> Board::mask_file{
    {'a',72340172838076673ULL},
    {'b',144680345676153346ULL},
    {'c',289360691352306692ULL},
    {'d',578721382704613384ULL},
    {'e',1157442765409226768ULL},
    {'f',2314885530818453536ULL},
    {'g',4629771061636907072ULL},
    {'h',9259542123273814144ULL},
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

const std::array<int, 64> bishop_occupancy_bits{
    6,5,5,5,5,5,5,6,
    5,5,5,5,5,5,5,5,
    5,5,7,7,7,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,7,7,7,5,5,
    5,5,5,5,5,5,5,5,
    6,5,5,5,5,5,5,6,
};

const std::array<int, 64> rook_occupancy_bits {
    12,11,11,11,11,11,11,12,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    12,11,11,11,11,11,11,12,
};

bool Board::init_magic = false;

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

int count_bits(uint64_t a){
    int count;
    for(count = 0; a; count++, a &= (a-1));
    return count;
}

uint64_t Board::mask_rook_attack(square s){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //RIGHT
    for(int r = rank, c = file + 1; c < RANK_7; c++){
        attack_map |= 1ULL << (r*8 + c); 
    }
    //up
    for(int r = rank + 1, c = file; r < RANK_7; r++){
        attack_map |= 1ULL << (r * 8 + c);
    }
    //LEFT
    for(int r = rank, c = file - 1; c > 0 ; c--){
        attack_map |= 1ULL << (r * 8 + c);
    }
    //down
    for(int r = rank - 1, c = file; r > 0; r--){
        attack_map |= 1ULL << (r * 8 + c);
    }
    return attack_map;
}

uint64_t Board::mask_rook_attack_ray(square s, uint64_t blockers){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //RIGHT
    for(int r = rank, c = file + 1; c < RANK_7; c++){
        attack_map |= 1ULL << (r*8 + c); 
        if(blockers & (1ULL << (r* 8 + c))) break;
    }
    //up
    for(int r = rank + 1, c = file; r < RANK_7; r++){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }
    //LEFT
    for(int r = rank, c = file - 1; c > 0 ; c--){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }
    //down
    for(int r = rank - 1, c = file; r > 0; r--){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }
    return attack_map;
}

uint64_t Board::mask_bishop_attack(Board::square s){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //up diagonal RIGHT
    for(int r = rank + 1, c = file + 1; r < RANK_7 && c < RANK_7; r++, c++){
        attack_map |= 1ULL << (r*8 + c); 
    }

    //DOWN DIAGONAL RIGHT
    for(int r = rank - 1, c = file + 1; c < RANK_7 && r > 0; r--, c++){
        attack_map |= 1ULL << (r * 8 + c);
    }

    //LEFT DIAGONAL UP
    for(int r = rank + 1, c = file  - 1; c > 0 && r < RANK_7; c--, r++){
        attack_map |= 1ULL << (r * 8 + c);
    }

    //LEFT DIAGONAL DOWN
    for(int r = rank - 1, c = file - 1; c > 0 && r > 0; r--, c--){
        attack_map |= 1ULL << (r * 8 + c);
    }
    return attack_map;
}

uint64_t Board::mask_bishop_attack_ray(square s, uint64_t blockers){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //up diagonal RIGHT
    for(int r = rank + 1, c = file + 1; r < RANK_7 && c < RANK_7; r++, c++){
        attack_map |= 1ULL << (r*8 + c); 
        if(blockers & (1ULL << (r* 8 + c))) break;
    }

    //DOWN DIAGONAL RIGHT
    for(int r = rank - 1, c = file + 1; c < RANK_7 && r > 0; r--, c++){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }

    //LEFT DIAGONAL UP
    for(int r = rank + 1, c = file  - 1; c > 0 && r < RANK_7; c--, r++){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }

    //LEFT DIAGONAL DOWN
    for(int r = rank - 1, c = file - 1; c > 0 && r > 0; r--, c--){
        attack_map |= 1ULL << (r * 8 + c);
        if(blockers & (1ULL << (r* 8 + c))) break;
    }
    return attack_map;
}

uint64_t Board::random_num() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
  u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

uint64_t Board::generate_magic_nums() {
  return random_num() & random_num() & random_num();
}

inline int get_lsb_index(uint64_t num){
    if(num){
        return count_bits((num & -num) - 1);
    }
    return -1;
}

uint64_t occupancy(int index, uint64_t attack_mask){
    int count = count_bits(attack_mask);
    uint64_t occup_map = 0;

    for(int i = 0; i < count; i++){
        int square = get_lsb_index(attack_mask);

        attack_mask ^= (1ULL << square);

        if(index & 1 << i){
            occup_map |= 1ULL << square;
        }
    }
    return occup_map;
}

uint64_t Board::find_magic(Board::square square, Board::piece p){
    std::array<uint64_t, 4096> occupancies;
    std::array<uint64_t, 4096> attacks;
    std::array<uint64_t, 4096> used_attacks;

    uint64_t attack_mask = p == BISHOPS ? mask_bishop_attack(square) : mask_rook_attack(square);
    int occupancy_bitshift = 64 - (p == BISHOPS ? bishop_occupancy_bits[square] : rook_occupancy_bits[square]);
    int num_bits = count_bits(attack_mask);

    for(int i = 0; i < (1 << num_bits); i++){
        occupancies[i] = occupancy(i, attack_mask);

        attacks[i] = p == BISHOPS ? mask_bishop_attack_ray(square, occupancies[i]) 
                                    : mask_rook_attack_ray(square, occupancies[i]);
    }

    for(int i = 0; i < 100000000; i++){
        uint64_t magic = generate_magic_nums();
        //need top bits to be set for hash function to work
        if(count_bits((attack_mask * magic) & 0xFF00000000000000ULL) < 6){
            continue;
        }
        used_attacks.fill(0);

        bool fail = false;

        for(int index = 0; !fail && index < (1 << num_bits); index++){
            int magic_index = (int)((occupancies[index] * magic) >> occupancy_bitshift);

            if(used_attacks[magic_index] == 0ULL) 
                used_attacks[magic_index] = attacks[index];
            else{
                fail = true;
            }
        }

        if(!fail){
            return magic;
        }
    }

    std::cout << "FAILED\n";
    return 0;
}

uint64_t Board::fill_magic_table_rook(){
    printf("const std::array<uint64_t, 64> = {\n");
    for(int i = a8; i <= h1; i++)
    {
        printf("  0x%lxULL,\n", find_magic(static_cast<square>(i), ROOKS));
    }
    printf("};\n\n");

    return 0;
}

uint64_t Board::fill_magic_table_bishop(){
    printf("const std::array<uint64_t, 64> = {\n");
    for(int i = a8; i <= h1; i++)
    {
        printf("  0x%lxULL,\n", find_magic(static_cast<square>(i), BISHOPS));
    }
    printf("};\n\n");

    return 0;
}


inline uint64_t Board::get_square(Board::square s){
    return 1ULL << s;
}

Board::Board() : side(WHITE){
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
}

uint64_t Board::check_pawn_move_white(uint64_t curr_board, uint64_t own_side, uint64_t other_side){
    uint64_t all_pieces = own_side | other_side;

    uint64_t move_forward = (curr_board << 8) & ~all_pieces;
    uint64_t second_move = ((move_forward & mask_rank.at(3)) << 8) & ~all_pieces;

    uint64_t left_pawn_attack = curr_board & clear_file.at(FILE_A) << 7;
    uint64_t right_pawn_attack = curr_board & clear_file.at(FILE_H) << 9;

    uint64_t all_pawn_attacks = left_pawn_attack | right_pawn_attack;

    uint64_t valid_moves = move_forward | second_move | (all_pawn_attacks & other_side);

    return valid_moves;

}

uint64_t Board::check_pawn_move_black(uint64_t curr_board, uint64_t own_side, uint64_t other_side){
    uint64_t all_pieces = own_side | other_side;

    uint64_t move_forward = (curr_board >> 8) & ~all_pieces;
    uint64_t second_move = ((move_forward & mask_rank.at(6)) >> 8) & ~all_pieces;

    uint64_t left_pawn_attack = curr_board & clear_file.at(FILE_A) >> 9;
    uint64_t right_pawn_attack = curr_board & clear_file.at(FILE_H) >> 7;

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
    uint64_t mask_a = mask_file.at(FILE_A);
    uint64_t mask_h = mask_file.at(FILE_H);

    uint64_t mask_a_b = mask_file.at(FILE_A) & mask_file.at(FILE_B);
    uint64_t mask_g_h = mask_file.at(FILE_B) & mask_file.at(FILE_H);

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
    uint64_t clear_file_h = curr_board & clear_file.at(FILE_H);
    uint64_t clear_file_a = curr_board & clear_file.at(FILE_A);

    uint64_t spot1 = clear_file_a << 7;
    uint64_t spot2 = curr_board << 8;
    uint64_t spot3 = clear_file_h << 9;
    uint64_t spot5 = clear_file_h << 1;
    
    uint64_t spot4 = clear_file_a >> 1;
    uint64_t spot6 = clear_file_a >> 9;
    uint64_t spot7 = curr_board >> 8;
    uint64_t spot8 = clear_file_h >> 7;

    uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;
    return (valid_spots & ~own_side);
}

uint64_t Board::check_bishop_move(uint64_t curr_board, uint64_t own_side){
    return 0;
}

uint64_t Board::check_queen_move(uint64_t curr_board, uint64_t own_side){
    return 0;
}

uint64_t Board::check_rook_move(uint64_t curr_board, uint64_t own_side){
    return 0;    
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
            validate = check_bishop_move(source_square, own_side);
            break;
        case KNIGHTS:
            validate = check_knight_move(source_square, own_side);
            break;
        case KING:
            validate = check_king_move(source_square, own_side);
            break;
        case QUEEN:
            validate = check_queen_move(source_square, own_side);
            break;
        case ROOKS:
            validate = check_rook_move(source_square, own_side);
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

    fill_magic_table_rook();
    fill_magic_table_bishop();
}


int main(){
    Board b;
    std::string square;

    b.debug(square);

}