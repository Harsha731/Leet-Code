# [2742. Painting the Walls (Hard)](https://leetcode.com/problems/painting-the-walls)

<p>You are given two <strong>0-indexed</strong> integer arrays,&nbsp;<code>cost</code> and <code>time</code>, of size <code>n</code> representing the costs and the time taken to paint <code>n</code> different walls respectively. There are two painters available:</p>

<ul>
	<li>A<strong>&nbsp;paid painter</strong>&nbsp;that paints the <code>i<sup>th</sup></code> wall in <code>time[i]</code> units of time and takes <code>cost[i]</code> units of money.</li>
	<li>A<strong>&nbsp;free painter</strong> that paints&nbsp;<strong>any</strong> wall in <code>1</code> unit of time at a cost of <code>0</code>. But the&nbsp;free painter can only be used if the paid painter is already <strong>occupied</strong>.</li>
</ul>

<p>Return <em>the minimum amount of money required to paint the </em><code>n</code><em>&nbsp;walls.</em></p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> cost = [1,2,3,2], time = [1,2,3,2]
<strong>Output:</strong> 3
<strong>Explanation:</strong> The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time; meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2 = 3.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> cost = [2,3,4,2], time = [1,1,1,1]
<strong>Output:</strong> 4
<strong>Explanation:</strong> The walls at index 0 and 3 will be painted by the paid painter, and it will take 2 units of time; meanwhile, the free painter will paint the walls at index 1 and 2, free of cost in 2 units of time. Thus, the total cost is 2 + 2 = 4.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= cost.length &lt;= 500</code></li>
	<li><code>cost.length == time.length</code></li>
	<li><code>1 &lt;= cost[i] &lt;= 10<sup>6</sup></code></li>
	<li><code>1 &lt;= time[i] &lt;= 500</code></li>
</ul>


**Companies**:
[Amazon](https://leetcode.com/company/amazon), [Adobe](https://leetcode.com/company/adobe), [Snowflake](https://leetcode.com/company/snowflake), [Apple](https://leetcode.com/company/apple)

**Related Topics**:  
[Array](https://leetcode.com/tag/array), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming)

**Hints**:
* Can we break the problem down into smaller subproblems and use DP?
* Paid painters will be used for a maximum of N/2 units of time. There is no need to use paid painter for a time greater than this.

## Solution 1. Memoization

```cpp
// OJ: https://leetcode.com/problems/painting-the-walls
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N)

class Solution {
public:
    int solve(vector<int>& cost, vector<int>& time, int idx, int walls, vector<vector<int>>& dp) {
        // Base case: If no walls are left to paint, no cost is needed.
        if (walls <= 0) {
            return 0;
        }
        // Base case: If no painters are left but walls remain, return a large value (invalid state).
        if (idx >= cost.size()) {
            return 1e9;
        }
        // If the result is already computed, return it.
        if (dp[idx][walls] != -1) {
            return dp[idx][walls];
        }

        // Case 1: Do not take the current painter.
        int skip = solve(cost, time, idx + 1, walls, dp);

        // Case 2: Take the current painter. Subtract the walls painted by the current painter (time[idx] + 1).
        int take = cost[idx] + solve(cost, time, idx + 1, walls - time[idx] - 1, dp);

        return dp[idx][walls] = min(skip, take);
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = time.size();
        vector<vector<int>> dp(501, vector<int>(501, -1));
        // Start solving from the first painter and all walls remaining.
        return solve(cost, time, 0, n, dp);
    }
};
```

## Solution 2. Tabulation

```cpp
// dp[i][j] represents the minimum cost to paint j walls using the first i painters

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));

        // Base case: If no walls are to be painted, the cost is 0.
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }

        // Fill the DP table
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Case 1: Do not take the current painter
                int notTake = dp[i - 1][j];
                // Case 2: Take the current painter
                int take = cost[i - 1] + dp[i - 1][max(j - time[i - 1] - 1, 0)];
                // Choose the minimum of the two options
                dp[i][j] = min(notTake, take);
            }
        }

        // The answer is the minimum cost to paint all `n` walls
        return dp[n][n];
    }
};
```


## Solution 3. Space Optimization

```cpp

// dp[i][j] represents the minimum cost to paint j walls using the first i painters

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<int> prev(n + 1, 1e9); // Initialize prev array
        prev[0] = 0; // Base case: No cost to paint 0 walls

        // Iterate through each painter
        for (int i = 0; i < n; ++i) {
            vector<int> curr(n + 1, 1e9); // Initialize curr array
            for (int j = 0; j <= n; ++j) {
                // Case 1: Skip the current painter
                int skip = prev[j];
                // Case 2: Take the current painter
                int take = cost[i] + prev[max(j - time[i] - 1, 0)];
                // Choose the minimum of the two options
                curr[j] = min(skip, take);
            }
            prev = curr; // Update prev for the next iteration
        }

        // The answer is the minimum cost to paint all `n` walls
        return prev[n];
    }
};
```
