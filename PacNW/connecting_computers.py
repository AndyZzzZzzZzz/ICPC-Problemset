#!/Library/Frameworks/Python.framework/Versions/3.11/bin/python3

"""
Problem:
There are n computers that need to be connected together to form a fully connected network - any computer can reach any other by following a series of connections.

There are m bidirectional connections (edges), each sing one of k types of cables.

Each edge tells you: computer A, computer B, and cable type.

Constraints:
1. Every pair of computers can have at most one direct connection
2. Using all available cables, the graph is already connected
3. No two cycles in the graph (closed loops) can share more than one computer

Questions:
1. What is the minimum number of cable types needed to use to make sure all computers stay connected?
2. How many different subsets of cable types exist such that using only those cable types still results in a fult connected network.

Input:
First line contains 3 integers: n (number of computers), m (number of connections), and k (number of cable types)
Next line contains k strings represeting cable types
Next m lines describes the connections between computers

Output:
Output two lines, each containing a single integer. The first line should contain the minimum number of cable types the tech team needs connect all the computers. The second line should contain the number of subsets of cable types such that only installing those types would connect all of the computers.

Sample Input:
6 7 4
CAT5 RS232 MIDI USBC
1 2 CAT5
2 3 MIDI
3 4 MIDI
2 4 CAT5
4 5 MIDI
5 6 MIDI
4 6 RS232


Sample Output:
2
4


https://open.kattis.com/problems/connectingcomputers
"""

from itertools import combinations
from collections import defaultdict

# Disjoint Union Find
class DSU:
    """Disjoint-Set with path compression and union-by-size"""
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.size = [1] * n
        self.cc = n                     # connected components counter
    
    def find(self, x: int) -> int:
        while self.parent[x] != x:
            # Do path compression, set the current node's parent to its parent's parent
            self.parent[x] = self.parent[self.parent[x]]
