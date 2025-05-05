#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given two sets of cards, check if we can find a pair of two cards that is the same and is in different rows and different columns.

Input:
First line consist a single integer n -> number of test cases

Each test cases contain two lines each with 5 integers between 1 to 9.

Output:
For each test case, if there exists a pair of cards with the same number in different rows and different columns, output YES. Otherwise, output NO.

Sample Input:
3
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
2 6 7 8 9
5 5 5 5 5
5 5 5 5 5


Sample Output:
NO
YES
YES


https://open.kattis.com/problems/ruffians
"""

n = int(input())

for cases in range(n):
    row1 = list(i for i in input().split())
    row2 = list(i for i in input().split())

    found = False
    # Fixed bounds
    for i in range(5):
        for j in range(5):
            if row1[i] == row2[j] and i != j:
                found = True
                break
        if found:
            break
    if found:
        print("YES")
    else:
        print("NO")

