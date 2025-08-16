import sys

n, *arr = list(map(int, input().split()))


largest  = [0]*n
smallest = [0]*n

curr = arr[0]
for i in range(n):
    curr = max(curr, arr[i])
    largest[i] = curr

curr = arr[-1]
for i in range(n-1, -1, -1):
    curr = min(curr, arr[i])
    smallest[i] = curr

count = 0
res   = []
for i, v in enumerate(arr):
    left_ok  = (i == 0) or (largest[i-1] <= v)
    right_ok = (i == n-1) or (smallest[i+1] > v)
    if left_ok and right_ok:
        count += 1
        if count <= 100:
            res.append(str(v))


res.insert(0, str(count))
print(' '.join(res))
