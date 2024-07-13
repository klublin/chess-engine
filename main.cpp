#include <iostream>
#include <string>
#include "board.hpp"
#include "engine.hpp"

/*
    Inital goal, play a game of chess on the commandline
*/

int main(){
    std::string input;
    Board b;

    b.print();

    std::cout << "hi! Welcome to a chess engine. Type end at the end of game to end the game\n";
    std::cout << "To input a move type the chess notation, the engine will respond with its own move\n";

    while(true){
        std::cin >> input;

        if(input == "end"){
            break;
        }
        
        b.update(input);
        b.print();
    }



}