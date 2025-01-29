# [446. Arithmetic Slices II - Subsequence (Hard)](https://leetcode.com/problems/arithmetic-slices-ii-subsequence/)

<p>A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.</p>

<p>For example, these are arithmetic sequences:</p>

<pre>1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9</pre>

<p>The following sequence is not arithmetic.</p>

<pre>1, 1, 2, 5, 7</pre>
&nbsp;

<p>A zero-indexed array A consisting of N numbers is given. A <b>subsequence</b> slice of that array is any sequence of integers (P<sub>0</sub>, P<sub>1</sub>, ..., P<sub>k</sub>) such that 0 ≤ P<sub>0</sub> &lt; P<sub>1</sub> &lt; ... &lt; P<sub>k</sub> &lt; N.</p>

<p>A <b>subsequence</b> slice (P<sub>0</sub>, P<sub>1</sub>, ..., P<sub>k</sub>) of array A is called arithmetic if the sequence A[P<sub>0</sub>], A[P<sub>1</sub>], ..., A[P<sub>k-1</sub>], A[P<sub>k</sub>] is arithmetic. In particular, this means that k ≥ 2.</p>

<p>The function should return the number of arithmetic subsequence slices in the array A.</p>

<p>The input contains N integers. Every integer is in the range of -2<sup>31</sup> and 2<sup>31</sup>-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 2<sup>31</sup>-1.</p>
&nbsp;

<p><b>Example:</b></p>

<pre><b>Input:</b> [2, 4, 6, 8, 10]

<b>Output:</b> 7

<b>Explanation:</b>
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]
</pre>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Arithmetic Slices (Medium)](https://leetcode.com/problems/arithmetic-slices/)

## Solution 2. DP Tabulation

Let `dp[i][d]` be the number of weak arithmetic subsequences ending at `A[i]` and with common difference `d`. Here `weak` means the subsequence can be of size `2`.

For each `A[i]`, we loop through all `j < i`:
1. `A[j], A[i]` forms a new sequence.
1. We can append `A[i]` to all the weak arithmetic subsequences ending at `A[j]` with common difference `d`.

```
dp[i][d] = sum(dp[j][d] + 1 | 0 <= j < i && A[i] - A[j] == d)
```

While summing the answer, we can ignore the `1`s corresponding to weak arithmetic subsequences.

```cpp
// OJ: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
// Author: github.com/lzl124631x
// Time Complexity : O(n^2) where n is the length of the input array, due to the nested loops.
// Space Complexity: O(n^2)  in the worst case for storing counts in the hash maps

// Ref: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/solution/
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<long long, int>> dp(n);
        int totalCount = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long long diff = static_cast<long long>(nums[i]) - nums[j];
                
                // Get the count of sequences ending at index j with the same difference
                int countAtJ = dp[j][diff];
                
                // Add the count to the total count of arithmetic slices
                totalCount += countAtJ;
                
                // Update the count of sequences ending at index i with this difference
                dp[i][diff] += countAtJ + 1; // +1 for the new sequence formed by nums[j] and nums[i]
            }
        }

        return totalCount;
    }
};

```


## Solution 1. DP Memoization

```cpp
// OJ: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N^2)

class Solution {
private:
    vector<unordered_map<long long, int>> dp;

    int dfs(int i, long long diff, const vector<int>& nums) {
        if (dp[i].count(diff)) return dp[i][diff];

        int count = 0;
        for (int j = 0; j < i; ++j) {
            if ((long long)nums[i] - nums[j] == diff) {
                count += dfs(j, diff, nums) + 1; // Add subsequences ending at j and the new pair (j, i)
            }
        }

        return dp[i][diff] = count;
    }

public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;

        dp.resize(n);
        int totalCount = 0;

        // Iterate over all pairs (i, j) to calculate subsequences
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long long diff = (long long)nums[i] - nums[j];
                totalCount += dfs(j, diff, nums); // Add all subsequences ending at j with difference `diff`
            }
        }

        return totalCount;
    }
};

```
