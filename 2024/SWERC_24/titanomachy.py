
import sys

n, m = map(int, sys.stdin.readline().split())

initial = list(map(int, sys.stdin.readline().split()))
result = []
offset = 0


def max_sub(arr, offset):
    best = curr = 0
    for v in arr:
        v += offset
        curr = max(v, curr + v)
        best = max(best, curr)
    
    return best


for events in range(m):
    e = [i for i in input().split()]

    if e[0] == 'STRENGTH':
        
        offset += int(e[1])      
    
    else:
        r = int(e[1]) - 1                
        l = int(e[2]) - 1
        result.append(
            max_sub(initial[r:l+1], offset)
        )


print('\n'.join(map(str, result)))




        