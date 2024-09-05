#include "Move.hpp"
#include <cassert>
#include "board.hpp"

//index by attacker, caputred piece

//need to change!!!! The values are in the wrong place
std::array<std::array<int, 12>, 12> Move::mva_table{{
   { 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605, },
   { 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605, },
   { 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604, },
   { 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604, },
   { 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603, },
   { 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603, },
   { 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602, },
   { 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602, },
   { 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601, },
   { 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601, },
   { 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600, },   
   { 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600, },
}};

int Move::score(State *st, int ply) const{
   if(capture()){
      Square dest = static_cast<Square>(target());
      Piece taken;
      if(enpassant()){
         taken = P + st->side;
      }
      else
         taken = st->which_piece(dest);

      assert(taken!= K);
      assert(taken!=k);
      assert(taken!=no_piece);

      return mva_table[piece()][taken];
   }
    // else{
    //     Table& table = Table::get_instance();
    //     if(table.killer_moves[0][ply] == data){
    //         return 9000;
    //     }
    //     else if(table.killer_moves[1][ply] == data){
    //         return 8000;
    //     }
    //     return table.history_moves[piece()][target()];
    // }

    return 0;
}