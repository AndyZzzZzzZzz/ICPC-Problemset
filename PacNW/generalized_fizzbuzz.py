#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given positive integers n, a, and b, for all integers i from 1 to n inclusive:
-   if i is divisible by both a and b print FizzBuzz
-   if divisible by a print Fizz
-   if divisible by b print Buzz
-   else print i

Input:
n a and b

Output:
Three integers: the number of times "Fizz" is printed, the number of times "Buzz" is printed, and the number of times "FizzBuzz" is printed

Sample Input:
17 3 5

Sample Output:
4 2 1

https://open.kattis.com/problems/generalizedfizzbuzz
"""

# Read inputs
n, a, b = map(int, input().split())

# variables storing the result
fizzbuzz, fizz, buzz = 0, 0, 0

# Loop through 1 to n inclusive
for i in range(1, n + 1):
    # Swtich statements
    if i % a == 0 and i % b == 0:
        fizzbuzz += 1
    elif i % a == 0:
        # print(f'Fizz - {i}')
        fizz += 1
    elif i % b == 0:
        # print(f'Buzz - {i}')
        buzz += 1

print(f"Fizz: {fizz}, Buzz: {buzz}, FizzBuzz: {fizzbuzz}")
