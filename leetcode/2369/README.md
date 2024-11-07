# [2369. Check if There is a Valid Partition For The Array (Medium)](https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array)

<p>You are given a <strong>0-indexed</strong> integer array <code>nums</code>. You have to partition the array into one or more <strong>contiguous</strong> subarrays.</p>
<p>We call a partition of the array <strong>valid</strong> if each of the obtained subarrays satisfies <strong>one</strong> of the following conditions:</p>
<ol>
	<li>The subarray consists of <strong>exactly</strong> <code>2</code> equal elements. For example, the subarray <code>[2,2]</code> is good.</li>
	<li>The subarray consists of <strong>exactly</strong> <code>3</code> equal elements. For example, the subarray <code>[4,4,4]</code> is good.</li>
	<li>The subarray consists of <strong>exactly</strong> <code>3</code> consecutive increasing elements, that is, the difference between adjacent elements is <code>1</code>. For example, the subarray <code>[3,4,5]</code> is good, but the subarray <code>[1,3,5]</code> is not.</li>
</ol>
<p>Return <code>true</code><em> if the array has <strong>at least</strong> one valid partition</em>. Otherwise, return <code>false</code>.</p>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> nums = [4,4,4,5,6]
<strong>Output:</strong> true
<strong>Explanation:</strong> The array can be partitioned into the subarrays [4,4] and [4,5,6].
This partition is valid, so we return true.
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [1,1,1,2]
<strong>Output:</strong> false
<strong>Explanation:</strong> There is no valid partition for this array.
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>2 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>6</sup></code></li>
</ul>

**Companies**:
[Google](https://leetcode.com/company/google)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. Top-down DP

```cpp
// OJ: https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    bool dfs(int index, const vector<int>& nums, vector<int>& memo, int size) {
        if (index == size) return true;
        if (memo[index] != -1) return memo[index] == 1;

        bool isValidPartition = false;

        if (index + 1 <= size - 1 && nums[index] == nums[index + 1])
            isValidPartition = isValidPartition || dfs(index + 2, nums, memo, size);
      
        if (index + 2 <= size - 1 && nums[index] == nums[index + 1] && nums[index + 1] == nums[index + 2])
            isValidPartition = isValidPartition || dfs(index + 3, nums, memo, size);
      
        if (index + 2 <= size - 1 && nums[index + 1] - nums[index] == 1 && nums[index + 2] - nums[index + 1] == 1)
            isValidPartition = isValidPartition || dfs(index + 3, nums, memo, size);
      
        memo[index] = isValidPartition ? 1 : 0;
      
        return isValidPartition;
    }

    bool validPartition(vector<int>& nums) {
        int size = nums.size();
        vector<int> memo(size, -1);
        return dfs(0, nums, memo, size);
    }
};
```

## Solution 2. Bottom-up DP

```cpp
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return false; // If there's only one element, no valid partition exists.

        vector<bool> dp(n + 1, false); // DP array where dp[i] means whether nums[0..i-1] can be partitioned.
        dp[0] = true; // Base case: an empty array is always valid.

        for (int i = 2; i <= n; ++i) {
            // Check for a valid partition ending at index i-1
            if (nums[i - 1] == nums[i - 2]) {
                dp[i] = dp[i] || dp[i - 2]; // Case: two consecutive equal numbers.
            }
            if (i > 2 && nums[i - 1] == nums[i - 2] && nums[i - 2] == nums[i - 3]) {
                dp[i] = dp[i] || dp[i - 3]; // Case: three consecutive equal numbers.
            }
            if (i > 2 && nums[i - 1] - nums[i - 2] == 1 && nums[i - 2] - nums[i - 3] == 1) {
                dp[i] = dp[i] || dp[i - 3]; // Case: three consecutive numbers forming a strict increasing sequence.
            }
        }

        return dp[n]; // The result for the entire array is stored in dp[n].
    }
};
```
