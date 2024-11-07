# [740. Delete and Earn (Medium)](https://leetcode.com/problems/delete-and-earn/)

<p>You are given an integer array <code>nums</code>. You want to maximize the number of points you get by performing the following operation any number of times:</p>

<ul>
	<li>Pick any <code>nums[i]</code> and delete it to earn <code>nums[i]</code> points. Afterwards, you must delete <b>every</b> element equal to <code>nums[i] - 1</code> and <strong>every</strong> element equal to <code>nums[i] + 1</code>.</li>
</ul>

<p>Return <em>the <strong>maximum number of points</strong> you can earn by applying the above operation some number of times</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> nums = [3,4,2]
<strong>Output:</strong> 6
<strong>Explanation:</strong> You can perform the following operations:
- Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
- Delete 2 to earn 2 points. nums = [].
You earn a total of 6 points.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> nums = [2,2,3,3,3,4]
<strong>Output:</strong> 9
<strong>Explanation:</strong> You can perform the following operations:
- Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
- Delete a 3 again to earn 3 points. nums = [3].
- Delete a 3 once more to earn 3 points. nums = [].
You earn a total of 9 points.</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 2 * 10<sup>4</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
</ul>


**Companies**:  
[Goldman Sachs](https://leetcode.com/company/goldman-sachs), [Amazon](https://leetcode.com/company/amazon), [Facebook](https://leetcode.com/company/facebook), [Bloomberg](https://leetcode.com/company/bloomberg)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Hash Table](https://leetcode.com/tag/hash-table/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [House Robber (Medium)](https://leetcode.com/problems/house-robber/)

## Solution 1. DP

Firstly, to avoid duplicate, store the data in a map from the number to its count.

Let `dp[i]` be the max point you can get at point `i`.

If `num != prevNum + 1`, we can freely pick `num`, then `dp[i] = dp[i-1] + num * count`.

Otherwise:
* If we skip `num`, `dp[i] = dp[i-1]`.
* If we pick `num`, `dp[i] = dp[i-2] + num * count`.

So in sum:

```
dp[i] = num == prevNum ? max(dp[i-1], dp[i-2] + num * count) : (dp[i-1] + num * count)
```

```cpp
// OJ: https://leetcode.com/problems/delete-and-earn/
// Author: github.com/lzl124631x
// Time: O(NlogN)
// Space: O(N)
class Solution {
    vector<int> points;
    vector<int> memo;
    int minVal;

    // Top-down helper function
    int dp(int i) {
        if (i < minVal) return 0; // Base case: indices less than minVal return 0
        if (memo[i] != -1) return memo[i]; // Return memoized result if available

        // Recurrence relation: choose the max between skipping i or taking i
        return memo[i] = max(dp(i - 1), dp(i - 2) + points[i]);
    }

public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;

        // Find the minimum and maximum values in nums
        minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());

        // Create and fill the points array
        points.resize(maxVal + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        // Initialize the memoization array
        memo.assign(maxVal + 1, -1);

        return dp(maxVal); // Start recursion from maxVal
    }
};

```

## Solution 2. DP

Let `use[i]` be the maximum points we can get if we use numbers in range `[1,i]` and we must use the number `i`.

Let `skip[i]` be the maximum points we can get if we use numbers in range `[1,i]` and we must skip the number `i`.

```
use[0] = skip[0] = 0
use[i] = skip[i-1] + cnt[i] * i
skip[i] = max(use[i-1], skip[i-1])
```

```cpp
// OJ: https://leetcode.com/problems/delete-and-earn/
// Author: github.com/lzl124631x
// Time: O(N + R) where `R` is the range of numbers in `A`
// Space: O(R)
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;

        // Find the minimum and maximum values in nums
        int minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());

        // Create and fill the points array
        vector<int> points(maxVal + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        // Use dynamic programming to solve the problem
        vector<int> dp(maxVal + 1, 0);
        dp[minVal] = points[minVal]; // Initialize dp at minVal

        for (int i = minVal + 1; i <= maxVal; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + points[i]);
        }

        return dp[maxVal];
    }
};

```
