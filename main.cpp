#include <iostream>
#include <string>
#include "uci.hpp"
#include "eval.hpp"

/*
    Inital goal, play a game of chess on the commandline
*/

int main(){
    Board b("rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1");

    std::cout << Evaluation::score_material(b.st) << "\n";

    // Search s;

    // s.negamax(b, Extremes::MIN, Extremes::MAX, 2);
}