#include "tables.hpp"
#include <iostream>

static const std::array<int, 64> bishop_occupancy_bits{
    6,5,5,5,5,5,5,6,
    5,5,5,5,5,5,5,5,
    5,5,7,7,7,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,9,9,7,5,5,
    5,5,7,7,7,7,5,5,
    5,5,5,5,5,5,5,5,
    6,5,5,5,5,5,5,6,
};

static const std::array<int, 64> rook_occupancy_bits {
    12,11,11,11,11,11,11,12,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    11,10,10,10,10,10,10,11,
    12,11,11,11,11,11,11,12,
};

uint64_t Table::mask_rook_attack(square s){
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

uint64_t Table::mask_rook_attack_ray(square s, uint64_t blockers){
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

uint64_t Table::mask_bishop_attack(square s){
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

uint64_t Table::mask_bishop_attack_ray(square s, uint64_t blockers){
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

uint64_t Table::random_num() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
  u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

uint64_t Table::generate_magic_nums() {
  return random_num() & random_num() & random_num();
}

inline int get_lsb_index(uint64_t num){
    if(num){
        return count_bits((num & -num) - 1);
    }
    return -1;
}

//index here is the configuration for a certain attack_mask
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

uint64_t Table::find_magic(square square, Table::piece p){
    std::array<uint64_t, 4096> occupancies;
    std::array<uint64_t, 4096> attacks;
    std::array<uint64_t, 4096> used_attacks;

    uint64_t attack_mask = p == BISHOP ? mask_bishop_attack(square) : mask_rook_attack(square);
    int occupancy_bitshift = 64 - (p == BISHOP ? bishop_occupancy_bits[square] : rook_occupancy_bits[square]);
    int num_bits = count_bits(attack_mask);

    for(int i = 0; i < (1 << num_bits); i++){
        occupancies[i] = occupancy(i, attack_mask);

        attacks[i] = p == BISHOP ? mask_bishop_attack_ray(square, occupancies[i]) 
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

void Table::fill_magic_table_rook(){
    for(int i = a8; i <= h1; i++){
        uint64_t attack_mask = mask_rook_attack(static_cast<square>(i));
        rook_attack_table[i] = attack_mask;

        int num_bits = count_bits(attack_mask);
        for(int index = 0; index < (1 << num_bits); index++){
            uint64_t occup = occupancy(index, attack_mask);

            int magic_index = int((occup * rook_magics[i]) >> (64 - num_bits));

            rook_table[i][magic_index] = mask_rook_attack_ray(static_cast<square>(i), occup);
        }
    }
}

void Table::fill_magic_table_bishop(){
    for(int i = a8; i <= h1; i++){
        uint64_t attack_mask = mask_bishop_attack(static_cast<square>(i));
        rook_attack_table[i] = attack_mask;

        int num_bits = count_bits(attack_mask);
        for(int index = 0; index < (1 << num_bits); index++){
            uint64_t occup = occupancy(index, attack_mask);
        
            int magic_index = int((occup * rook_magics[i]) >> (64 - num_bits));

            rook_table[i][magic_index] = mask_bishop_attack_ray(static_cast<square>(i), occup);
        }
    }
}

uint64_t Table::generate_pawn_white(square s){
    uint64_t board = get_square(s);

    uint64_t left_pawn_attack = (board & get_clear_file(FILE_A)) << 7;
    uint64_t right_pawn_attack = (board & get_clear_file(FILE_H)) << 9;

    return left_pawn_attack | right_pawn_attack;
}

uint64_t Table::generate_pawn_black(square s){
    uint64_t board = get_square(s);

    uint64_t left_pawn_attack = (board & get_clear_file(FILE_A)) >> 9;
    uint64_t right_pawn_attack = (board & get_clear_file(FILE_H)) >> 7;

    return left_pawn_attack | right_pawn_attack;
}

uint64_t Table::generate_king(square s){
    uint64_t curr_board = get_square(s);

    uint64_t clear_file_h = curr_board & get_clear_file(FILE_H);
    uint64_t clear_file_a = curr_board & get_clear_file(FILE_A);

    uint64_t spot1 = clear_file_a << 7;
    uint64_t spot2 = curr_board << 8;
    uint64_t spot3 = clear_file_h << 9;
    uint64_t spot5 = clear_file_h << 1;
    
    uint64_t spot4 = clear_file_a >> 1;
    uint64_t spot6 = clear_file_a >> 9;
    uint64_t spot7 = curr_board >> 8;
    uint64_t spot8 = clear_file_h >> 7;

    uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;
    return valid_spots;
}

uint64_t Table::generate_knight(square s){
    uint64_t mask_a = get_mask_file(FILE_A);
    uint64_t mask_h = get_mask_file(FILE_H);

    uint64_t mask_a_b = get_mask_file(FILE_A) & get_mask_file(FILE_B);
    uint64_t mask_g_h = get_mask_file(FILE_B) & get_mask_file(FILE_H);

    uint64_t spot1 = mask_a << 15;
    uint64_t spot2 = mask_h << 17;
    uint64_t spot3 = mask_a_b << 6;
    uint64_t spot4 = mask_g_h << 10;

    uint64_t spot5 = mask_a_b >> 10;
    uint64_t spot6 = mask_g_h >> 6;
    uint64_t spot7 = mask_a >> 17;
    uint64_t spot8 = mask_h >> 15;

    uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;

    return valid_spots;
}

void Table::init_leapers(){

    for(int i = a8; i <= h1; i++){
        pawn_attack_table[WHITE_PAWNS][i] =  generate_pawn_white(static_cast<square>(i));
        pawn_attack_table[BLACK_PAWNS][i] = generate_pawn_black(static_cast<square>(i));
        king_attack_table[i] = generate_king(static_cast<square>(i));
        knight_attack_table[i] = generate_knight(static_cast<square>(i));
    }
}

Table::Table() : 
clear_rank{
    18446744073709551360ULL,
    18446744073709486335ULL,
    18446744073692839935ULL,
    18446744069431361535ULL,
    18446742978492891135ULL,
    18446463698244468735ULL,
    18374967954648334335ULL,
    72057594037927935ULL,
}, 
mask_rank{
    255ULL,
    65280ULL,
    16711680ULL,
    4278190080ULL,
    1095216660480ULL,
    280375465082880ULL,
    71776119061217280ULL,
    18374686479671623680ULL,
}, 
clear_file{
    18374403900871474942ULL,
    18302063728033398269ULL,
    18157383382357244923ULL,
    17868022691004938231ULL,
    17289301308300324847ULL,
    16131858542891098079ULL,
    13816973012072644543ULL,
    9187201950435737471ULL,
},
mask_file{
    72340172838076673ULL,
    144680345676153346ULL,
    289360691352306692ULL,
    578721382704613384ULL,
    1157442765409226768ULL,
    2314885530818453536ULL,
    4629771061636907072ULL,
    9259542123273814144ULL,
}{
    
    for(int i = a8; i <= h1; i++){
        bishop_magics[i] = find_magic(static_cast<square>(i), BISHOP);
        rook_magics[i] = find_magic(static_cast<square>(i), ROOK);
    }

    init_leapers();
    fill_magic_table_bishop();
    fill_magic_table_rook();
}