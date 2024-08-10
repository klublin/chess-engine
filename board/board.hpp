#pragma once
#include <string>
#include <unordered_map>
#include "tables.hpp"
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

/*
    One probably no need to verify moves sent to the engine if using UCI. 

    capturing pieces 

    then we can move onto the evaluation and generation

*/

class Board{
    enum piece{
        PAWNS,
        KNIGHTS,
        BISHOPS,
        QUEEN,
        KING,
        ROOKS,
        NUM_PIECES
    };
public:

    enum color{
        WHITE = 0, 
        BLACK=1,
        BLACK_INDEX = 6
    };
    enum pieces{P,N,B,Q,K,R,p,n,b,q,k,r};

    enum castling{
        NONE=0,
        WK=1,
        WQ=2,
        BK=4,
        BQ=8
    };
    color side;
    Table& table;
    square enpessant;
    int castling_rights;

    //12 for all pieces and 1 for whole set
    std::array<uint64_t, 12> bitboards;

    #define OCCUP_WHITE 0
    #define OCCUP_BLACK 1
    #define OCCUP_ALL 2
    std::array<uint64_t, 3> occup;

    const static std::array<std::string, 64> square_map;

    //these maps may be better suited as arrays? Maybe cahnge for later when runtime becomes an issue
    // const static std::unordered_map<std::string, uint64_t> square_to_num;
    // const static std::unordered_map<uint64_t, std::string> num_to_square;
    static const std::unordered_map<int, char> symbol_map;
    static const std::unordered_map<char, piece> reverse_symbol_map;

    int which_piece(const uint64_t board);

    //sliders
    uint64_t get_pawn_attack_white(square);
    uint64_t get_pawn_attack_black(square);
    uint64_t get_knight_attack(square);
    uint64_t get_king_attack(square);
    //non sliders
    uint64_t get_bishop_attack(square, uint64_t);
    uint64_t get_queen_attack(square, uint64_t);
    uint64_t get_rook_attack(square, uint64_t);

    static constexpr const std::array<char, 12> pieces = {'P', 'N', 'B', 'Q', 'K', 'R', 'p', 'n', 'b', 'q', 'k', 'r'};
    void read_fen(const std::string&);
    inline int check_is_piece(char c);
    //todo add check(the chess one) boolean for both white and black maybe?
    bool white_check;
    bool black_check;

    bool attacked(square, color);
    //friend std::ostream& operator<<(std::ostream& os, const Board&);
    void print();
    Board();

    void update(const std::string&, const std::string&);
    void debug(const std::string& square); 
};