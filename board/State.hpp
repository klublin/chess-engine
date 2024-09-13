#pragma once
#include <stack>
#include <iostream>
#include "tables.hpp"

class State{
public:
    void generate_hash();
    color side;
    Square enpessant;
    uint8_t castling_rights;
    Piece captured;
    uint64_t hash_key;

    std::array<uint64_t, 12> bitboards;
    std::array<uint64_t, 3> occup;

    State() : captured(no_piece), hash_key(0), bitboards{0}, occup{0} {}

    // we don't need to copy the bitboards
    // State(const State& t){
    //     side = t.side;
    //     enpessant = t.enpessant;
    //     castling_rights = t.castling_rights;
    //     captured = t.captured;
    // }
    inline void clear(){
        bitboards.fill(0);
        occup.fill(0);
    }

    Piece which_piece(const Square s){
        uint64_t board = get_square(static_cast<Square>(s));
        for(int i = 0; i < 12; i++){
            if((bitboards[i] & board) != 0)
                return static_cast<Piece>(i);
        }
        return no_piece;
    }
};



