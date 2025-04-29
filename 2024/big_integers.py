#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given inatgers in base 62, with 0 through 9 representing digit values 0 - 9, lowercase letters a - z representing digit values 10 - 35, and
uppercase letters A - Z representing digit values 36 - 61. Example Aa = 36 * 62 + 10

Given two strings representing two distinct base 62 integers and determine if the numerically smaller value is the lexicographically smaller ones.

Input:
An integer n representing number of test cases followed by 2 * n strings with each pair being a test case

Output:
output a single line with YES if the lexicographically smaller string represents the smaller integer in base 62, and output a single line with NO otherwise

Sample Input:
2
icpc
ICPC
a
bc

Sample Output:
NO
YES

https://open.kattis.com/problems/bigintegers
"""

import sys

input = sys.stdin.readline

# ─────────────────────────────────────────────────────────────
# build ASCII → base-62 value table (size 128 is enough)
val = [-1] * 128
for i in range(10):
    val[ord('0') + i] = i                # 0-9  → 0-9
for i in range(26):
    val[ord('a') + i] = 10 + i           # a-z → 10-35
    val[ord('A') + i] = 36 + i           # A-Z → 36-61
# ─────────────────────────────────────────────────────────────

def num_smaller(s1: str, s2: str) -> bool:
    """Return True if s1 < s2 numerically in base-62."""
    # 1) different lengths → shorter one is smaller
    if len(s1) != len(s2):
        return len(s1) < len(s2)
    # 2) same length → compare first differing digit
    for c1, c2 in zip(s1, s2):
        if c1 != c2:
            return val[ord(c1)] < val[ord(c2)]
    # never equal per problem statement, but return False for completeness
    return False

t = int(input())
out_lines = []

for _ in range(t):
    a = input().strip()
    b = input().strip()

    lexi_smaller_first = a < b           # lexicographic order
    num_smaller_first  = num_smaller(a, b)

    # If the string that is lexicographically first is also numerically first
    out_lines.append("YES" if lexi_smaller_first == num_smaller_first else "NO")

sys.stdout.write("\n".join(out_lines))

"""
Note: the problem require highly optimized approach in Python due to time constraints 

Numeric ordering comparison:
Naive approach: construct the number -> takes O(len)
Optimized:      1. shorter length -> smaller 2. same length -> compare first position differ


Exponentiation:
Naive approach: Actually building the value by calling 62 ** power
Optimized:      Ignore exponentiation

Digit -> value look up table's optimization is questionalble. I doubt it makes a difference in any case
"""
