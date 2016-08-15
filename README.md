# Data-structures

### RMQ (Range Minimum Query): Online minimum-queries on subarrays of given array (of size n)

Method with sqrt-decomposition: O(sqrt(n)) time queries with O(n) precomputing

Method with sparse tables: O(log(n)) time queries with O(nlog(n)) precomputing and O(nlog(n)) required space

### LCA (Lowest commun ancestor): Online LCA-queries on pairs of vertices of given tree (of size n), similar to RMQ, see the topcoder tutorial

Method with sqrt-decomposition: O(sqrt(n)) time queries with O(n) precomputing

Method with sparse tables: O(log(n)) time queries with O(nlog(n)) precomputing and O(nlog(n)) required space

### Segment trees

Various types of online updates and queries on arrays in logarithmic time, with O(log(n)) precomputing and space required.
Queries of min,sum,number of distinc elements... Range/Point queries and updates, sometimes the lazy propagation trick is needed to get what you want !

### BIT (Bit Indexed Tree or Fentwick Tree)

A nice improvement of Segment Trees using clever bit tricks for very fast implementation. But sometimes it won't be enough : segment trees can do more !

### Treap (Cartesian Tree, Tree-Heap)

Allying the structures of Binary Search Trees and Heaps, and using some randomness, this wonderful (and quite hard to implement live!) structure is the ultimate tool for logarithmic queries on arrays, such as the famous inversion update query. It is also said that it supports duplication and a lot more... See e-maxx.ru/algo

### Book for SWERC selections in Telecom ParisTech, 2016

- Dijkstra
- The famous union-find of bmerry (see on data structure gym page of codeforces.com)
- Largest rectangle in histogram (linear time)
- Largest palindrome in string
- KMP (find substring in string in linear time)
- Matching
