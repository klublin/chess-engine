#include "MoveGenerator.hpp"

uint64_t driver(Board& b, int level){
    if(level == 0){
        return 1ULL;
    }

    move_list list = generate_all(b);
    uint64_t nodes = 0;

    for(const Move& m : list){
        if(!b.make_move(m)){
            continue;
        }

        nodes += driver(b, level-1);
        
        b.unmake_move();
    }
    std::cout << "level: " << level << " nodes: " << nodes << "\n";
    return nodes;
}

void perft(const std::string& fen, int depth){
    Board b(fen);

    uint64_t tot = driver(b, 4);
    std::cout << "tot = " << tot << "\n";
}

int main(){
    perft(tricky_position, 3);
}