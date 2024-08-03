#pragma once
#include <array>
#include <cstdint>

#define FILE_A 'a'
#define FILE_B 'b'
#define FILE_C 'c'
#define FILE_D 'd'
#define FILE_E 'e'
#define FILE_F 'f'
#define FILE_G 'g'
#define FILE_H 'h'

#define RANK_1 1
#define RANK_2 2
#define RANK_3 3
#define RANK_4 4
#define RANK_5 5
#define RANK_6 6
#define RANK_7 7
#define RANK_8 8

enum square{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

class Table{
    enum piece{
        PAWN,
        ROOK,
        BISHOP,
        QUEEN,
        KING
    };
    Table();

    uint64_t random_num();
    uint64_t generate_magic_nums();
    uint64_t find_magic(square, piece);
    
    void fill_magic_table_rook();
    void fill_magic_table_bishop();
    uint64_t mask_bishop_attack(square);
    uint64_t mask_rook_attack(square);
    uint64_t mask_bishop_attack_ray(square, uint64_t);
    uint64_t mask_rook_attack_ray(square, uint64_t);

    uint64_t generate_pawn_white(square);
    uint64_t generate_pawn_black(square);
    uint64_t generate_king(square);
    uint64_t generate_knight(square);
    void init_sliders();
public:
    const std::array<uint64_t, 8> clear_rank{
        18446744073709551360ULL,
        18446744073709486335ULL,
        18446744073692839935ULL,
        18446744069431361535ULL,
        18446742978492891135ULL,
        18446463698244468735ULL,
        18374967954648334335ULL,
        72057594037927935ULL,
    };
    inline uint64_t get_clear_rank(int index){
        return clear_rank[index - 1];
    }
    const std::array<uint64_t, 8> mask_rank{
        255ULL,
        65280ULL,
        16711680ULL,
        4278190080ULL,
        1095216660480ULL,
        280375465082880ULL,
        71776119061217280ULL,
        18374686479671623680ULL,
    };
    inline uint64_t get_mask_rank(int index){
        return clear_rank[index - 1];
    }
    const std::array<uint64_t, 8> clear_file{
        18374403900871474942ULL,
        18302063728033398269ULL,
        18157383382357244923ULL,
        17868022691004938231ULL,
        17289301308300324847ULL,
        16131858542891098079ULL,
        13816973012072644543ULL,
        9187201950435737471ULL,
    };
    inline uint64_t get_clear_file(int index){
        return clear_file[index - 1];
    }
    const std::array<uint64_t, 8> mask_file{
        72340172838076673ULL,
        144680345676153346ULL,
        289360691352306692ULL,
        578721382704613384ULL,
        1157442765409226768ULL,
        2314885530818453536ULL,
        4629771061636907072ULL,
        9259542123273814144ULL,
    };
    inline uint64_t get_mask_file(int index){
        return mask_file[index - 1];
    }

    #define WHITE_PAWNS 0
    #define BLACK_PAWNS 1

    const std::array<uint64_t, 64> bishop_magics{
        0x420c80100408202, 0x2300224811184, 0x842140302e00000, 0x404404284000100, 0x840420006c0010, 0x81042004804004, 0x1004980130102880, 0x81040084044201,
        0x300869100c0044, 0x80221024208082, 0x40404084000, 0x180182184a00000, 0x6808040308003c44, 0x1012080404010a, 0x28000c012188200c, 0x800428404014500,
        0xc008001002108400, 0x1802026018066488, 0x1010808050010, 0xc000124028000, 0x804000880a03002, 0x22012410440418, 0x8001000088011004, 0x2801000040761000,
        0x430400011024240, 0x1885080221360404, 0x880030802400, 0x5040040102021004, 0x1001001004000, 0x624150000900481, 0xa80082100c0a2200, 0x426200c900b40200,
        0x104104200480200, 0x82101102040100, 0x52005100300100, 0x8080020082280080, 0x8140002022020080, 0x4a0080640008068, 0x2008408108040120, 0x80c040420204130,
        0x1012022001000, 0x800a4802106818a8, 0x81100802402c080, 0x400810c010401208, 0x51600410122904, 0x88a200240800505, 0x2882129000400, 0x1584040082058032,
        0x4010842904000, 0x201040082080080, 0x100020352180010, 0x1824420042020110, 0x8405040020, 0x2400810a1020401, 0x80a880124040000, 0x4204840082060020,
        0x1820804048200802, 0x6100182208020800, 0x42081140, 0x6140080840420210, 0xc461411102020c, 0x1000002224900081, 0x2000100410140053, 0x89a1121896040240
    };
    
