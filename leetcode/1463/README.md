# [1463. Cherry Pickup II (Hard)](https://leetcode.com/problems/cherry-pickup-ii/)

<p>Given a <code>rows x cols</code> matrix <code>grid</code> representing a field of cherries.&nbsp;Each cell in&nbsp;<code>grid</code>&nbsp;represents the number of cherries that you can collect.</p>

<p>You have two&nbsp;robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.</p>

<p>Return the maximum number of cherries collection using both robots&nbsp; by following the rules below:</p>

<ul>
	<li>From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).</li>
	<li>When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).</li>
	<li>When both robots stay on the same cell, only one of them takes the cherries.</li>
	<li>Both robots cannot move outside of the grid at&nbsp;any moment.</li>
	<li>Both robots should reach the bottom row in the <code>grid</code>.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/04/29/sample_1_1802.png" style="width: 139px; height: 182px;"></strong></p>

<pre><strong>Input:</strong> grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
<strong>Output:</strong> 24
<strong>Explanation:</strong>&nbsp;Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.
</pre>

<p><strong>Example 2:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/04/23/sample_2_1802.png" style="width: 284px; height: 257px;"></strong></p>

<pre><strong>Input:</strong> grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
<strong>Output:</strong> 28
<strong>Explanation:</strong>&nbsp;Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
<strong>Output:</strong> 22
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> grid = [[1,1],[1,1]]
<strong>Output:</strong> 4
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>rows == grid.length</code></li>
	<li><code>cols == grid[i].length</code></li>
	<li><code>2 &lt;= rows, cols &lt;= 70</code></li>
	<li><code>0 &lt;= grid[i][j] &lt;= 100&nbsp;</code></li>
</ul>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. DP Top-down

It's a typical DP problem. The best answer for a given row index `i`, and column index `a` for the robot #1 and `b` for the robot #2 is fixed, but there are multiple ways to get to this state `i, a, b`, so we can use `dp` to memorize the corresponding answer.

Let `dp(i, a, b)` be the max number of cherries we can get given state `i, a, b`.

```
dp(i, a, b) = sum( dp(i + 1, p, q) | (i+1, p), (i+1, q) are the points reachable from (i, a) and (i, b) )
```

Since there are some states unreacheable at the upper part of the `grid`, using top-down DP can easily skip the computation for those states.

```cpp
// OJ: https://leetcode.com/problems/cherry-pickup-ii/
// Author: github.com/lzl124631x
// Time: O(M * N^2)
// Space: O(M * N^2)
class Solution {
public:

int fun(int i, int j1, int j2, int n, int m, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp){
    if(j1<0 || j1>=m || j2<0 || j2>=m) return INT_MIN;
    if(i==n) return 0;
    if(dp[i][j1][j2]!=-1) return dp[i][j1][j2];
    
    int maxi = INT_MIN;
    for(int di=-1;di<=1;di++){
        for(int dj=-1;dj<=1;dj++){
            int ans;
            if(j1==j2){
                ans = grid[i][j1] + fun(i+1, j1+di, j2+dj, n, m, grid, dp);
            }
            else{
                ans = grid[i][j1] + grid[i][j2] + fun(i+1, j1+di, j2+dj, n, m, grid, dp);
            }
            maxi = max(maxi, ans);
        }
    }
    return dp[i][j1][j2] = maxi;
}  

    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return fun(0, 0, m-1, n, m, grid, dp);
    }
};
```

## Solution 2. DP Bottom-up

```cpp
// OJ: https://leetcode.com/problems/cherry-pickup-ii/
// Author: github.com/lzl124631x
// Time: O(M * N^2)
// Space: O(M * N^2)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), dp[71][70][70] = {0};
        for (int r = M - 1; r >= 0; --r) {
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    for (int a = i - 1; a <= i + 1; ++a) {
                        if (a < 0 || a >= N) continue;
                        for (int b = j - 1; b <= j + 1; ++b) {
                            if (b < 0 || b >= N || b <= a) continue;
                            dp[r][a][b] = max(dp[r][a][b],
                                                  (a == b ? A[r][a] : (A[r][a] + A[r][b])) + dp[r + 1][i][j]);
                        }
                    }
                }
            }
        }
        return dp[0][0][N - 1];
    }
};
```

## Solution 3. DP Space Optimization

```cpp
// Time: O(M * N^2)
// Space: O(N^2)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Initialize the DP tables
        vector<vector<int>> curr(m, vector<int>(m, 0)); // Represents the current row
        vector<vector<int>> next(m, vector<int>(m, 0)); // Represents the next row

        // Base case: Fill the last row
        for (int j1 = 0; j1 < m; j1++) {
            for (int j2 = 0; j2 < m; j2++) {
                if (j1 == j2) {
                    next[j1][j2] = grid[n-1][j1]; // Only one robot picks the cherry
                } else {
                    next[j1][j2] = grid[n-1][j1] + grid[n-1][j2]; // Both robots pick cherries
                }
            }
        }

        // Fill the DP tables from the second last row to the first row
        for (int i = n-2; i >= 0; i--) {
            for (int j1 = 0; j1 < m; j1++) {
                for (int j2 = 0; j2 < m; j2++) {
                    int maxi = INT_MIN;

                    // Explore all 9 possible moves (di, dj)
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            int value;

                            if (j1 == j2) {
                                value = grid[i][j1]; // Only one robot picks the cherry
                            } else {
                                value = grid[i][j1] + grid[i][j2]; // Both robots pick cherries
                            }

                            // Check if the new positions are valid
                            if (j1 + di >= 0 && j1 + di < m && j2 + dj >= 0 && j2 + dj < m) {
                                value += next[j1+di][j2+dj]; // Add the result from the next row
                            } else {
                                value += INT_MIN; // Invalid move, ignore
                            }

                            maxi = max(maxi, value); // Track the maximum value
                        }
                    }

                    curr[j1][j2] = maxi; // Store the result in the current row
                }
            }

            // Swap curr and next for the next iteration
            swap(curr, next);
        }

        // The result is the maximum cherries collected starting from the first row
        return next[0][m-1];
    }
};
```
