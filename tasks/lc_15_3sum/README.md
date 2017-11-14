# Task
[Link](https://leetcode.com/problems/sqrtx/description/)

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

```
For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

# Solutions
* Burte-force through pairs of values, find a third one with binary search. Asymptote is `O(n^2 \log^2 n)` due to deduplicating returns by storing them into a `std::set`. Input sequence is left uncompressed.

