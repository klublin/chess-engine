#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
/*
Board representation

 0,  1,  2,  3,  4,  5,  6,  7
 8,  9, 10, 11, 12, 13, 14, 15
16, 17, 18, 19, 20, 21, 22, 23
24, 25, 26, 27, 28, 29, 30, 31
32, 33, 34, 35, 36, 37, 38, 39
40, 41, 42, 43, 44, 45, 46, 47
48, 49, 50, 51, 52, 53, 54, 55
56, 57, 58, 59, 60, 61, 62, 63

a8, b8, c8, d8, e8, f8, g8, h8
a7, b7, c7, d7, e7, f7, g7, h7
a6, b6, c6, d6, e6, f6, g6, h6
a5, b5, c5, d5, e5, f5, g5, h5
a4, b4, c4, d4, e4, f4, g4, h4
a3, b3, c3, d3, e3, f3, g3, h3
a2, b2, c2, d2, e2, f2, g2, h2
a1, b1, c1, d1, e1, f1, g1, h1

*/

class Board{

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

    enum color{
        WHITE = 0, 
        BLACK = 6
    };
    color side;

    enum piece{
        PAWNS,
        KNIGHTS,
        BISHOPS,
        QUEEN,
        KING,
        ROOKS,
        NUM_PIECES
    };

    uint64_t bitboards[12];

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
    
    const static std::unordered_map<std::string, square> square_map;
    inline uint64_t get_square(Board::square s);

    //these maps may be better suited as arrays? Maybe cahnge for later when runtime becomes an issue
    // const static std::unordered_map<std::string, uint64_t> square_to_num;
    // const static std::unordered_map<uint64_t, std::string> num_to_square;
    const static std::unordered_map<int, char> symbol_map;
    const static std::unordered_map<char, piece> reverse_symbol_map;

    //again these might become array's, if runtime is an issue
    const static std::unordered_map<int, uint64_t> clear_rank;
    const static std::unordered_map<int, uint64_t> mask_rank;
    const static std::unordered_map<char, uint64_t> clear_file;
    const static std::unordered_map<char, uint64_t> mask_file;

    //magics
    static bool init_magic;
    static uint64_t rook_table[64][512];
    static uint64_t bishop_table[64][512];
    
    //filling might be better done in script tbd
    uint64_t mask_bishop_attack(square);
    uint64_t mask_rook_attack(square);
    uint64_t mask_bishop_attack_ray(square, uint64_t);
    uint64_t mask_rook_attack_ray(square, uint64_t);
    uint64_t fill_magic_table_rook();
    uint64_t fill_magic_table_bishop();
    static uint64_t random_num();
    static uint64_t generate_magic_nums();
    uint64_t find_magic(square, piece);

    int which_piece(const uint64_t board);

    //todo might need to change these function names tbh
    uint64_t check_pawn_move_white(uint64_t, uint64_t, uint64_t);
    uint64_t check_pawn_move_black(uint64_t, uint64_t, uint64_t);
    uint64_t check_knight_move(uint64_t, uint64_t);
    uint64_t check_bishop_move(uint64_t, uint64_t);
    uint64_t check_queen_move(uint64_t, uint64_t);
    uint64_t check_king_move(uint64_t, uint64_t);
    uint64_t check_rook_move(uint64_t, uint64_t);
    //todo add check(the chess one) boolean for both white and black maybe?
public:
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
    void print();
    Board();

    void update(const std::string&, const std::string&);
    void debug(const std::string& square); 
    
};