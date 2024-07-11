#include "board.hpp"
#include <iostream>

const std::unordered_map<std::string, uint64_t> Board::square_to_num = {
    {"A1", 1}, {"B1", 2}, {"C1", 4}, {"D1", 8}, {"E1", 16}, {"F1", 32}, {"G1", 64}, {"H1", 128},
    {"A2", 256}, {"B2", 512}, {"C2", 1024}, {"D2", 2048}, {"E2", 4096}, {"F2", 8192}, {"G2", 16384}, {"H2", 32768},
    {"A3", 65536}, {"B3", 131072}, {"C3", 262144}, {"D3", 524288}, {"E3", 1048576}, {"F3", 2097152}, {"G3", 4194304}, {"H3", 8388608},
    {"A4", 16777216}, {"B4", 33554432}, {"C4", 67108864}, {"D4", 134217728}, {"E4", 268435456}, {"F4", 536870912}, {"G4", 1073741824}, {"H4", 2147483648},
    {"A5", 4294967296}, {"B5", 8589934592}, {"C5", 17179869184}, {"D5", 34359738368}, {"E5", 68719476736}, {"F5", 137438953472}, {"G5", 274877906944}, {"H5", 549755813888},
    {"A6", 1099511627776}, {"B6", 2199023255552},{"C6", 4398046511104}, {"D6", 8796093022208}, {"E6", 17592186044416}, {"F6", 35184372088832}, {"G6", 70368744177664}, {"H6", 140737488355328},
    {"A7", 281474976710656},{"B7", 562949953421312}, {"C7", 1125899906842624}, {"D7", 2251799813685248}, {"E7", 4503599627370496}, {"F7", 9007199254740992}, {"G7", 18014398509481984}, {"H7", 36028797018963968}, 
    {"A8", 72057594037927936}, {"B8", 144115188075855872}, {"C8", 288230376151711744}, {"D8", 576460752303423488}, {"E8", 1152921504606846976}, {"F8", 2305843009213693952}, {"G8", 4611686018427387904},{"H8", 9223372036854775808ULL},
};

const std::unordered_map<uint64_t, std::string> Board::num_to_square = {
    {1, "A1"}, {2, "B1"}, {4, "C1"}, {8, "D1"}, {16, "E1"}, {32, "F1"}, {64, "G1"}, {128, "H1"},
    {256, "A2"}, {512, "B2"}, {1024, "C2"}, {2048, "D2"}, {4096, "E2"}, {8192, "F2"}, {16384, "G2"}, {32768, "H2"},
    {65536, "A3"}, {131072, "B3"}, {262144, "C3"}, {524288, "D3"}, {1048576, "E3"}, {2097152, "F3"}, {4194304, "G3"}, {8388608, "H3"},
    {16777216, "A4"}, {33554432, "B4"}, {67108864, "C4"}, {134217728, "D4"}, {268435456, "E4"}, {536870912, "F4"}, {1073741824, "G4"}, {2147483648, "H4"},
    {4294967296, "A5"}, {8589934592, "B5"}, {17179869184, "C5"}, {34359738368, "D5"}, {68719476736, "E5"}, {137438953472, "F5"}, {274877906944, "G5"}, {549755813888, "H5"},
    {1099511627776, "A6"}, {2199023255552, "B6"}, {4398046511104, "C6"}, {8796093022208, "D6"}, {17592186044416, "E6"}, {35184372088832, "F6"}, {70368744177664, "G6"}, {140737488355328, "H6"},
    {281474976710656, "A7"}, {562949953421312, "B7"}, {1125899906842624, "C7"}, {2251799813685248, "D7"}, {4503599627370496, "E7"}, {9007199254740992, "F7"}, {18014398509481984, "G7"}, {36028797018963968, "H7"},
    {72057594037927936, "A8"}, {144115188075855872, "B8"}, {288230376151711744, "C8"}, {576460752303423488, "D8"}, {1152921504606846976, "E8"}, {2305843009213693952, "F8"}, {4611686018427387904, "G8"}, {9223372036854775808ULL, "H8"}
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
};

Board::Board() : side(WHITE){
    bitboards[ROOKS + WHITE] = square_to_num.at("A1") | square_to_num.at("H1");
    bitboards[ROOKS + BLACK] = square_to_num.at("A8") | square_to_num.at("H8");
    
    bitboards[BISHOPS + WHITE] = square_to_num.at("C1") | square_to_num.at("F1");
    bitboards[BISHOPS + BLACK] = square_to_num.at("C8") | square_to_num.at("F8");

    bitboards[PAWNS + WHITE] = square_to_num.at("A2") | square_to_num.at("B2") | square_to_num.at("C2") | square_to_num.at("D2") | 
                    square_to_num.at("E2") | square_to_num.at("F2") | square_to_num.at("G2") | square_to_num.at("H2");
    bitboards[PAWNS + BLACK] = square_to_num.at("A7") | square_to_num.at("B7") | square_to_num.at("C7") | square_to_num.at("D7") | 
                    square_to_num.at("E7") | square_to_num.at("F7") | square_to_num.at("G7") | square_to_num.at("H7");
    
    bitboards[QUEEN + WHITE] = square_to_num.at("D1");
    bitboards[QUEEN + BLACK] = square_to_num.at("D8");
    
    bitboards[KING + WHITE] = square_to_num.at("E1");
    bitboards[KING + BLACK] = square_to_num.at("E8");

    bitboards[KNIGHTS + WHITE] = square_to_num.at("B1") | square_to_num.at("G1"); 
    bitboards[KNIGHTS + BLACK] = square_to_num.at("B8") | square_to_num.at("G8");
}

void Board::update(const std::string& s){

}

char Board::which_piece(const uint64_t square){
    
    for(int i = 0; i < 12; i++){
        if((bitboards[i] & square) != 0)
            return symbol_map.at(i);
    }
    return ' ';
}

void Board::print(){
    uint64_t mask = (uint64_t)1 << 63;

    uint64_t all_pieces;

    for(int i = WHITE; i < NUM_PIECES; i++){
        all_pieces |= (bitboards[i] | bitboards[i + BLACK]);
    }

    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            uint64_t mask = 1ULL << (i*8+j);
            //std::cout << "mask = " << mask << " " << i << " " << j << "\n";
            std::cout << which_piece(all_pieces & mask) << " ";
        }
        std::cout << "\n";
    }
}