stock_fish = {}
me = {}
with open("stockfish", 'r') as f1, open("me", 'r') as f2:
    for line in f1:
        # Strip any surrounding whitespace (like newlines)
        line = line.strip()
        
        # Split the line at the colon to separate key and value
        if ':' in line:
            key, value = line.split(':')
            # Remove extra spaces and convert the value to an integer
            stock_fish[key.strip()] = int(value.strip())
    for line in f2:
        line =line.strip()

        if ':' in line:
            key, value = line.split(':')
            me[key.strip()] = int(value.strip())


def find_differences(dict1, dict2):
    # Initialize an empty dictionary to store differences
    differences = {}

    # Get the union of all keys in both dictionaries
    all_keys = set(dict1.keys()).union(set(dict2.keys()))

    # Loop through each key and compare the values in both dictionaries
    for key in all_keys:
        if dict1.get(key) != dict2.get(key):
            differences[key] = (dict1.get(key), dict2.get(key))

    return differences


print(find_differences(stock_fish, me))