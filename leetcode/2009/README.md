# [2009. Minimum Number of Operations to Make Array Continuous (Hard)](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous)

<p>You are given an integer array <code>nums</code>. In one operation, you can replace <strong>any</strong> element in <code>nums</code> with <strong>any</strong> integer.</p>

<p><code>nums</code> is considered <strong>continuous</strong> if both of the following conditions are fulfilled:</p>

<ul>
	<li>All elements in <code>nums</code> are <strong>unique</strong>.</li>
	<li>The difference between the <strong>maximum</strong> element and the <strong>minimum</strong> element in <code>nums</code> equals <code>nums.length - 1</code>.</li>
</ul>

<p>For example, <code>nums = [4, 2, 5, 3]</code> is <strong>continuous</strong>, but <code>nums = [1, 2, 3, 5, 6]</code> is <strong>not continuous</strong>.</p>

<p>Return <em>the <strong>minimum</strong> number of operations to make </em><code>nums</code><em> </em><strong><em>continuous</em></strong>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [4,2,5,3]
<strong>Output:</strong> 0
<strong>Explanation:</strong>&nbsp;nums is already continuous.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,2,3,5,6]
<strong>Output:</strong> 1
<strong>Explanation:</strong>&nbsp;One possible solution is to change the last element to 4.
The resulting array is [1,2,3,5,4], which is continuous.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [1,10,100,1000]
<strong>Output:</strong> 3
<strong>Explanation:</strong>&nbsp;One possible solution is to:
- Change the second element to 2.
- Change the third element to 3.
- Change the fourth element to 4.
The resulting array is [1,2,3,4], which is continuous.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>9</sup></code></li>
</ul>


**Companies**:
[Amazon](https://leetcode.com/company/amazon), [Apple](https://leetcode.com/company/apple), [Uber](https://leetcode.com/company/uber)

**Related Topics**:  
[Array](https://leetcode.com/tag/array), [Binary Search](https://leetcode.com/tag/binary-search)

**Similar Questions**:
* [Longest Repeating Character Replacement (Medium)](https://leetcode.com/problems/longest-repeating-character-replacement)
* [Continuous Subarray Sum (Medium)](https://leetcode.com/problems/continuous-subarray-sum)
* [Moving Stones Until Consecutive II (Medium)](https://leetcode.com/problems/moving-stones-until-consecutive-ii)
* [Minimum One Bit Operations to Make Integers Zero (Hard)](https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero)
* [Minimum Adjacent Swaps for K Consecutive Ones (Hard)](https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones)

**Hints**:
* Sort the array.
* For every index do a binary search to get the possible right end of the window and calculate the possible answer.



## Solution 1. Sliding Window

```cpp
// Instead of   A.erase(unique(A.begin(), A.end()), A.end()); // Remove duplicates

int idx = 0;
for (int j = 1; j < A.size(); ++j) {
    if (A[j] != A[idx]) {
        A[++idx] = A[j];
    }
}
A.resize(idx + 1); // Trim the vector to contain only unique elements
```

``` cpp
// Time: O(N log N)
// Space: O(1) (excluding input and output space)

/*
    Idea:
    - We want to make the array contain all integers from 1 to N (size of array) with no duplicates.
    - First, sort the array and remove duplicates since duplicates are useless for a strictly increasing sequence.
    - Use a sliding window (i, j) to find the largest window where all elements can fit in a continuous segment of size N.
    - For a valid window, we need:
        A[j] - A[i] < N  => that means this subarray could be part of a continuous array of size N.
    - For each valid window, the number of elements we can keep is (j - i + 1).
    - So, the answer is: N - max(j - i + 1)
*/

class Solution {
public:
    int minOperations(vector<int>& A) {
        int N = A.size(), i = 0, maxWindow = 0;

        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end()); // Remove duplicates

        for (int j = 0; j < A.size(); ++j) {
            // Slide i forward if the window size exceeds N
            while (A[j] - A[i] >= N) ++i;

            // maxWindow stores the longest valid subarray (no operations needed for it)
            maxWindow = max(maxWindow, j - i + 1);
        }

        return N - maxWindow; // Operations = Total elements - kept elements
    }
};
```

Use Non-shrinkable Sliding Window Template:

```cpp
// We can simply change the while to if to get non shrinkable approach
// But we generally don't use ans in the 2nd approach

class Solution {
public:
    int minOperations(vector<int>& A) {
        int N = A.size(), i = 0, j;
        sort(begin(A), end(A));
        A.erase(unique(begin(A), end(A)), end(A)); // only keep unique elements

        for (j=0; j < A.size(); ++j) {
            if (A[i] + N <= A[j]) ++i;
        }
        return N - (j - i);   // as j is already at n. i,e j is j+1
    }
};
```

## Discuss

https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/discuss/1470857/C%2B%2B-Sliding-Window
