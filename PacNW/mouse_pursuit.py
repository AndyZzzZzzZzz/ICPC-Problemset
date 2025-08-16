#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
An event consists of pursuing a mouse. If the mouse is caught, you get cheese and glory, otherwise you loss cheese and glory. Given recent events,
calculate how much cheese and glory you earn in the last k seconds.

Input:
First line consist a single integer n -> number of events

The next n lines comes in one of two forms:
CAUGHT s c g -> A mouse caught exactly s seconds ago with c cheese and g glory
MISS  s c g -> A mouse missed exactly s seconds ago with c cheese and g glory

The last line is a single integer k (seconds)

Output:
Format: ! k where k represents the length of longest increasing subsequence

Sample Input:
3
CAUGHT 1 6 5
MISS 4 1 2
CAUGHT 8 0 3
5

Sample Output:
5 3

https://open.kattis.com/problems/mousepursuit
"""

# read input
n = int(input())

final_cheese = 0
final_glory = 0
events = []

# read and store all events 
for i in range(n):
    event, sec, cheese, glory = input().split()
    
    # If caught, store positive values else negative
    if event == "CAUGHT":
        events.append((int(sec), int(cheese), int(glory)))
    else:
        events.append((int(sec), -int(cheese), -int(glory)))

# read seconds
sec = int(input())

# calculate result
for e in events:
    if sec > e[0]:
        final_cheese += e[1]
        final_glory += e[2]

print(f'{final_cheese} {final_glory}')
