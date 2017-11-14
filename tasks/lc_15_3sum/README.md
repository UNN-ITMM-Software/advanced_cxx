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
1. Sort the array, consider all pairs (one iterator is set to the begin and the second iterator is set to the end), find the third element for triplet with binary_search between iterators. If iterator is moved to the repeated value, skip it. O(n^2 * log n)