    const std::array<uint64_t, 64> rook_magics{
        0xa8002c000108020, 0x6c00049b0002001, 0x100200010090040, 0x2480041000800801, 0x280028004000800, 0x900410008040022, 0x280020001001080, 0x2880002041000080,
        0xa000800080400034, 0x4808020004000, 0x2290802004801000, 0x411000d00100020, 0x402800800040080, 0xb000401004208, 0x2409000100040200, 0x1002100004082,
        0x22878001e24000, 0x1090810021004010, 0x801030040200012, 0x500808008001000, 0xa08018014000880, 0x8000808004000200, 0x201008080010200, 0x801020000441091,
        0x800080204005, 0x1040200040100048, 0x120200402082, 0xd14880480100080, 0x12040280080080, 0x100040080020080, 0x9020010080800200, 0x813241200148449,
        0x491604001800080, 0x100401000402001, 0x4820010021001040, 0x400402202000812, 0x209009005000802, 0x810800601800400, 0x4301083214000150, 0x204026458e001401,
        0x40204000808000, 0x8001008040010020, 0x8410820820420010, 0x1003001000090020, 0x804040008008080, 0x12000810020004, 0x1000100200040208, 0x430000a044020001,
        0x280009023410300, 0xe0100040002240, 0x200100401700, 0x2244100408008080, 0x8000400801980, 0x2000810040200, 0x8010100228810400, 0x2000009044210200,
        0x4080008040102101, 0x40002080411d01, 0x2005524060000901, 0x502001008400422, 0x489a000810200402, 0x1004400080a13, 0x4000011008020084, 0x26002114058042
    };

    const std::array<int, 64> bishop_occupancy_bits{
        6,5,5,5,5,5,5,6,
        5,5,5,5,5,5,5,5,
        5,5,7,7,7,7,5,5,
        5,5,7,9,9,7,5,5,
        5,5,7,9,9,7,5,5,
        5,5,7,7,7,7,5,5,
        5,5,5,5,5,5,5,5,
        6,5,5,5,5,5,5,6,
    };
    
    const std::array<int, 64> rook_occupancy_bits{
        12,11,11,11,11,11,11,12,
        11,10,10,10,10,10,10,11,
        11,10,10,10,10,10,10,11,
        11,10,10,10,10,10,10,11,
        11,10,10,10,10,10,10,11,
        11,10,10,10,10,10,10,11,
        11,10,10,10,10,10,10,11,
        12,11,11,11,11,11,11,12,
    };

    std::array<std::array<uint64_t, 4096>, 64> rook_table;
    std::array<std::array<uint64_t, 512>, 64> bishop_table;
    std::array<uint64_t, 64> rook_attack_table;
    std::array<uint64_t, 64> bishop_attack_table;
    
    std::array<uint64_t, 64> king_attack_table;
    std::array<std::array<uint64_t, 64>, 64> pawn_attack_table;
    std::array<uint64_t, 64> knight_attack_table;

    static Table& get_instance(){
        static Table t;
        return t;
    }
};

inline uint64_t get_square(square s){
    return 1ULL << s;
}

static inline int count_bits(uint64_t a) {
    int count;
    for(count = 0; a; count++, a &= (a-1));
    return count;
} 