#include "Move.hpp"
#include <cassert>
#include "board.hpp"

//index by attacker, caputred piece

//need to change!!!! The values are in the wrong place
std::array<std::array<int, 12>, 12> Move::mva_table{{
    {0, 105, 0, 205, 0, 305, 0, 405, 0, 505, 0, 605, }, 
    {105, 0, 205, 0, 305, 0, 405, 0, 505, 0, 605, 0, }, 
    {0, 104, 0, 204, 0, 304, 0, 404, 0, 504, 0, 604, }, 
    {104, 0, 204, 0, 304, 0, 404, 0, 504, 0, 604, 0, }, 
    {0, 103, 0, 203, 0, 303, 0, 403, 0, 503, 0, 603, }, 
    {103, 0, 203, 0, 303, 0, 403, 0, 503, 0, 603, 0, }, 
    {0, 102, 0, 202, 0, 302, 0, 402, 0, 502, 0, 602, }, 
    {102, 0, 202, 0, 302, 0, 402, 0, 502, 0, 602, 0, }, 
    {0, 101, 0, 201, 0, 301, 0, 401, 0, 501, 0, 601, }, 
    {101, 0, 201, 0, 301, 0, 401, 0, 501, 0, 601, 0, }, 
    {0, 100, 0, 200, 0, 300, 0, 400, 0, 500, 0, 600, }, 
    {100, 0, 200, 0, 300, 0, 400, 0, 500, 0, 600, 0, }, 
}};

int Move::score(State *st, int ply, Heuristics& h) const{
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

      return mva_table[piece()][taken] + 10000;
   }
    else{
        if(h.killer_moves[0][ply] == data){
            return 9000;
        }
        else if(h.killer_moves[1][ply] == data){
            return 8000;
        }
        return h.history_moves[piece()][target()];
    }

    return 0;
}