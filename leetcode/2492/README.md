# [2492. Minimum Score of a Path Between Two Cities (Medium)](https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities)

<p>You are given a positive integer <code>n</code> representing <code>n</code> cities numbered from <code>1</code> to <code>n</code>. You are also given a <strong>2D</strong> array <code>roads</code> where <code>roads[i] = [a<sub>i</sub>, b<sub>i</sub>, distance<sub>i</sub>]</code> indicates that there is a <strong>bidirectional </strong>road between cities <code>a<sub>i</sub></code> and <code>b<sub>i</sub></code> with a distance equal to <code>distance<sub>i</sub></code>. The cities graph is not necessarily connected.</p>
<p>The <strong>score</strong> of a path between two cities is defined as the <strong>minimum </strong>distance of a road in this path.</p>
<p>Return <em>the <strong>minimum </strong>possible score of a path between cities </em><code>1</code><em> and </em><code>n</code>.</p>
<p><strong>Note</strong>:</p>
<ul>
	<li>A path is a sequence of roads between two cities.</li>
	<li>It is allowed for a path to contain the same road <strong>multiple</strong> times, and you can visit cities <code>1</code> and <code>n</code> multiple times along the path.</li>
	<li>The test cases are generated such that there is <strong>at least</strong> one path between <code>1</code> and <code>n</code>.</li>
</ul>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2022/10/12/graph11.png" style="width: 190px; height: 231px;">
<pre><strong>Input:</strong> n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
<strong>Output:</strong> 5
<strong>Explanation:</strong> The path from city 1 to 4 with the minimum score is: 1 -&gt; 2 -&gt; 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.
</pre>
<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2022/10/12/graph22.png" style="width: 190px; height: 231px;">
<pre><strong>Input:</strong> n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
<strong>Output:</strong> 2
<strong>Explanation:</strong> The path from city 1 to 4 with the minimum score is: 1 -&gt; 2 -&gt; 1 -&gt; 3 -&gt; 4. The score of this path is min(2,2,4,7) = 2.
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>2 &lt;= n &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= roads.length &lt;= 10<sup>5</sup></code></li>
	<li><code>roads[i].length == 3</code></li>
	<li><code>1 &lt;= a<sub>i</sub>, b<sub>i</sub> &lt;= n</code></li>
	<li><code>a<sub>i</sub> != b<sub>i</sub></code></li>
	<li><code>1 &lt;= distance<sub>i</sub> &lt;= 10<sup>4</sup></code></li>
	<li>There are no repeated edges.</li>
	<li>There is at least one path between <code>1</code> and <code>n</code>.</li>
</ul>

**Companies**:
[Unbxd](https://leetcode.com/company/unbxd)

**Related Topics**:  
[Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Breadth-First Search](https://leetcode.com/tag/breadth-first-search/), [Union Find](https://leetcode.com/tag/union-find/), [Graph](https://leetcode.com/tag/graph/)

**Similar Questions**:
* [Checking Existence of Edge Length Limited Paths (Hard)](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/)
* [Checking Existence of Edge Length Limited Paths II (Hard)](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/)

## Solution 1. DFS

	Graph Construction: The input edges are used to build an adjacency list representation of the graph, where each city (node) points to its connected cities along with the corresponding road distances.
	DFS Traversal: A depth-first search (DFS) is initiated from the starting city (city 1). As the DFS explores the graph, it marks cities as visited to avoid revisiting them.
	Minimum Distance Calculation: During the traversal, the algorithm continuously checks the distances of roads leading to neighboring cities and updates the minimum distance encountered.
	Return Result: Once all reachable cities are visited, the function returns the minimum road score found.

```cpp
// OJ: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N + E)

class Solution {
    vector<vector<pair<int, int>>> G; // Graph representation
    vector<bool> seen; // Track visited cities
    int ans = INT_MAX; // Initialize minimum score

    void dfs(int u) {
        if (seen[u]) return; // If already visited, return
        seen[u] = true; // Mark current city as visited
        for (auto &[v, dist] : G[u]) {
            ans = min(ans, dist); // Update minimum score
            dfs(v); // Recursive DFS for neighboring cities
        }
    }
    
public:
    int minScore(int n, vector<vector<int>>& E) {
        G.resize(n); // Resize graph to number of cities
        for (auto &e : E) {
            int u = e[0] - 1, v = e[1] - 1, dist = e[2];
            G[u].emplace_back(v, dist); // Add edge to graph
            G[v].emplace_back(u, dist); // Add bidirectional edge
        }
        seen.resize(n, false); // Initialize seen array
        dfs(0); // Start DFS from city 1 (index 0)
        return ans; // Return the minimum score found
    }
};

```

## Solution 2. Union Find
	
	Initialization: The union-find structure is initialized with each city as its own parent, and the minimum scores for each city are set to INT_MAX.
	Union-Find Operations: The find function implements path compression, which helps keep the structure flat and efficient. The connect function merges two sets and updates the minimum score for the connected component.
	Processing Edges: For each edge, the cities are connected, and the minimum road score is updated.
	Final Result: The minimum score for paths from the starting city (city 1) is returned using the union-find structure to find the root of the component containing city 1.

```cpp
// OJ: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities
// Author: github.com/lzl124631x
// Time: O(N + ElogN). This can be reduced to O(N + E) if we use union-by-rank.
// Space: O(N)

class Solution {
public:
    int minScore(int n, vector<vector<int>>& E) {
        vector<int> id(n), score(n, INT_MAX); // Union-Find structure
        iota(begin(id), end(id), 0); // Initialize union-find
        function<int(int)> find = [&](int a) {
            return id[a] == a ? a : (id[a] = find(id[a])); // Find with path compression
        };
        auto connect = [&](int u, int v, int dist) {
            int p = find(u), q = find(v);
            id[q] = p; // Union operation
            score[p] = min({score[p], score[q], dist}); // Update minimum score
        };
        for (auto &e : E) {
            int u = e[0] - 1, v = e[1] - 1, dist = e[2];
            connect(u, v, dist); // Connect nodes
        }
        return score[find(0)]; // Return minimum score for city 1
    }
};


```
