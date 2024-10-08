# [417. Pacific Atlantic Water Flow (Medium)](https://leetcode.com/problems/pacific-atlantic-water-flow/)

<p>Given an <code>m x n</code> matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.</p>

<p>Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.</p>

<p>Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.</p>

<p><b>Note:</b></p>

<ol>
	<li>The order of returned grid coordinates does not matter.</li>
	<li>Both <i>m</i> and <i>n</i> are less than 150.</li>
</ol>

<p>&nbsp;</p>

<p><b>Example:</b></p>

<pre>Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
</pre>

<p>&nbsp;</p>


**Related Topics**:  
[Depth-first Search](https://leetcode.com/tag/depth-first-search/), [Breadth-first Search](https://leetcode.com/tag/breadth-first-search/)

## Solution 1.

	We can also use a two bits for each cell to represent if it's reachable from top-left and/or bottom-right. Here for simplicity I just used two `vector<vector<int>>`.
	Initialization: Define directions for movement and set up dimensions of the grid. Initialize two matrices, a and b, to track which cells can reach the Pacific and Atlantic Oceans, respectively.
	Depth-First Search (DFS):
    Perform DFS starting from the edges connected to the Pacific Ocean (left and top edges), marking reachable cells in matrix a.
    Perform DFS from the edges connected to the Atlantic Ocean (right and bottom edges), marking reachable cells in matrix b.
	Collect Results: After both DFS traversals, iterate through the matrices a and b. For each cell that is marked in both matrices, add its coordinates to the result list, indicating that it can reach both oceans.
	Return Output: Return the list of coordinates where water can flow to both oceans.
```cpp
// OJ: https://leetcode.com/problems/pacific-atlantic-water-flow/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(MN)

class Solution {
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}}, M, N;

    // Depth-first search to mark reachable cells
    void dfs(vector<vector<int>> &A, int x, int y, vector<vector<int>> &m) {
        if (m[x][y]) return; // Already visited
        m[x][y] = 1; // Mark as reachable
        for (auto &[dx, dy] : dirs) {
            int a = x + dx, b = y + dy;
            // Check bounds and height condition
            if (a < 0 || a >= M || b < 0 || b >= N || A[a][b] < A[x][y]) continue;
            dfs(A, a, b, m); // Recur for adjacent cells
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& A) {
        if (A.empty() || A[0].empty()) return {};
        M = A.size(), N = A[0].size();
        vector<vector<int>> a(M, vector<int>(N)), b(M, vector<int>(N)), ans; 

        // Start DFS from Pacific Ocean edges
        for (int i = 0; i < M; ++i) {
            dfs(A, i, 0, a); // Left edge
            dfs(A, i, N - 1, b); // Right edge
        }
        // Start DFS from Atlantic Ocean edges
        for (int j = 0; j < N; ++j) {
            dfs(A, 0, j, a); // Top edge
            dfs(A, M - 1, j, b); // Bottom edge
        }
        
        // Collect coordinates where both oceans can be reached
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (a[i][j] && b[i][j]) ans.push_back({i, j});
            }
        }
        return ans; // Return result
    }
};

```
