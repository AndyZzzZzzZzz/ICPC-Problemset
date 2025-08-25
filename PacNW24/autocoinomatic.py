#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
Given a set of coins and query of events, determine the fewest number of coins needed for each events. If the query is Q, this is an event
that need calculation for. If the query is X, this is indicating that a type of coin is banned for all future event.

Example:
Q 23 - represent an event that needs 23 value to attend
X 5  - represent that all future event cannot use coin with face value 5

Input:
First line:     n (number of coints initially), m (number of queries)
Second line:    n integers representing the types of coins we hae initially
Next m lines:   queries that has either type Q or type X

Output:
For each Q type event, outputs the number of minimum coin we need to attend the event. If not possible, print -1.

Sample Input:
4 7
1 2 5 10
Q 23
X 1
Q 23
X 5
Q 23
X 10
Q 22


Sample Output:
4
6
-1
11


https://open.kattis.com/problems/autocoinomatic
"""

# Note: Greedy (selecting the largest coin) won't work here beacuse take a look at this case:
#       Coints: 3,5  Target 9 -> picking 5 is not viable here
#       This is related to the classic coin change problem Leetcode 322


def top_down_tle():
    # Top down approach: recursive + memoization (Brute force -> TLE)
    def dfs(coins: set, targ: int, memo: dict) -> int:

        # Base case: reaching zero means that the current path successfully constructed target
        if targ == 0: 
            return 0 
        # Check if we've seen this paths before
        if targ in memo:
            return memo[targ]

        # For invalid path, return None
        result = None
        # Main loop to apply each coin on the current target
        for c in coins:
            # Check that the amount is valid and do not exceed target
            if targ - c >= 0:
                # Temp is the intermediate result returned by this path
                temp = dfs(coins, targ - c, memo)
                if temp is not None:
                    if result is None:
                        result = 1 + temp
                    else:
                        result = min(result, 1 + temp)
        
        memo[targ] = result
        return result

    # read input
    n, m = input().split()

    # read coins
    coins = set(map(int, input().split()))

    # main process loop
    for i in range(int(m)):
        type, value = input().split()
        
        if type == 'X':
            coins.remove(int(value))
        else:
            min_result = dfs(coins, int(value), {})
            # check if we can construct the target
            if min_result is None:
                print(-1)
            else:
                print(min_result)


# Second try: reverse the problem with bottom up tabulation
# 1. Read n, m.
n, m = map(int, input().split())

# 2. Read the n distinct coin denominations into a set `initial`.
coins = set(map(int, input().split()))

# 3. Read the m events (type, value) into a vector `E[0..m-1]`.
events = []
for i in range(m):
    type, value = input().split()
    events.append((type, int(value)))

# 4. Scan `E` and mark which denominations are ever “X’ed.”  Let
#     S_final = initial \ { all values ever removed }.
# 5. Let V = max{ v | (type=='Q', v) in E }.
cap_value = 0
queries = 0
removed = set()
for e in events:
    if e[0] == 'X':
        removed.add(e[1])
    if e[0] == 'Q':
        cap_value = max(cap_value, e[1])
        queries += 1
final_coins = coins - removed

# 6. Build dp[0..V] ← INF, dp[0] = 0.
dp = (cap_value + 1) * [1e9]
dp[0] = 0

# 7. For each coin d in S_final:
#    for (t = d; t ≤ V; ++t)
#       dp[t] = min(dp[t], dp[t − d] + 1);
# This is to use all coin to build all target
for coin in final_coins:
    for temp in range(coin, cap_value + 1):
        dp[temp] = min(dp[temp], dp[temp - coin] + 1)

# 8. Prepare an answers array A, and set a running index qi = (#queries−1).
ans = queries * [0]
query = queries - 1

# dynamically compute answers
for i in range(m - 1, -1 , -1):
    if events[i][0] == 'Q':
        # calculate value with current dp table
        ans[query] = dp[events[i][1]] if dp[events[i][1]] < 1e9 else -1
        query -= 1
    else:
        # we need to add back the coin we removed 
        # update all value in the dp table that are larger than this coin because the coin could be 
        # a potential contributor
        for value in range(events[i][1], cap_value + 1):
            dp[value] = min(dp[value], dp[value - events[i][1]] + 1)

for a in ans:
    print(a)

# Note: This seemed to be the most optimized approach but cannot pass no matter what lol. C++ equivalent version passed.



