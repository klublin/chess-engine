#pragma once
#include "Move.hpp"
#include <array>


struct Heuristics{
    std::array<std::array<int, Extremes::MAX_PLY>, 2> killer_moves;
    std::array<std::array<int, Extremes::MAX_PLY>, 12> history_moves;

    std::array<std::array<Move, Extremes::MAX_PLY>, Extremes::MAX_PLY> pv_table;
    std::array<int, Extremes::MAX_PLY> pv_length;

    Heuristics() : killer_moves{}, history_moves{}, pv_table{}, pv_length{} {}
};