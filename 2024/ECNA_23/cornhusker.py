corns = list(map(int, input().split()))
n, kwf = map(int, input().split())

total = 0

for i in range(0, 10, 2):
    num = corns[i]
    length = corns[i + 1]
    total += num * length

print(int((total / 5 * n) // kwf))