#pragma once
#include <string>
#include "board.hpp"


class MoveGenerator{
    Board b;
public:
    int generate_pawn_moves();
    int generate_knight_moves();
    int generate_rook_moves();
    int generate_bishop_moves();
    int generate_king_moves();
};