# [1020. Number of Enclaves (Medium)](https://leetcode.com/problems/number-of-enclaves/)

<p>Given a 2D array <code>A</code>, each cell is 0 (representing sea) or 1 (representing land)</p>

<p>A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.</p>

<p>Return the number of land squares in the grid for which we <strong>cannot</strong> walk off the boundary of the grid in any number of moves.</p>

<p>&nbsp;</p>

<p><strong>Example 1:</strong></p>

<pre><strong>Input: </strong><span id="example-input-1-1">[[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]</span>
<strong>Output: </strong><span id="example-output-1">3</span>
<strong>Explanation: </strong>
There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input: </strong><span id="example-input-2-1">[[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]</span>
<strong>Output: </strong><span id="example-output-2">0</span>
<strong>Explanation: </strong>
All 1s are either on the boundary or can reach the boundary.
</pre>

<p>&nbsp;</p>

<p><strong>Note:</strong></p>

<ol>
	<li><code>1 &lt;= A.length &lt;= 500</code></li>
	<li><code>1 &lt;= A[i].length &lt;= 500</code></li>
	<li><code>0 &lt;= A[i][j] &lt;= 1</code></li>
	<li>All rows have the same size.</li>
</ol>

**Related Topics**:  
[Depth-first Search](https://leetcode.com/tag/depth-first-search/)

## Solution 1. DFS

	Initialization: Define the directions for DFS traversal and initialize the dimensions of the grid (M and N).
	Sink Border-connected Lands:
	    Traverse the first and last columns, and the first and last rows of the grid.
	    For each land cell (1) found on the borders, initiate a DFS to mark all connected land cells as 0, effectively sinking them.
	Count Enclaves:
	    After all border-connected land has been sunk, traverse the entire grid again.
	    Count and return the number of remaining 1s, which represent land cells that are enclaves (not connected to the border).

```cpp
// OJ: https://leetcode.com/problems/number-of-enclaves/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(1)

class Solution {
    const int dirs[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // Directions for DFS
    int M, N;

    // DFS to sink connected land cells
    void dfs(vector<vector<int>> &A, int x, int y) {
        if (x < 0 || x >= M || y < 0 || y >= N || !A[x][y]) return;
        A[x][y] = 0; // Sink the land
        for (auto &dir : dirs) dfs(A, x + dir[0], y + dir[1]); // Visit neighbors
    }

public:
    int numEnclaves(vector<vector<int>>& A) {
        M = A.size(), N = A[0].size();
        int ans = 0;
        
        // Sink land connected to borders
        for (int i = 0; i < M; ++i) dfs(A, i, 0), dfs(A, i, N - 1);
        for (int i = 0; i < N; ++i) dfs(A, 0, i), dfs(A, M - 1, i);
        
        // Count remaining land cells (enclaves)
        for (auto &row : A) {
            for (int n : row) {
                if (n) ++ans;
            }
        }
        return ans;
    }
};

```
