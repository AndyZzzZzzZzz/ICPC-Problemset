#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given two binary numbers a and b, what are the minimal powers of two 'coins' you need to carry in order to be able to pay all values between a - b (inclusive).

Input:
Two binary  numbers with no leading zeros

Output:
A single integer k, the minimum number of coins you need to bring

Sample Input:
10101
101010

Sample Output:
6


https://open.kattis.com/problems/exactchange3
"""

# Bit manipulation problem

import sys

# read input
a = sys.stdin.readline().strip()
b = sys.stdin.readline().strip()

# build the intger representationin base 10
num_a = int(a, 2)
num_b = int(b, 2)

# case one: these two numbers are the same
if num_a == num_b:
    final = num_a
else:
    # check the highest bit position where these two numbers diffr
    x = num_a ^ num_b
    diff_pos = x.bit_length() - 1 # index of that most-significant differing bit

    # num_a | nums_b keeps all ones in both number
    # 1 << diff_pos creates a bit mask
    #   Example: 1 << 6 = 0b1000000 and (1<< 6) - 1 = 0b0111111
    # Combined: keep all 1s from either a or b, turn on all bits that could have flipped in any number between a and b

    # Key insights: All bits below k (i.e., bits 0 through k−1) could change arbitrarily when going from a to b
    # where k is the highest differ position 
    final = (num_a | num_b) | ((1 << diff_pos) - 1)

count = final.bit_count()
print(count)


