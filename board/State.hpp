#include <stack>
#include "tables.hpp"

class State{
public:
    color side;
    square enpessant;
    uint8_t castling_rights;
    Piece captured;

    std::array<uint64_t, 12> bitboards;
    std::array<uint64_t, 3> occup;

    State() : captured(no_piece), bitboards{0}, occup{0} {}

    // we don't need to copy the bitboards
    // State(const State& t){
    //     side = t.side;
    //     enpessant = t.enpessant;
    //     castling_rights = t.castling_rights;
    //     captured = t.captured;
    // }
};