#include "MoveGenerator.hpp"
#include <chrono>
#include <iostream>


uint64_t perft(Board& b, int depth){
    if(depth == 0){
        return 1ULL;
    }
    move_list l = generate_all(b);

    uint64_t nodes = 0;
    for(const auto& m : l){
        if(!b.make_move(m))
            continue;
        nodes += perft(b, depth - 1);
        b.unmake_move(m);
    }

    return nodes;
}

void perft_test(const std::string& fen, int depth){
    Board board(fen);
    Table& t = Table::get_instance();
    uint64_t curr, tot = 0;

    const auto start{std::chrono::steady_clock::now()};

    move_list l = generate_all(board);
    for(const auto& m : l){
        if(!board.make_move(m)){
            continue;
        }
        curr = perft(board, depth - 1);
        tot += curr;
        board.unmake_move(m);

        std::cout<< t.square_map[m.source()] 
            << t.square_map[m.target()] << (m.promoted() ? t.pieces[m.promoted()] : (char)0) << ": " << curr << "\n";
        
    }

    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "depth " << depth << " nodes " << tot << " in: " << elapsed_seconds.count() << " seconds\n";
}

int main(){
    perft_test(tricky_position, 5);
}