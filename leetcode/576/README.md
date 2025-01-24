# [576. Out of Boundary Paths (Medium)](https://leetcode.com/problems/out-of-boundary-paths/)

<p>There is an <code>m x n</code> grid with a ball. The ball is initially at the position <code>[startRow, startColumn]</code>. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply <strong>at most</strong> <code>maxMove</code> moves to the ball.</p>

<p>Given the five integers <code>m</code>, <code>n</code>, <code>maxMove</code>, <code>startRow</code>, <code>startColumn</code>, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it <strong>modulo</strong> <code>10<sup>9</sup> + 7</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/04/28/out_of_boundary_paths_1.png" style="width: 500px; height: 296px;">
<pre><strong>Input:</strong> m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
<strong>Output:</strong> 6
</pre>

<p><strong>Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/04/28/out_of_boundary_paths_2.png" style="width: 500px; height: 293px;">
<pre><strong>Input:</strong> m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
<strong>Output:</strong> 12
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= m, n &lt;= 50</code></li>
	<li><code>0 &lt;= maxMove &lt;= 50</code></li>
	<li><code>0 &lt;= startRow &lt; m</code></li>
	<li><code>0 &lt;= startColumn &lt; n</code></li>
</ul>

**Companies**:  
[Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Knight Probability in Chessboard (Medium)](https://leetcode.com/problems/knight-probability-in-chessboard/)
* [Execution of All Suffix Instructions Staying in a Grid (Medium)](https://leetcode.com/problems/execution-of-all-suffix-instructions-staying-in-a-grid/)

## Solution 1. DP Top-down

Let `dp[x][y][k]` be the number of out-of-boundary moves starting from cell `(x, y)` with at most `k` moves.

```
dp[x][y][k] = SUM( dp[a][b][k - 1] | (a,b) is a neighbor of (x, y) )

dp[x][y][k] = 1   if (x, y) is out-of-boundary, and 0 <= k <= maxMoves

dp[x][y][0] = 0   if (x, y) is not out-of-boundary
```

The answer is `dp[startRow][startColumn][maxMove]`.

```cpp
// OJ: https://leetcode.com/problems/out-of-boundary-paths/
// Author: github.com/lzl124631x
// Time: O(MNK)
// Space: O(MNK)
class Solution {
    long rows, cols;
    long dp[50][50][51];
    const int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    const long mod = 1e9 + 7;

    int dfs(int x, int y, int moves) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) return 1;
        if (moves == 0) return 0;
        if (dp[x][y][moves] != -1) return dp[x][y][moves];

        long count = 0;
        for (const auto& [dx, dy] : dirs) {
            int newX = x + dx, newY = y + dy;
            count = (dfs(newX, newY, moves - 1) + count) % mod;
        }

        return dp[x][y][moves] = count;
    }

public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        rows = m;
        cols = n;
        memset(dp, -1, sizeof(dp));
        return dfs(startRow, startColumn, maxMove);
    }
};
```

## Solution 3. DP Bottom-up

Let `dp[i][j][k]` be the number of ways to go out of boundary from point `(i, j)` using exactly `k` steps.

```
dp[i][j][k] = SUM( dp[a][b][k - 1] | (a, b) is neighbor of (i, j) )
```

`dp[i][j][1]` is the number of edges the point `(i, j)` touches.

The answer is `SUM( dp[x][y][k] | k = 1, 2, ..., maxMoves )`.

Why not define `dp[i][j][k]` as the number of ways to go out of boundary from point `(i, j)` **with at most `k` steps**?

Because when computing `dp[i][j][k]`, assume we know `dp[i][j][k - 1]`, then we need to compute the ways to go out of boundary with exact `k` steps. So we need the number of ways with **exact `k` steps** any way.

```cpp
// OJ: https://leetcode.com/problems/out-of-boundary-paths/
// Author: github.com/lzl124631x
// Time: O(MNK)
// Space: O(MN)

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int mod = 1e9 + 7;
        const int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        // dp[k][x][y] = number of ways to reach (x, y) in exactly k moves
        vector<vector<vector<long>>> dp(maxMove + 1, vector<vector<long>>(m, vector<long>(n, 0)));

        // Base case: 0 moves, starting at (startRow, startColumn)
        dp[0][startRow][startColumn] = 1;

        long result = 0;

        // Iterate over the number of moves
        for (int k = 0; k < maxMove; k++) {
            for (int x = 0; x < m; x++) {
                for (int y = 0; y < n; y++) {
                    // If no ways to reach (x, y) in k moves, skip
                    if (dp[k][x][y] == 0) continue;

                    // Explore all 4 directions
                    for (const auto& [dx, dy] : dirs) {
                        int newX = x + dx, newY = y + dy;

                        // If the new position is out of bounds, add to the result
                        if (newX < 0 || newX >= m || newY < 0 || newY >= n) {
                            result = (result + dp[k][x][y]) % mod;
                        } else {
                            // Otherwise, update the number of ways to reach (newX, newY) in k+1 moves
                            dp[k + 1][newX][newY] = (dp[k + 1][newX][newY] + dp[k][x][y]) % mod;
                        }
                    }
                }
            }
        }

        return result;
    }
};    
```
