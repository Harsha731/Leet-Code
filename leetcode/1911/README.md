 # [1911. Maximum Alternating Subsequence Sum (Medium)](https://leetcode.com/problems/maximum-alternating-subsequence-sum/)

<p>The <strong>alternating sum</strong> of a <strong>0-indexed</strong> array is defined as the <strong>sum</strong> of the elements at <strong>even</strong> indices <strong>minus</strong> the <strong>sum</strong> of the elements at <strong>odd</strong> indices.</p>

<ul>
	<li>For example, the alternating sum of <code>[4,2,5,3]</code> is <code>(4 + 5) - (2 + 3) = 4</code>.</li>
</ul>

<p>Given an array <code>nums</code>, return <em>the <strong>maximum alternating sum</strong> of any subsequence of </em><code>nums</code><em> (after <strong>reindexing</strong> the elements of the subsequence)</em>.</p>

<ul>
</ul>

<p>A <strong>subsequence</strong> of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, <code>[2,7,4]</code> is a subsequence of <code>[4,<u>2</u>,3,<u>7</u>,2,1,<u>4</u>]</code> (the underlined elements), while <code>[2,4,2]</code> is not.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> nums = [<u>4</u>,<u>2</u>,<u>5</u>,3]
<strong>Output:</strong> 7
<strong>Explanation:</strong> It is optimal to choose the subsequence [4,2,5] with alternating sum (4 + 5) - 2 = 7.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> nums = [5,6,7,<u>8</u>]
<strong>Output:</strong> 8
<strong>Explanation:</strong> It is optimal to choose the subsequence [8] with alternating sum 8.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> nums = [<u>6</u>,2,<u>1</u>,2,4,<u>5</u>]
<strong>Output:</strong> 10
<strong>Explanation:</strong> It is optimal to choose the subsequence [6,1,5] with alternating sum (6 + 5) - 1 = 10.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>5</sup></code></li>
</ul>


**Companies**:  
[Quince](https://leetcode.com/company/quince)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. DP Memoization
 
```cpp
// OJ: https://leetcode.com/contest/biweekly-contest-55/problems/maximum-alternating-subsequence-sum/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)

class Solution {
public:
    long long dp[2][100001]; 

    long long helper(int index, vector<int>& nums, bool isPositive) {
        // Base case: if we've reached the end of the array, return 0
        if (index >= nums.size()) {
            return 0;
        }

        if (dp[isPositive][index] != -1) {
            return dp[isPositive][index];
        }

        // Calculate the current value based on whether it's positive or negative
        long long currentValue = isPositive ? nums[index] : -nums[index];

        // Recursively compute the maximum alternating sum by either including or excluding the current element
        long long includeCurrent = currentValue + helper(index + 1, nums, !isPositive);
        long long excludeCurrent = helper(index + 1, nums, isPositive);

        return dp[isPositive][index] = max(includeCurrent, excludeCurrent);
    }

    long long maxAlternatingSum(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return helper(0, nums, true);
    }
};

```

## Solution 2. DP Tabulation

```cpp
// OJ: https://leetcode.com/problems/maximum-alternating-subsequence-sum/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        long long dp[2][n + 1]; // DP table

        // Base case: When no elements are left, the sum is 0
        dp[0][n] = 0;
        dp[1][n] = 0;

        // Fill the DP table from the end to the beginning
        for (int j = n - 1; j >= 0; j--) {
            // If the current element is treated as positive
            dp[1][j] = max(nums[j] + dp[0][j + 1], dp[1][j + 1]);

            // If the current element is treated as negative
            dp[0][j] = max(-nums[j] + dp[1][j + 1], dp[0][j + 1]);
        }

        // The result is the maximum sum starting from index 0, treating the first element as positive
        return dp[1][0];
    }
};
```
## Solution 3. DP Space Optimization

```cpp

// TC : O(N) and SC : O(1)
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        long long cur[2] = {0, 0}; // cur[0]: negative, cur[1]: positive
        long long next[2] = {0, 0}; // next[0]: negative, next[1]: positive

        // Iterate from the end to the beginning
        for (int j = n - 1; j >= 0; j--) {
            // Compute next states
            next[1] = max(nums[j] + cur[0], cur[1]); // Treat current element as positive
            next[0] = max(-nums[j] + cur[1], cur[0]); // Treat current element as negative

            // Update cur for the next iteration
            cur[0] = next[0];
            cur[1] = next[1];
        }

        // The result is the maximum sum when the first element is treated as positive
        return cur[1];
    }
};

```
