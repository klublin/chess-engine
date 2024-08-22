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
    list.print();
    const auto start{std::chrono::steady_clock::now()};
    for(const auto& m : list){
        if(!b.make_move(m))
            continue;
        
        uint64_t cum = nodes;
        if(m.source() == e8 && m.target() == e7){
            std::cout << "hi?\n";
        }
        driver(b, depth - 1);

        uint64_t old_nodes = nodes - cum;

        b.unmake_move(m);

        std::cout<< b.table.square_map[m.source()] 
            << b.table.square_map[m.target()] << ": " << old_nodes << "\n";
    }
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "depth " << depth << " nodes " << nodes << " in: " << elapsed_seconds.count() << " seconds\n";

    // int i = 0;
    // for(uint64_t attack : b.table.knight_attack_table){
    //     std::cout << "square " << b.table.square_map[i] << "\n";
    //     b.debug(attack);
    //     std::cout << "\n";
    //     i++;
    // }
    // std::cout << i << "\n";

}

#define s "r3k2r/p1pp1pb1/bn1Ppnp1/2q1N3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq - 0 1"

int main(){   
    perft(s, 3);
    // perft("r3k1nr/p1ppqQb1/bn2p1p1/3PN3/Pp2P3/2N4p/1PPBBPPP/R3K2R b KQkq - 0 1", 1);
    // Board bb("r3k1nr/p1ppqQb1/bn2p1p1/3PN3/Pp2P3/2N4p/1PPBBPPP/R3K2R b KQkq - 0 1");
    // bb.print();
    // move_list list = generate_all(bb);
    // std::cout << bb.make_move(list.moves[0]) << "\n";
    // list.print();

    // Board bb(tricky_position);

    // Move a(a2, a4, P, 0, 0);
    // bb.make_move(a);

    // move_list list = generate_all(bb);
    // list.print();

    // bb.make_move(a);
    // move_list list = generate_all(bb);
    // list.print();
    
    // // // Move b_move(d7, d5, p, 0, DOUBLE);
    // // // Move c(g1, h3, N, 0, 0);
    // // // Move d(c8, h3, b, 0, CAPTURE);

    // bb.make_move(a);
    



    // move_list list = generate_all(bb);
    // list.print();
    // // bb.make_move(b_move);
    // // bb.make_move(c);
    // // bb.make_move(d);

}