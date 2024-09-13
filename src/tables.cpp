#include <iostream>
#include "tables.hpp"


uint64_t Table::mask_rook_attack(Square s){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //RIGHT
    for(int r = rank, c = file + 1; c <= RANK_7; c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }
    //up
    for(int r = rank + 1, c = file; r <= RANK_7; r++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }
    //LEFT
    for(int r = rank, c = file - 1; c > 0 ; c--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }
    //down
    for(int r = rank - 1, c = file; r > 0; r--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }
    return attack_map;
}

uint64_t Table::mask_rook_attack_ray(Square s, uint64_t blockers){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //RIGHT
    for(int r = rank, c = file + 1; c <= RANK_8; c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }
    //up
    for(int r = rank + 1, c = file; r <= RANK_8; r++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }
    //LEFT
    for(int r = rank, c = file - 1; c >= 0 ; c--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }
    //down
    for(int r = rank - 1, c = file; r >= 0; r--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }
    return attack_map;
}

uint64_t Table::mask_bishop_attack(Square s){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //up diagonal RIGHT
    for(int r = rank + 1, c = file + 1; r <= RANK_7 && c <= RANK_7; r++, c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }

    //DOWN DIAGONAL RIGHT
    for(int r = rank - 1, c = file + 1; c <= RANK_7 && r > 0; r--, c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }

    //LEFT DIAGONAL UP
    for(int r = rank + 1, c = file  - 1; c > 0 && r <= RANK_7; c--, r++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }

    //LEFT DIAGONAL DOWN
    for(int r = rank - 1, c = file - 1; c > 0 && r > 0; r--, c--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
    }
    return attack_map;
}

