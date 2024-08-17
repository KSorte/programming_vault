## Notes
With hindsight, Two Pointers, Sliding Window and Binary Search were most difficult to solve.
However, trees, graphs and linked list problems all rely on a finite class of tricks.

Slow fast pointer technique in linked list: Leetcode 141, 143(I haven't used it, one can here), and Leetcode 19 use two pointers
fast and slow to achieve their ends. A classic technique.

Problem 22 Generate Parentheses needs be revisited during Backtracking, Decision Trees, Recursion and Tree Search.
This problem even though using a stack is more significantly belonging to one of the above groups.

Leetcode 128 - Longest Consecutive Sequence : Was a hard crack, the trick is very nuanced and may not strike immediately.

Leetcode 853 : Did not need the usage of stacks. The trick did not strike organically.

Leetcode 84 - Did not need stacks.

Leetcode 543 Diameter of Binary Tree and Leetcode 110 Balanced Binary Tree used DFS with recursion. Very peculiar technique.

Leetcode 33 Search in Rotated Sorted array - From Blind 75. Took a long time to crack.

Leetcode 424 Longest Repeating Character Replacement: Most important from the sliding window section;
Count of the most occuring letter after moving the left pointer need not be recalculated.
It is recalculated currently by iterating over the map.

Leetcode 100, 104, 110, 226, 543 and 572 - Easy leetcodes from the `Trees` section. An excellent set of problems for understanding
binary tree traversal and most importantly RECURSION. Each of these problems hinge on a single trick. Some form of bfs or dfs
The latter gives a rich understanding of recursion. Very very important set of problems.

Leetcode 235 Lowest Common Ancestor in BST - the key thing to understand is that the BST is valid. This helps in understanding that
nullptr errors wont occur.

Leetcode 200 Number of Islands is a very important problem asked in many coding rounds.
It is solved with both DFS and BFS. Must read for understanding these two searches properly.

Leetcode 208 Implement Trie Prefix Tree : This is a good problem for application of unique pointers as against
raw pointers. Methods such as `make_unique()` to create new instance of unique pointer and `get()` to get raw pointers from unique ptrs are used in this solution.
No usage of pointers lead to problems with the hashmaps since they copy the class elements and lead to
heap-use-after-free error.
This is a problem worth studying to understand when to use and not use pointers.

Leetcode 211 Design. Add and Search Words Data Structure. This is part of the Blind 75 list and is an extremely important extension of the
Leetcode 208. It employs a very canny implementation of DFS. It is worth trying to dry run the algorithm over and over to understand how it works. KEY: Understand the problem first.

Leetcode 143 Reorder List: Important learning - When dealing with pointers use while loops using nullptr conditions rather than
for loops which can cause nullptr errors.

Leetcode 133 Clone Graph: Important learning - Do not assume that the graph is a tree. This problem the graph was bidirectional.
Which meant that in a BFS algorithm even if you have visited a neighbor before, the current node can still form a connection.
Trick: BFS with a map pointing from old node to new.

### Backtracking
The difference between DFS and backtracking is that in the former, you do not unmark the cells visited after the branch
is done. In backtracking, when you hit the base case and the recursion starts unrolling, you essentially unmark the states as you
go up.
These problems usually need to same resource in multiple branches of the search, needing repeated visits.
Eg. permutations, combinations, subsets, the generate parentheses problem.

Leetcode 78 Subsets, Leetcode 39 Combination Sum: Was a tough introduction to backtracking. Solution not intuitive.
Use recursive DFS for searching all possible subsets. "children" of a node are actually decisions
about whether to add a node to a subset being constructed.

Leetcode 22 Generate Parentheses can also be solved with backtracking.

Note the DFS function where the efficiency depends on whether you are passing the current combination or subset by reference or
by value to the DFS function. The former is also much more efficient. Both algos are slightly different.

## Bit Manipulation
Leetcode 136 Single Number and Leetcode 338 Counting Bits needed some deep thinking and pattern searching.
136 uses XOR.

## Advanced Graphs
Leetcode 743 Network Delay Time -  Solve using Dijkstra's algorithm.