#include "Transposition.hpp"

void Transposition_table::write_hash(uint64_t hash_key, int score, int depth, int ply, Hash_Flags flags){
    Transposition_node *node = &tt[hash_key % Hash_Flags::HASH_SIZE];

    if(score < -MATE_SCORE) score -= ply;
    if(score > MATE_SCORE) score += ply;

    node->key = hash_key;
    node->flags = flags;
    node->depth = depth;
    node->score = score;
}

int Transposition_table::read_hash(uint64_t hash_key, int alpha, int beta, int depth, int ply){
    Transposition_node *node = &tt[hash_key % Hash_Flags::HASH_SIZE];

    if(node->key == hash_key && node->depth >= depth){
        int cached_score = node->score;

        if(cached_score < -MATE_SCORE) cached_score += ply;
        if(cached_score > MATE_SCORE) cached_score -= ply;

        if(node->flags == Hash_Flags::EXACT){
            return cached_score;
        }
        else if(node->flags == Hash_Flags::ALPHA && cached_score <= alpha){
            return alpha;
        }
        else if(node->flags == Hash_Flags::BETA && cached_score >= beta){
            return beta;
        }
    }

    return Hash_Flags::NO_HASH_ENTRY;
}