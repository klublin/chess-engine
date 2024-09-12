#include "uci.hpp"
#include <iostream>
#include "MoveGenerator.hpp"
#include <algorithm>

Table& UCI::t = Table::get_instance();

std::string UCI::str_move(const Move& m){
    std::string move;
    move += t.square_map[m.source()];
    move += t.square_map[m.target()];

    if(m.promoted()){
        move += t.pieces[m.promoted()];
    }
    return move;
}

inline void to_lower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](auto c) { return std::tolower(c); });
}

Move UCI::to_move(std::string& move){
    to_lower(move);
    for(const auto& m : generate_all(board)){
        if(move == str_move(m)){
           return m;
        }
    }
    return Move::none();
}

void UCI::set_position(std::string& fen, std::vector<std::string>& moves){
    board.read_fen(fen);

    for(std::string& move : moves){
        Move m = to_move(move);

        if(m != Move::none()){
            board.make_move(m);
        }
    }
}

void UCI::parse_position(std::istringstream& is){
    std::string token, fen;

    is >> token;

    if(token == "startpos"){
        fen = start_position;
        is >> token;
    }
    else if(token == "fen"){
        while(is >> token && token!= "moves"){
            fen += token + " ";
        }
    }
    else{
        return;
    }
    std::vector<std::string> moves;

    while(is >> token){
        moves.push_back(token);
    }

    set_position(fen, moves);
}

void UCI::parse_go(std::istringstream& is){
    std::string token;
    Search s;
    Heuristics *h = s.get_heuristic();
    int depth;

    is >> token;

    if(!(is >> depth)){
        depth=6;
    }
    
    for(int curr_depth = 1; curr_depth <= depth; curr_depth++){
        int score = s.negamax(board, Extremes::MIN, Extremes::MAX, curr_depth);
        std::cout << "info score cp " << score << " depth " << curr_depth << " nodes " << s.nodes << " ";

        for(int i = 0; i < h->pv_length[0]; i++){
            h->pv_table[0][i].print(t);
        }
        std::cout << "\n";
    }

    std::cout << "bestmove ";
    h->pv_table[0][0].print(Table::get_instance());
    std::cout << "\n";
}

void UCI::print(){
    board.print();
}

void UCI::loop(){
    std::string token,cmd;

    std::cout << "id name kevbot\nid name klublin\nuciok\n";

    while(1){
        if(!getline(std::cin, cmd)){
            return;
        }

        std::istringstream is(cmd);

        token.clear();
        is >> token;

        if(token == "isready"){
            std::cout << "readyok\n";
        }
        else if(token == "position"){
            parse_position(is);
        }
        else if(token == "go"){
            parse_go(is);
        }
        else if(token == "quit"){
            return;
        }
        else if(token == "uci"){
            std::cout << "id name kevbot\nid name klublin\nuciok\n";
        }
        else if(token == "d"){
            std::cout << "\n";
            print();
        }
        else if(token == "move"){
            std::string user_move;
            is >> user_move;
            Move m = to_move(user_move);

            if(m != Move::none()){
                board.make_move(m);
            }
            else{
                std::cout << "please input the correct move\n";
            }
        }
    }
}