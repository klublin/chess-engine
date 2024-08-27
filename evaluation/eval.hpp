#include <array>
#include "State.hpp"

class Evaluation{
    //indexed based on enum piece
    static std::array<int, 12> material_score;
    static std::array<std::array<int, 64>, 12> positional_scores;
    Evaluation();
    template<color c>
    static inline int score_board(uint64_t board, int piece);
public:
    static int score_material(State& st);
};