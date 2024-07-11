

nums = [1,2,3,4,5,6,7,8]
letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']

letter_to_num = {}
i = 0

for num in nums:
    for letter in letters:
        letter_to_num[f"{letter}{num}"] = 1 << i
        i += 1 


num_to_letter = dict(zip(letter_to_num.values(), letter_to_num.keys()))

for key, val in letter_to_num.items():
    p = "{\"" + str(key) + "\", " + str(val) + "},"
    print(p)
for key, val in num_to_letter.items():
    p = "{" + str(key) + ", \"" + str(val) + "\"},"
    print(p)


print(letter_to_num['A8'], 1 << 56)