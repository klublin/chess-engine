#pragma once
#include <iostream>
#include "tables.hpp"
#include "State.hpp"

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
struct Heuristics;

class Move{
    int data;
    static std::array<std::array<int, 12>, 12> mva_table;
public:
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
    static inline Move none(){return Move();}

    int score(State *st, int ply, Heuristics& h) const;
    constexpr bool operator==(const Move& m) const {return data == m.data;};
    constexpr bool operator!=(const Move& m) const {return data != m.data;};
    void print(Table& t) const{
        std::cout << t.square_map[source()] << t.square_map[target()] << (promoted() ? t.pieces[promoted()] : char(0)) << " ";
    }

    int get_data() const{
        return data;
    }
    
};

//place at bottom for compiler
#include "Heuristics.hpp"