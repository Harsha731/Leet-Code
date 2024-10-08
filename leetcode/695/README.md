# [695. Max Area of Island (Medium)](https://leetcode.com/problems/max-area-of-island/)

<p>You are given an <code>m x n</code> binary matrix <code>grid</code>. An island is a group of <code>1</code>'s (representing land) connected <strong>4-directionally</strong> (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.</p>

<p>The <strong>area</strong> of an island is the number of cells with a value <code>1</code> in the island.</p>

<p>Return <em>the maximum <strong>area</strong> of an island in </em><code>grid</code>. If there is no island, return <code>0</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/05/01/maxarea1-grid.jpg" style="width: 500px; height: 310px;">
<pre><strong>Input:</strong> grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
<strong>Output:</strong> 6
<strong>Explanation:</strong> The answer is not 11, because the island must be connected 4-directionally.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> grid = [[0,0,0,0,0,0,0,0]]
<strong>Output:</strong> 0
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>m == grid.length</code></li>
	<li><code>n == grid[i].length</code></li>
	<li><code>1 &lt;= m, n &lt;= 50</code></li>
	<li><code>grid[i][j]</code> is either <code>0</code> or <code>1</code>.</li>
</ul>

**Companies**:  
[Google](https://leetcode.com/company/google), [Affirm](https://leetcode.com/company/affirm), [Amazon](https://leetcode.com/company/amazon), [Qualtrics](https://leetcode.com/company/qualtrics), [Facebook](https://leetcode.com/company/facebook), [Uber](https://leetcode.com/company/uber), [DoorDash](https://leetcode.com/company/doordash)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Breadth-First Search](https://leetcode.com/tag/breadth-first-search/), [Union Find](https://leetcode.com/tag/union-find/), [Matrix](https://leetcode.com/tag/matrix/)

**Similar Questions**:
* [Number of Islands (Medium)](https://leetcode.com/problems/number-of-islands/)
* [Island Perimeter (Easy)](https://leetcode.com/problems/island-perimeter/)
* [Largest Submatrix With Rearrangements (Medium)](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)
* [Detonate the Maximum Bombs (Medium)](https://leetcode.com/problems/detonate-the-maximum-bombs/)

## Solution 1. DFS

	Initialization: Determine the grid dimensions and set up directions for exploring adjacent cells.
	Depth-First Search (DFS): Define a DFS function to explore and count the area of connected land cells, marking visited cells as 0.
	Grid Traversal: Iterate through each cell in the grid. When a land cell (1) is found, call the DFS function to calculate the area and update the maximum area if needed.
	Return Result: After processing the entire grid, return the largest island area found.

```cpp
// OJ: https://leetcode.com/problems/max-area-of-island/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(MN)

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), dirs[4][2] = {{0,1},{0,-1},{-1,0},{1,0}}, ans = 0;
        
        // Depth-first search to calculate area of the island
        function<int(int, int)> dfs = [&](int i, int j) {
            A[i][j] = 0; // Mark the cell as visited
            int cnt = 1; // Count the current cell
            for (auto &[dx, dy] : dirs) {
                int x = i + dx, y = j + dy;
                // Explore adjacent cells
                if (x < 0 || x >= M || y < 0 || y >= N || A[x][y] == 0) continue;
                cnt += dfs(x, y); // Add area of the connected land
            }
            return cnt; // Return the area count
        };
        
        // Iterate through the grid to find islands
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 0) continue; // Skip water cells
                ans = max(ans, dfs(i, j)); // Update maximum area
            }
        }
        return ans; // Return the maximum area found
    }
};


```

## Solution 2. BFS
	
	Grid Traversal: Iterate through each cell in the grid.
	BFS Initialization: When a land cell (1) is found, initialize a breadth-first search (BFS) queue, mark the cell as visited by setting it to 0, and start counting the island's area.
	BFS Exploration: For each cell in the queue, explore its adjacent cells. If an adjacent cell is land (1), mark it as visited, add it to the queue, and increment the area count.
	Update Maximum Area: After processing an entire island, update the maximum area found if the current island's area is larger.
	Return Result: Finally, return the largest area of any island found in the grid.

```cpp
// OJ: https://leetcode.com/problems/max-area-of-island/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(M + N)

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), dirs[4][2] = {{0,1},{0,-1},{-1,0},{1,0}}, ans = 0;

        // Iterate through the grid
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 0) continue; // Skip water cells
                
                queue<pair<int, int>> q{{{i, j}}}; // Initialize BFS queue
                A[i][j] = 0; // Mark the starting land cell as visited
                int cnt = 0; // Count the area of the island
                
                // Perform BFS to explore the island
                while (q.size()) {
                    auto [x, y] = q.front(); // Get the front cell
                    q.pop();
                    for (auto &[dx, dy] : dirs) {
                        int a = x + dx, b = y + dy;
                        // Check boundaries and unvisited land cells
                        if (a < 0 || a >= M || b < 0 || b >= N || A[a][b] == 0) continue;
                        A[a][b] = 0; // Mark the cell as visited
                        q.emplace(a, b); // Add the cell to the queue
                    }
                    ++cnt; // Increment the island area count
                }
                ans = max(ans, cnt); // Update maximum area found
            }
        }
        return ans; // Return the maximum area
    }
};

```

## Solution 3. Union Find

	Initialization: Create a Union-Find structure to manage connected components (islands) in the grid.
	Connect Land Cells: Traverse the grid and connect adjacent land cells (1) using the connect method. This establishes unions for cells that are part of the same island.
	Calculate Maximum Area: After connecting the cells, iterate through the grid again to find the maximum size of any island by retrieving the size of each component through the getSize method.
	Return Result: Finally, return the largest area found among all islands.

```cpp
// OJ: https://leetcode.com/problems/max-area-of-island/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(MN)
class UnionFind {
    vector<int> id, size;
public:
    UnionFind(int N) : id(N), size(N, 1) {
        iota(begin(id), end(id), 0); // Initialize id with self-references
    }
    int find(int x) {
        return id[x] == x ? x : (id[x] = find(id[x])); // Path compression
    }
    void connect(int x, int y) {
        int p = find(x), q = find(y);
        if (p == q) return; // Already connected
        id[p] = q; // Union the sets
        size[q] += size[p]; // Update size of the root
    }
    int getSize(int x) { return size[find(x)]; } // Get the size of the set
};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), dirs[4][2] = {{0,1},{0,-1},{-1,0},{1,0}}, ans = 0;
        UnionFind uf(M * N); // Union-Find structure for grid cells
        auto key = [&](int x, int y) { return x * N + y; }; // Mapping 2D index to 1D
        
        // Connect adjacent land cells
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 0) continue; // Skip water cells
                for (auto &[dx, dy] : dirs) {
                    int a = i + dx, b = j + dy;
                    if (a < 0 || a >= M || b < 0 || b >= N || A[a][b] == 0) continue; // Check bounds and land
                    uf.connect(key(i, j), key(a, b)); // Connect land cells
                }
            }
        }

        // Calculate maximum area of connected land
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == 1) ans = max(ans, uf.getSize(key(i, j))); // Update max area
            }
        }
        return ans; // Return the maximum area found
    }
};

```
