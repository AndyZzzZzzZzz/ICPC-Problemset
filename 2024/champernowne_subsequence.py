#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
The kth Champernowne word is obtained by writing down the first positive integers and concatenating them together.

It can be proven that, for any finite string of digits, there exists some integer k such that the finite string of digts will appear
as a subsequence in the kth Champernowne word.

Given a string of digits, compute the smallest integer k such that the given string of digits is a subsequence of the kth Champernowne word.


Input:
The first line of input contains a single integer n: the length of the string of digits
The second line of inputs contains a string of n digits

Output:
output a integer k, the minimum integer such that the given string is a subsequence of the kth Champernowne word.

Sample Input:
2
90


Sample Output:
10

https://open.kattis.com/problems/champernownesubsequence
"""

# Solution: This is an interesting problem. Since we are checking for subsequence, we don't actually have to construct the string and trying to delete characters.
#           Oberserve that we can simple check whether a given digit in the string s appears in the next number we add to the Champernowne:
#           Example: 91 
#           First Target:9 -> 12345678 (9)
#           Next Target: 10 -> the next number we add (10) contains this target -> return as answer

# read input
n = int(input())
string = input()

# start the Champernowne chain
start = 1
index = 0

while index < n:

    # keep building if we don't see this characer
    for character in str(start):
        # Found a match, increase counter
        if index < n and character == string[index]:
            index += 1

    start += 1

print(start - 1)

