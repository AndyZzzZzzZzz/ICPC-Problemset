
n, q = map(int, input().split())

chairs = list(range(n))

# simulation loop to shift people
def simulation(op: str, change: int):
    if op == '+':
        pass

res = []
# query loop
for i in range(q):
    comm = list(input().split())

    if comm[0] == '?':
        idx = int(comm[1]) - 1           
        player = chairs[idx]
        if player == -1:
            res.append('-1')
        else:
            res.append(f'{player + 1}')
    elif comm[0] == '+':
        simulation('+', int(comm[1]))
    elif comm[0] == '*':
        simulation('*', int(comm[1]))

print('\n'.join(res))
