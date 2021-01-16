stacks = []

with open('vmapstack.txt', 'r') as f:
    for line in f.readlines():
        tmps = line.split(' ')
        stacks.append(tmps[-1])

print(set(stacks))