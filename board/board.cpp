#include "board.hpp"


const std::unordered_map<std::string, uint64_t> Board::square_to_num = {
    {"A1", 0 }, {"A2", 1 }, {"A3", 2 }, {"A4", 4 }, {"A5", 8 }, {"A6", 16 }, {"A7", 32 }, {"A8", 64 },
    {"B1", 128 }, {"B2", 256 }, {"B3", 512 }, {"B4", 1024 }, {"B5", 2048 }, {"B6", 4096 }, {"B7", 8192 }, {"B8", 16384 }, 
    {"C1", 32768 }, {"C2", 65536 },{"C3", 131072 }, {"C4", 262144 }, {"C5", 524288 }, {"C6", 1048576 }, {"C7", 2097152 }, {"C8", 4194304 },
    {"D1", 8388608 },{"D2", 16777216 },{"D3", 33554432 },{"D4", 67108864 },{"D5", 134217728 },{"D6", 268435456 },{"D7", 536870912 },{"D8", 1073741824 },
    {"E1", 2147483648 },{"E2", 4294967296 },{"E3", 8589934592 },{"E4", 17179869184 },{"E5", 34359738368 },{"E6", 68719476736 },{"E7", 137438953472 },{"E8", 274877906944 },
    {"F1", 549755813888 },{"F2", 1099511627776 },{"F3", 2199023255552 },{"F4", 4398046511104 },{"F5", 8796093022208 },{"F6", 17592186044416 },{"F7", 35184372088832 },{"F8", 70368744177664 },
    {"G1", 140737488355328 },{"G2", 281474976710656 },{"G3", 562949953421312 },{"G4", 1125899906842624 },{"G5", 2251799813685248 },{"G6", 4503599627370496 },{"G7", 9007199254740992 },{"G8", 18014398509481984 },
    {"H1", 36028797018963968 },{"H2", 72057594037927936 },{"H3", 144115188075855872 },{"H4", 288230376151711744 },{"H5", 576460752303423488 },{"H6", 1152921504606846976 },{"H7", 2305843009213693952 }, {"H8", 4611686018427387904 }
};

const std::unordered_map<uint64_t, std::string> Board::num_to_square = {
    { 0 ,"A1"}, { 1 ,"A2"},{ 2 ,"A3"},{ 4 ,"A4"},{ 8 ,"A5"},{ 16 ,"A6"},{ 32 ,"A7"},{ 64 ,"A8"},
    { 128 ,"B1"},{ 256 ,"B2"},{ 512 ,"B3"},{ 1024 ,"B4"},{ 2048 ,"B5"},{ 4096 ,"B6"},{ 8192 ,"B7"},{ 16384 ,"B8"},
    { 32768 ,"C1"},{ 65536 ,"C2"},{ 131072 ,"C3"},{ 262144 ,"C4"},{ 524288 ,"C5"},{ 1048576 ,"C6"},{ 2097152 ,"C7"},{ 4194304 ,"C8"},
    { 8388608 ,"D1"},{ 16777216 ,"D2"},{ 33554432 ,"D3"}, {67108864 ,"D4"},{134217728,"D5"},{268435456,"D6"},{536870912, "D7"},{1073741824, "D8"},
    { 2147483648 ,"E1"},{ 4294967296 ,"E2"},{ 8589934592 ,"E3"},{ 17179869184 ,"E4"},{ 34359738368 ,"E5"},{ 68719476736 ,"E6"},{ 137438953472 ,"E7"},{ 274877906944 ,"E8"},
    { 549755813888 ,"F1"},{ 1099511627776 ,"F2"},{ 2199023255552 ,"F3"},{ 4398046511104 ,"F4"},{ 8796093022208 ,"F5"},{ 17592186044416 ,"F6"},{ 35184372088832 ,"F7"},{ 70368744177664 ,"F8"},
    { 140737488355328 ,"G1"},{ 281474976710656 ,"G2"},{ 562949953421312 ,"G3"},{ 1125899906842624 ,"G4"},{ 2251799813685248 ,"G5"},{ 4503599627370496 ,"G6"},{ 9007199254740992 ,"G7"},{ 18014398509481984 ,"G8"},
    { 36028797018963968 ,"H1"},{ 72057594037927936 ,"H2"},{ 144115188075855872 ,"H3"},{ 288230376151711744 ,"H4"},{ 576460752303423488 ,"H5"},{ 1152921504606846976 ,"H6"},{ 2305843009213693952 ,"H7"},{ 4611686018427387904 ,"H8"}
};

Board::Board() : side(WHITE){
    board[ROOKS + WHITE] = square_to_num.at("A1") | square_to_num.at("H1");
    board[ROOKS + BLACK] = square_to_num.at("A8") | square_to_num.at("H8");
    
    board[BISHOPS + WHITE] = square_to_num.at("C1") | square_to_num.at("F1");
    board[BISHOPS + BLACK] = square_to_num.at("C8") | square_to_num.at("C8");

    board[PAWNS + WHITE] = square_to_num.at("A2") | square_to_num.at("B2") | square_to_num.at("C2") | square_to_num.at("D2") | 
                    square_to_num.at("E2") | square_to_num.at("F2") | square_to_num.at("G2") | square_to_num.at("H2");
    board[PAWNS + BLACK] = square_to_num.at("A7") | square_to_num.at("B7") | square_to_num.at("C7") | square_to_num.at("D7") | 
                    square_to_num.at("E7") | square_to_num.at("F7") | square_to_num.at("G7") | square_to_num.at("H7");
    
    board[QUEEN + WHITE] = square_to_num.at("D1");
    board[QUEEN + BLACK] = square_to_num.at("D8");
    
    board[KING + WHITE] = square_to_num.at("E1");
    board[KING + BLACK] = square_to_num.at("E8");

    board[KNIGHTS + WHITE] = square_to_num.at("B1") | square_to_num.at("G1"); 
    board[KNIGHTS + BLACK] = square_to_num.at("B8") | square_to_num.at("G8");
}

void Board::update(const std::string& s){

}