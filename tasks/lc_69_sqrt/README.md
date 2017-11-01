# Task
[Link](https://leetcode.com/problems/3sum/description/)

Implement `int sqrt(int x)`.
Compute and return the square root of x.

# Solutions
* Wrap a set of `n**2` values into an iterator, and use binary search from standard library to find a solution of `n ** 2 == x` in `O(1)` memory and `O(\log n)` time.
* Save `O(\sqrt n)` possible solutions into a container, and use a custom comparator. Assume that value we seek is only used as a first argument in comparison.