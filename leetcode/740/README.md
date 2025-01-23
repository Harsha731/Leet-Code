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

## Solution 1. Tabulation

```cpp

/* Same as House robber problem
Using max_element takes O(N)
iteration takes O(M), M is maxVal
TC : O(N+M) and SC : O(M)
*/

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) return 0;

        // Find the maximum value in nums to determine the size of dp array
        int maxVal = *max_element(nums.begin(), nums.end());

        // Create and fill the points array
        vector<int> points(maxVal + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        // Use dynamic programming to solve the problem
        vector<int> dp(maxVal + 1, 0);
        dp[0] = 0; // No points for number 0
        dp[1] = points[1]; // Points we get for number 1

        for (int i = 2; i <= maxVal; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + points[i]);
        }

        return dp[maxVal];
    }
};
```

## Solution 2. Memoization
```cpp
class Solution {
private:
    int solve(int num, std::vector<int>& points, std::unordered_map<int, int>& memo) {
        if (num <= 0) return 0;
        if (memo.find(num) != memo.end()) return memo[num];

        int take = points[num] + solve(num - 2, points, memo);
        int skip = solve(num - 1, points, memo);

        memo[num] = std::max(take, skip);
        return memo[num];
    }

public:
    int deleteAndEarn(std::vector<int>& nums) {
        if (nums.empty()) return 0;

        int maxVal = *std::max_element(nums.begin(), nums.end());
        std::vector<int> points(maxVal + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        std::unordered_map<int, int> memo;
        return solve(maxVal, points, memo);
    }
};
```
