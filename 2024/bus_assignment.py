#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
A bus travels through n stops labeled from 1 to n. At each stop i, x amount of people get off from the bus and y amount of people gets on. The bus starts out empty at stop 1 and eventually stops & empties at stop n. 
When someone rides the bus they must be seated. The bus has a total capcity of n seats.

Input:
A single integer n.
Each of the next n lines conatins two integers representing x and y,

Output:
A single integer representing the minimum capacity bus needed to run the bus line

Smaple Input:
4
0 3
1 2
2 1
3 0

Sample Output:
4

https://open.kattis.com/problems/busassignment
"""


# read inputs
n = input()

# Solution: this is a greedy problem, we can simple keep track of the most people on bus at any given moment and set 
# that as our bus capcity to ensure everyone is able to ride.

# Keep track of most amount of people on the bus
max_amount = 0

# Keep track of the current status of the bus
current_amount = 0

for stops in range(int(n)):
    leaving, boarding = input().split()
    
    # print(f'Boarding: {boarding} Leaving: {leaving} at stops {stops}')

    current_amount += (int(boarding) - int(leaving))
    max_amount = max(max_amount, current_amount)

print(f'Minimum capacity needed: {max_amount}')

    


