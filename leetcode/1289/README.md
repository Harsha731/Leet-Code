# [1289. Minimum Falling Path Sum II (Hard)](https://leetcode.com/problems/minimum-falling-path-sum-ii/)

<p>Given a square grid&nbsp;of integers&nbsp;<code>arr</code>, a <em>falling path with non-zero shifts</em>&nbsp;is a choice of&nbsp;exactly one element from each row of <code>arr</code>, such that no two elements chosen in adjacent rows are in&nbsp;the same column.</p>

<p>Return the&nbsp;minimum&nbsp;sum of a falling path with non-zero shifts.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> arr = [[1,2,3],[4,5,6],[7,8,9]]
<strong>Output:</strong> 13
<strong>Explanation: </strong>
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is&nbsp;[1,5,7], so the answer is&nbsp;13.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= arr.length == arr[i].length &lt;= 200</code></li>
	<li><code>-99 &lt;= arr[i][j] &lt;= 99</code></li>
</ul>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Minimum Falling Path Sum (Medium)](https://leetcode.com/problems/minimum-falling-path-sum/)

## Solution 1. DP

```cpp
// TC : O(N^3) and SC : O(N^2)

class Solution {
public:
    int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
        // Base case: If we reach the last row, return 0
        if (i == grid.size()) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int minSum = INT_MAX;

        for (int k = 0; k < grid[0].size(); k++) {
            if (k == j) {
                continue; 
            }
            minSum = min(minSum, solve(grid, i + 1, k, dp) + grid[i][j]);
        }
        return dp[i][j] = minSum;
    }

    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();

        // Edge case: If there's only one row, return the only element
        if (n == 1) {
            return grid[0][0];
        }

        vector<vector<int>> dp(n, vector<int>(n, -1));
        int result = INT_MAX;

        // Start the recursion from each column in the first row
        for (int j = 0; j < n; j++) {
            result = min(result, solve(grid, 0, j, dp));
        }

        return result;
    }
};
```

## Solution 2. Tabulation
```cpp
// TC : O(N^3) and SC : O(N^2)

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();

        // Edge case: If there's only one row, return the only element
        if (n == 1) {
            return grid[0][0];
        }
        vector<vector<int>> dp(n, vector<int>(n));

        // Fill the first row of the DP table with the values from the grid
        for (int j = 0; j < n; j++) {
            dp[0][j] = grid[0][j];
        }

        // Fill the DP table for the remaining rows
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int minSum = INT_MAX;

                for (int k = 0; k < n; k++) {
                    if (k == j) {
                        continue; 
                    }
                    minSum = min(minSum, dp[i - 1][k] + grid[i][j]);
                }
                dp[i][j] = minSum;
            }
        }

        // Return the minimum value in the last row of the DP table
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};

```

## Solution 3. Space Optimization

```cpp

// TC : O(N^3) and SC : O(N)

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) {
            return grid[0][0];
        }

        vector<int> prev(n);
        vector<int> curr(n);

        for (int j = 0; j < n; j++) {
            prev[j] = grid[0][j];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int minSum = INT_MAX;
                for (int k = 0; k < n; k++) {
                    if (k == j) continue;
                    minSum = min(minSum, prev[k] + grid[i][j]);
                }
                curr[j] = minSum;
            }
            swap(prev, curr);
        }

        return *min_element(prev.begin(), prev.end());
    }
};
```
