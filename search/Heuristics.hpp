#pragma once
#include "Move.hpp"
#include <array>


struct Heuristics{
    std::array<std::array<int, 64>, 2> killer_moves;
    std::array<std::array<int, 64>, 12> history_moves;

    std::array<std::array<Move, 64>, 64> pv_table;
    std::array<int, 64> pv_length;

    Heuristics() : killer_moves{}, history_moves{}, pv_table{}, pv_length{} {}
};