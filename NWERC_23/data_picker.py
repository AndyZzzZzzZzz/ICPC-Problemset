from itertools import combinations

grid = [input().strip() for _ in range(7)]

d, h = map(int, input().split())

gobal_max = 0
for comb in combinations(d, 7):
    print(comb)


