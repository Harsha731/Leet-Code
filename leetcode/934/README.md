# [934. Shortest Bridge (Medium)](https://leetcode.com/problems/shortest-bridge/)

<p>In a given 2D binary array <code>grid</code>, there are two islands.&nbsp; (An island is a 4-directionally connected group of&nbsp;<code>1</code>s not connected to any other 1s.)</p>

<p>Now, we may change <code>0</code>s to <code>1</code>s so as to connect the two islands together to form 1 island.</p>

<p>Return the smallest number of <code>0</code>s that must be flipped.&nbsp; (It is guaranteed that the answer is at least 1.)</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> grid = [[0,1],[1,0]]
<strong>Output:</strong> 1
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> grid = [[0,1,0],[0,0,0],[0,0,1]]
<strong>Output:</strong> 2
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
<strong>Output:</strong> 1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>2 &lt;= grid.length == grid[0].length &lt;= 100</code></li>
	<li><code>grid[i][j] == 0</code> or <code>grid[i][j] == 1</code></li>
</ul>


**Companies**:  
[Microsoft](https://leetcode.com/company/microsoft), [Google](https://leetcode.com/company/google), [Uber](https://leetcode.com/company/uber), [Bloomberg](https://leetcode.com/company/bloomberg), [Snapchat](https://leetcode.com/company/snapchat)

**Related Topics**:  
[Depth-first Search](https://leetcode.com/tag/depth-first-search/), [Breadth-first Search](https://leetcode.com/tag/breadth-first-search/)

## Solution 1.

	DFS Function: This function marks the cells of the islands with different colors and adds their coordinates to respective queues (qa for one island, qb for the other).
	BFS Function: This function expands the distance from the marked islands into the water cells, recording the distance until reaching the other island.
	Shortest Bridge Calculation: After running DFS to color the islands and BFS to determine distances, the code checks all water cells to find the minimum distance required to connect the two islands by flipping 0s to 1s.

```cpp
// OJ: https://leetcode.com/problems/shortest-bridge/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(MN)

class Solution {
    int M, N, dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    queue<pair<int, int>> qa, qb; // queues for BFS

    // DFS to mark islands with different colors
    void dfs(vector<vector<int>> &A, int x, int y, int color) {
        A[x][y] = color; // mark the cell with the current color
        if (color == 2) qa.emplace(x, y); // add to queue for the first island
        else qb.emplace(x, y); // add to queue for the second island
        for (auto &[dx, dy] : dirs) {
            int a = x + dx, b = y + dy;
            if (a < 0 || b < 0 || a >= M || b >= N || A[a][b] != 1) continue; // boundary check
            dfs(A, a, b, color); // continue DFS
        }
    }

    // BFS to expand the island until reaching the other
    void bfs(vector<vector<int>> &A, queue<pair<int, int>> &q, vector<vector<int>> &dist) {
        int step = 1; // to count distance
        while (q.size()) {
            int cnt = q.size();
            while (cnt--) {
                auto [x, y] = q.front();
                q.pop();
                for (auto &[dx, dy] : dirs) {
                    int a = x + dx, b = y + dy;
                    if (a < 0 || b < 0 || a >= M || b >= N || A[a][b] != 0 || dist[a][b] != INT_MAX) continue; // boundary check
                    dist[a][b] = step; // update distance
                    q.emplace(a, b); // add to the queue
                }
            }
            ++step; // increment distance for next level
        }
    }

public:
    int shortestBridge(vector<vector<int>>& A) {
        M = A.size(), N = A[0].size();
        int color = 2, ans = INT_MAX;
        vector<vector<int>> da(M, vector<int>(N, INT_MAX)), db(M, vector<int>(N, INT_MAX));
        
        // Mark both islands
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 1) dfs(A, i, j, color++); // DFS to color islands
            }
        }
        
        bfs(A, qa, da); // BFS for first island
        bfs(A, qb, db); // BFS for second island
        
        // Calculate the minimum distance to connect the two islands
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 0 && da[i][j] != INT_MAX && db[i][j] != INT_MAX)
                    ans = min(ans, da[i][j] + db[i][j] - 1); // update the answer
            }
        }
        return ans; // return the result
    }
};

```
