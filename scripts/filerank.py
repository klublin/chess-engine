import numpy as np 

letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']


#horizontal lines
clear_rank = {}
mask_rank = {}

#vertical lines
clear_file = {}
mask_file = {}

num = np.uint64(0x0101010101010101)

for letter in letters:
    clear_file[letter] = ~num
    mask_file[letter] = num 
    num <<= 1

rank_num = np.uint64(0xFF)

for i in range(1, 9):
    clear_rank[9-i] = ~rank_num
    mask_rank[9-i] = rank_num 
    rank_num <<= 8


print('const std::unordered_map<char, uint64_t> Board::clear_rank{')
for key, val in reversed(clear_rank.items()):
    s = '    {' + str(key) + ',' + str(val) + 'ULL},'
    print(s)
print('};')

print('const std::unordered_map<char, uint64_t> Board::mask_rank{')
for key, val in reversed(mask_rank.items()):
    s = '    {' + str(key) + ',' + str(val) + 'ULL},'
    print(s)
print('};')

print('const std::unordered_map<int, uint64_t> Board::clear_file{')
for key, val in clear_file.items():
    s = '    {\'' + key + '\',' + str(val) + 'ULL},'
    print(s)
print('};')

print('const std::unordered_map<int, uint64_t> Board::mask_file{')
for key, val in mask_file.items():
    s = '    {\'' + key + '\',' + str(val) + 'ULL},'
    print(s)
print('};')
