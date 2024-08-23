#include "MoveGenerator.hpp"
#include <chrono>

uint64_t nodes;
void driver(Board& b, int level){
    if(level == 0){
        nodes++;
        return;
    }

    move_list list = generate_all(b);

    for(const auto& m : list){
        if(!b.make_move(m))
            continue;
        driver(b, level - 1);

        b.unmake_move(m);
    }
}

void perft(const std::string& fen, int depth){
    Board b(fen);
    move_list list = generate_all(b);
    const auto start{std::chrono::steady_clock::now()};
    for(const auto& m : list){
        if(!b.make_move(m))
            continue;
        
        uint64_t cum = nodes;

        driver(b, depth - 1);

        uint64_t old_nodes = nodes - cum;

        b.unmake_move(m);

        std::cout<< b.table.square_map[m.source()] 
            << b.table.square_map[m.target()] << ": " << old_nodes << "\n";
    }
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "depth " << depth << " nodes " << nodes << " in: " << elapsed_seconds.count() << " seconds\n";
}

#define s "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq - 0 1"

int main(){
    perft(s, 2);	
    //perft(s, 3);

}