uint64_t Table::mask_bishop_attack_ray(Square s, uint64_t blockers){
    int file = s%8;
    int rank = s/8;

    uint64_t attack_map = 0;
    
    //up diagonal RIGHT
    for(int r = rank + 1, c = file + 1; r <= RANK_8 && c <= RANK_8; r++, c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }

    //DOWN DIAGONAL RIGHT
    for(int r = rank - 1, c = file + 1; c <= RANK_8 && r >= 0; r--, c++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }

    //LEFT DIAGONAL UP
    for(int r = rank + 1, c = file  - 1; c >= 0 && r <= RANK_8; c--, r++){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
    }

    //LEFT DIAGONAL DOWN
    for(int r = rank - 1, c = file - 1; c >= 0 && r >= 0; r--, c--){
        attack_map |= get_square(static_cast<Square>(r*8 + c));
        if(blockers & get_square(static_cast<Square>(r*8 + c))) break;
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

//index here is the configuration for a certain attack_mask
uint64_t occupancy(int index, uint64_t attack_mask){
    int count = count_bits(attack_mask);
    uint64_t occup_map = 0;

    for(int i = 0; i < count; i++){
        Square s = static_cast<Square>(get_lsb_index(attack_mask));

        attack_mask ^= get_square(s);

        if(index & 1 << i){
            occup_map |= get_square(s);
        }
    }
    return occup_map;
}

uint64_t Table::find_magic(Square Square, Piece_type p){
    std::array<uint64_t, 4096> occupancies;
    std::array<uint64_t, 4096> attacks;
    std::array<uint64_t, 4096> used_attacks;

    uint64_t attack_mask = p == BISHOP ? mask_bishop_attack(Square) : mask_rook_attack(Square);
    int occupancy_bitshift = 64 - (p == BISHOP ? bishop_occupancy_bits[Square] : rook_occupancy_bits[Square]);
    int num_bits = count_bits(attack_mask);

    for(int i = 0; i < (1 << num_bits); i++){
        occupancies[i] = occupancy(i, attack_mask);

        attacks[i] = p == BISHOP ? mask_bishop_attack_ray(Square, occupancies[i]) 
                                    : mask_rook_attack_ray(Square, occupancies[i]);
    }

    for(int i = 0; i < 100000000; i++){
        uint64_t magic = generate_magic_nums();
        //need top bits to be set for hash function to work
        if(count_bits((attack_mask * magic) & 0xFF00000000000000ULL) < 6){
            continue;
        }
        used_attacks.fill(0ULL);

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
        uint64_t attack_mask = mask_rook_attack(static_cast<Square>(i));
        rook_attack_table[i] = attack_mask;

        int num_bits = rook_occupancy_bits[i];
        for(int index = 0; index < (1 << num_bits); index++){
            uint64_t occup = occupancy(index, attack_mask);

            int magic_index = int((occup * rook_magics[i]) >> (64 - num_bits));

            rook_table[i][magic_index] = mask_rook_attack_ray(static_cast<Square>(i), occup);
        }
    }  
}

void Table::fill_magic_table_bishop(){
    for(int i = a8; i <= h1; i++){
        uint64_t attack_mask = mask_bishop_attack(static_cast<Square>(i));
        bishop_attack_table[i] = attack_mask;

        int num_bits = bishop_occupancy_bits[i];
        for(int index = 0; index < (1 << num_bits); index++){
            uint64_t occup = occupancy(index, attack_mask);
        
            int magic_index = int((occup * bishop_magics[i]) >> (64 - num_bits));

            bishop_table[i][magic_index] = mask_bishop_attack_ray(static_cast<Square>(i), occup);
        }
    }
}

uint64_t Table::generate_pawn_white(Square s){
    uint64_t board = get_square(s);

    uint64_t left_pawn_attack = (board & clear_file[FILE_A]) >> 9;
    uint64_t right_pawn_attack = (board & clear_file[FILE_H]) >> 7;

    return (left_pawn_attack | right_pawn_attack);
}

uint64_t Table::generate_pawn_black(Square s){
    uint64_t board = get_square(s);

    uint64_t left_pawn_attack = (board & clear_file[FILE_A]) << 7;
    uint64_t right_pawn_attack = (board & clear_file[FILE_H]) << 9;
    return (left_pawn_attack | right_pawn_attack);
}

uint64_t Table::generate_king(Square s){
    uint64_t curr_board = get_square(s);

    uint64_t clear_file_h = curr_board & clear_file[FILE_H];
    uint64_t clear_file_a = curr_board & clear_file[FILE_A];

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

uint64_t Table::generate_knight(Square s){
    /*
        knight has 8 spots to move to
            x1x2x  
            3xxx4  
            xxNxx
            5xxx6
            x7x8x    
    */
    uint64_t curr_board = get_square(s);

    uint64_t mask_a = clear_file[FILE_A];
    uint64_t mask_h = clear_file[FILE_H];

    uint64_t mask_a_b = clear_file[FILE_A] & clear_file[FILE_B];
    uint64_t mask_g_h = clear_file[FILE_G] & clear_file[FILE_H];

    uint64_t spot1 = (curr_board & mask_a) >> 17;
    uint64_t spot2 = (curr_board & mask_h) >> 15;
    uint64_t spot3 = (curr_board & mask_a_b) >> 10;
    uint64_t spot4 = (curr_board & mask_g_h) >> 6;

    uint64_t spot5 = (curr_board & mask_a_b) << 6;
    uint64_t spot6 = (curr_board & mask_g_h) << 10;
    uint64_t spot7 = (curr_board & mask_a) << 15;
    uint64_t spot8 = (curr_board & mask_h) << 17;

    uint64_t valid_spots = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;

    return valid_spots;
}

void Table::init_sliders(){
    for(int i = a8; i <= h1; i++){
        king_attack_table[i] = generate_king(static_cast<Square>(i));
        knight_attack_table[i] = generate_knight(static_cast<Square>(i));
        pawn_attack_table[WHITE][i] =  generate_pawn_white(static_cast<Square>(i));
        pawn_attack_table[BLACK][i] = generate_pawn_black(static_cast<Square>(i));
    }
}

#include <unordered_set>
void Table::init_keys(){
    std::unordered_set<int> used;
    for(int piece = 0; piece < no_piece; piece++){
        for(int square = 0; square < none; square++){
            piece_keys[piece][square] = random_num();
            if(used.find(piece_keys[piece][square])!= used.end()){
                std::cout << "clash!\n";
            }
            used.insert(piece_keys[piece][square]);
        }
    }
    used.clear();
    for(int square = 0; square < none; square++){
        enpassant_keys[square] = random_num();
        if(used.find(enpassant_keys[square])!= used.end()){
            std::cout << "clash!\n";
        }
        used.insert(enpassant_keys[square]);
    }

    for(int i = 0; i < 16; i++){
        castling_keys[i] = random_num();
    }

    side_key = random_num();
}

Table::Table(){
    init_sliders();
    fill_magic_table_bishop();
    fill_magic_table_rook();
    init_keys();
}

const Table& table = Table::get_instance();