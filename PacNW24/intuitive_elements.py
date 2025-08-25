#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given a string and a proposed abbreviation, determine if it is intuitive. Intuitive means that every letter that appears in the abbreviation
appears in the original string. It is acceptable for a letter to appear more times in the abbreviation than in the original string or in different order.

Input:
The first line of input contains a single integer t indicating the number of output
Each test case is represented on two lines.
The first represents original string and the second represent the abbreviation

Output:
Three integers: the number of times "Fizz" is printed, the number of times "Buzz" is printed, and the number of times "FizzBuzz" is printed

Sample Input:
4
magnesium
mg
silver
ag
aabb
bbb
aabb
ba

Sample Output:
YES
NO
YES
YES

https://open.kattis.com/problems/intuitiveelements

"""

# read input
n = int(input())

result = []

for i in range(n):
    # get the string and its abbreviation
    string = input().strip()
    abbr = input().strip()

    # use a set for more efficient check
    char = set([])
    for c in string:
        char.add(c)

    valid = True # flag to check whether abbr is valid
    for c in abbr:
        if c not in char:
            valid = False
            # early exit
            break
    if valid:
        result.append("YES")
    else:
        result.append("NO")

print('\n'.join(result))