#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given a hidden permutation (array of integers), you need to reconstruct its structure using queries. The goal is to determine the length
of longest increasing subsequence. The queries are the in form of ? l r, where l and r represent positions within the array. The judge will
then tell you the number of inversions inside this range. 

Inversions means that for two indices i, j: i < j but arr[i] > arr[j]
Example: p = [3, 1, 4, 2] all inversions: (3, 1) (3, 2) (4, 2)

Rule:
1.  Permutation is fixed at the start
2.  Sending invalid iinput results in -1 and the program should terminates
3.  Must flush the output after each query


Output:
Format: ! k where k represents the length of longest increasing subsequence

Example: p = [3, 1, 4, 2] 
? 1 4 -> output: 3
? 1 2 -> output: 1
? 2 4 -> output: 1
? 1 3 -> output: 1

https://open.kattis.com/problems/homeworkhelp

Feel free to use the testing tool provided testing_tools(homeworkhelp).py
"""

# Attempting to build a Fenwick Tree in Python to help with the decoding process O(n^2) -> O(nlogn)
# Purpose: prefix sums and k-th order statistics
class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n+ 2)
    
    def add(self, idx, delta):
        while idx <= self.n:
            self.bit[idx] += delta
            idx += idx & -idx
    
    def sum(self, idx):
        res = 0
        while idx > 0:
            res += self.bit[idx]
            idx -= idx & -idx
        return res
    
    # Currently do not undersand this part well (at the time of writing this solution)
    def kth(self, k):
        idx = 0
        mask = 1 << 20
        while mask:
            nxt = idx | mask
            if nxt <= self.n and self.bit[nxt] < k:
                k -= self.bit[nxt]
                idx = nxt
            mask >>= 1
        return idx + 1
    

# Note: HARD!

# read input 
n = int(input())

# send n queries to the judge from n to 1 and store # of inverses in all suffix subarray
sufInv = (n + 2) * [0]      # we store elemets from 0 to n + 1, but we don't use the index 0
for i in range(n, 0, -1):
    print(f'? {i} {n}')
    count = int(input())
    if count < 0:
        raise RuntimeError # judge sends back -1 upon invalid request
    sufInv[i] = count

# Build the Lehmer digits
c = (n + 1) * [0]
for i in range(1, n + 1, 1):
    c[i] = sufInv[i] - sufInv[i + 1]

# Decode the permutation
ftree = Fenwick(n)
# Build the Fenwick tree
for i in range(1, n + 1):
    ftree.add(i, 1)

permutation = [0] * n
for i in range(1, n + 1):
    # essentally we are finding the kth smallest element to c[i] + 1
    position = ftree.kth(c[i] + 1)
    permutation[i - 1] = position
    # We are marking this element as used to look for next answer
    ftree.add(position , -1)

# Implement the patience sorting to find longest increasing subsequence
import bisect
piles = []
for x in permutation:
    # First position in the piles array we can put x without breaking the sorted order
    # First element that >= x 
    idx = bisect.bisect_left(piles, x)
    # Start anew pile if we cant find any
    if idx == len(piles):
         piles.append(x)
    # If we found a valid posiiton, put it on top of the pile 
    else:
        piles[idx] = x

LLIS = len(piles)
print(f'! {LLIS}', flush=True)
