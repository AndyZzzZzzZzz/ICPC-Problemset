#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
There are n bags of trash each with a specific weight. You can take one or two bags of trash per trip, and can carry a maximum total 
of m weight of trash in a single trip. What is the minimum nuber of trips you need to take to take out all the trash.

Input:
two integers n - number of bags of trash and m - maximum weight of trash.

n integers each representing the weight of each bag of trash

Output:
Minimum number of trips you need to make to take out all trash

Sample Input:
4 1000
100 900 200 900


Sample Output:
3

https://open.kattis.com/problems/takingoutthetrash
"""

# read input
n, m = map(int, input().split())

trash = [int(i) for i in input().split()]

# This is a greedy problm. The most optimal approach is to sort the array to try taking about max(trash) + min(trash) in 
# every single trip. This guarantees that we minimize the wasted space at hand

trash.sort()

res = 0
# greedy loop with two pointer
left = 0
right = len(trash) - 1

while left <= right:
    # Case 1: we can take out both bags of trash
    if trash[left] + trash[right] <= m:
        left += 1
        right -= 1
        res += 1
    # Case 2: we cannot take both bags. (This means that the maximum bag might be taken by itself)
    else:
        right -= 1
        res += 1

print(res)


