#pragma once
#include <array>
#include <cstdint>

#define FILE_A 'a'
#define FILE_B 'b'
#define FILE_C 'c'
#define FILE_D 'd'
#define FILE_E 'e'
#define FILE_F 'f'
#define FILE_G 'g'
#define FILE_H 'h'

#define RANK_1 1
#define RANK_2 2
#define RANK_3 3
#define RANK_4 4
#define RANK_5 5
#define RANK_6 6
#define RANK_7 7
#define RANK_8 8

enum square{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

class Table{
    enum piece{
        PAWN,
        ROOK,
        BISHOP,
        QUEEN,
        KING
    };
    Table();

    uint64_t random_num();
    uint64_t generate_magic_nums();
    uint64_t find_magic(square, piece);
    
    void fill_magic_table_rook();
    void fill_magic_table_bishop();
    uint64_t mask_bishop_attack(square);
    uint64_t mask_rook_attack(square);
    uint64_t mask_bishop_attack_ray(square, uint64_t);
    uint64_t mask_rook_attack_ray(square, uint64_t);

    uint64_t generate_pawn_white(square);
    uint64_t generate_pawn_black(square);
    uint64_t generate_king(square);
    uint64_t generate_knight(square);
    void init_leapers();
public:
    const std::array<uint64_t, 8> clear_rank;
    inline uint64_t get_clear_rank(int index){
        return clear_rank[index - 1];
    }
    const std::array<uint64_t, 8> mask_rank;
    inline uint64_t get_mask_rank(int index){
        return clear_rank[index - 1];
    }
    const std::array<uint64_t, 8> clear_file;
    inline uint64_t get_clear_file(int index){
        return clear_file[index - 1];
    }
    const std::array<uint64_t, 8> mask_file;
    inline uint64_t get_mask_file(int index){
        return mask_file[index - 1];
    }

    #define WHITE_PAWNS 0
    #define BLACK_PAWNS 1

    std::array<uint64_t, 64> bishop_magics;
    std::array<uint64_t, 64> rook_magics;
    std::array<std::array<uint64_t, 4096>, 64> rook_table;
    std::array<std::array<uint64_t, 512>, 64> bishop_table;
    std::array<int, 64> rook_attack_table;
    std::array<int, 64> bishop_attack_table;
    std::array<int, 64> king_attack_table;
    std::array<std::array<int, 64>, 64> pawn_attack_table;
    std::array<int, 64> knight_attack_table;

    static Table& get_instance(){
        static Table t;
        return t;
    }
};

inline uint64_t get_square(square s){
    return 1ULL << s;
}

static int __attribute__((unused)) count_bits(uint64_t a) {
    int count;
    for(count = 0; a; count++, a &= (a-1));
    return count;
} 