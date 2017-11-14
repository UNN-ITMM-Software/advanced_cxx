# Task
[Link](https://leetcode.com/problems/3sum/description/)

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
* Burte-force through pairs of values, find a third one with binary search. Asymptote is `O(n^2 \log^2 n)` due to deduplicating returns by storing them into a `std::set`. Input sequence is left uncompressed. [Link](https://github.com/UNN-VMK-Software/advancedc/blob/master/tasks/lc_15_3sum/banin.cpp)  
* Sort the array, consider all pairs (one iterator is set to the begin and the second iterator is set to the end), find the third element for triplet with binary_search between iterators. If iterator is moved to the repeated value, skip it. `O(n^2 * log n)` [Link](https://github.com/UNN-VMK-Software/advancedc/blob/master/tasks/lc_15_3sum/gritsenko.cpp)
* `O(n^2)` [Link](https://github.com/UNN-VMK-Software/advancedc/blob/master/tasks/lc_15_3sum/barinova.cpp)
  1. Sort input vector.
  2. Obtain 2 vectors from input one: first contains sorted unique elements, second - counts of corresponding elements in input vector.
  3. Additional vector 'max_corresp_candidat_idx' for storage min checked third triple element index for a second element in triplet (initialized with nums.size() - 1).
  4. Check triplets of elements with 3 indices:
  idx[0] is increasing from min element index to max negative index,
  idx[1] is increasing from idx[0] and stops increasing when triplets is found or when idx[1] == idx[2],
  idx[2] is decreasing from max_corresp_candidat_idx[idx[1]] and stops decreasing when triples is found or when idx[1] == idx[2].

