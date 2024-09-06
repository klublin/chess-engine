#include <iostream>
#include <string>
#include "uci.hpp"
#include "eval.hpp"
#include "perft.hpp"
#include "MoveGenerator.hpp"
/*
    Inital goal, play a game of chess on the commandline
*/

int main(){
    UCI u;
    u.loop();

    // Board b(tricky_position);
    // Search s;

    // s.negamax(b, Extremes::MIN, Extremes::MAX, 1);

    // Search s;

    // s.negamax(b, Extremes::MIN, Extremes::MAX, 2);
}