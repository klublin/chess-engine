#pragma once
#include <array>
#include <cstdint>
//these are more for testing purposes 
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

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
enum square{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, none
};

enum color{
    WHITE = 0, 
    BLACK = 6
};

inline color operator^(color a, color b){return static_cast<color>(int(a)^int(b));}

enum pawns{
    WHITE_PAWNS,
    BLACK_PAWNS
};

enum Castle{
    NONE=0,
    WK=1,
    WQ=2,
    BK=4,
    BQ=8
};

enum File {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H
};

enum Occup{
    OCCUP_WHITE,
    OCCUP_BLACK,
    OCCUP_ALL
};

enum Rank {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8
};

enum Piece{ P, N, B, R, Q, K, p, n, b, r, q, k, no_piece};

enum piece_type{    
    PAWN, 
    KNIGHT, 
    BISHOP, 
    ROOK, 
    QUEEN,
    KING,
    NUM_PIECES=6
};

enum Flags{
    CAPTURE=1,
    DOUBLE=2,
    ENPASSANT=4,
    CASTLING=8
};

static inline uint64_t get_square(square s){
    return 1ULL << s;
}

static inline int count_bits(uint64_t a) {
    int count;
    for(count = 0; a; count++, a &= (a-1));
    return count;
} 

static inline int get_lsb_index(uint64_t num){
    if(num){
        return count_bits((num & -num) - 1);
    }
    return -1;
}


/*
encoding of moves list
          binary move bits                               hexidecimal constants
    
    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000
*/
class Move{
public:
    int data;
    Move() : data(0){}
    Move(int source, int target, int piece, int promoted, int flags) : data((source) | (target << 6) | (piece << 12) | (promoted << 16) | (flags << 20)){}
    inline int source() const{ return data & 0x3f; }
    inline int target() const { return (data & 0xfc0) >> 6; }
    inline int piece() const { return (data & 0xf000) >> 12; }
    inline int promoted() const { return (data & 0xf0000) >> 16; }
    inline int capture() const { return (data & 0x100000); }
    inline int double_push() const { return (data & 0x200000); }
    inline int enpassant() const { return (data & 0x400000); }
    inline int castling() const { return (data & 0x800000); }
    inline int flags() const { return (data & 0xF00000) >> 20; }
};


