# [261. Graph Valid Tree (Medium)](https://leetcode.com/problems/graph-valid-tree)

<p>You have a graph of <code>n</code> nodes labeled from <code>0</code> to <code>n - 1</code>. You are given an integer n and a list of <code>edges</code> where <code>edges[i] = [a<sub>i</sub>, b<sub>i</sub>]</code> indicates that there is an undirected edge between nodes <code>a<sub>i</sub></code> and <code>b<sub>i</sub></code> in the graph.</p>
<p>Return <code>true</code> <em>if the edges of the given graph make up a valid tree, and</em> <code>false</code> <em>otherwise</em>.</p>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/12/tree1-graph.jpg" style="width: 222px; height: 302px;">
<pre><strong>Input:</strong> n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
<strong>Output:</strong> true
</pre>
<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/12/tree2-graph.jpg" style="width: 382px; height: 222px;">
<pre><strong>Input:</strong> n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
<strong>Output:</strong> false
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>1 &lt;= n &lt;= 2000</code></li>
	<li><code>0 &lt;= edges.length &lt;= 5000</code></li>
	<li><code>edges[i].length == 2</code></li>
	<li><code>0 &lt;= a<sub>i</sub>, b<sub>i</sub> &lt; n</code></li>
	<li><code>a<sub>i</sub> != b<sub>i</sub></code></li>
	<li>There are no self-loops or repeated edges.</li>
</ul>

**Companies**:
[Google](https://leetcode.com/company/google), [Bloomberg](https://leetcode.com/company/bloomberg), [TikTok](https://leetcode.com/company/tiktok)

**Related Topics**:  
[Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Breadth-First Search](https://leetcode.com/tag/breadth-first-search/), [Union Find](https://leetcode.com/tag/union-find/), [Graph](https://leetcode.com/tag/graph/)

**Similar Questions**:
* [Course Schedule (Medium)](https://leetcode.com/problems/course-schedule/)
* [Number of Connected Components in an Undirected Graph (Medium)](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/)
* [Keys and Rooms (Medium)](https://leetcode.com/problems/keys-and-rooms/)

## Solution 1. Union Find


	Initialization: It initializes the Union-Find structure for n nodes, where each node is its own parent initially.
	Cycle Detection: As it processes each edge, it checks if the two nodes are already connected (indicating a cycle). If they are, it returns false.
	Union Operation: If the nodes are not connected, it merges their sets (connects them).
	Final Check: After processing all edges, it verifies that there is exactly one connected component (i.e., uf.getCount() == 1), indicating the graph is connected and acyclic, hence a valid tree.

* No cycle
* Single graph component


```cpp
// OJ: https://leetcode.com/problems/graph-valid-tree/
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N)

class UnionFind {
    vector<int> id; // Parent nodes
    int cnt; // Number of connected components
public:
    UnionFind(int N) : id(N), cnt(N) {
        iota(begin(id), end(id), 0); // Initialize parent nodes
    }
    int find(int x) {
        return id[x] == x ? x : (id[x] = find(id[x])); // Path compression
    }
    void connect(int a, int b) {
        id[find(a)] = find(b); // Union operation
        --cnt; // Decrement component count
    }
    bool connected(int a, int b) {
        return find(a) == find(b); // Check if two nodes are connected
    }
    int getCount() { return cnt; } // Get the number of components
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& E) {
        UnionFind uf(n); // Initialize Union-Find for n nodes
        for (auto &e : E) {
            if (uf.connected(e[0], e[1])) return false; // Cycle check
            uf.connect(e[0], e[1]); // Connect nodes
        }
        return uf.getCount() == 1; // Check if there's exactly one component
    }
};

```

## Solution 2. DFS

	Edge Count Check: It first verifies that the number of edges is exactly n - 1, which is a necessary condition for a tree.
	Graph Construction: It builds an adjacency list representation of the graph from the edge list.
	DFS for Cycle Detection: A DFS is initiated from the first node (node 0), marking nodes as visited. If it encounters a visited node that is not the parent of the current node, a cycle is detected.
	Connectivity Check: After the DFS, it checks if all nodes have been visited. If any node is unvisited, the graph is disconnected.
	Result: If no cycles are detected and all nodes are visited, the function returns true, confirming that the graph is a valid tree; otherwise, it returns false.

```cpp
// OJ: https://leetcode.com/problems/graph-valid-tree/
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N + E)
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& E) {
        if (E.size() != n - 1) return false; // A tree must have exactly n-1 edges
        
        vector<vector<int>> G(n);
        for (auto &e : E) {
            int u = e[0], v = e[1];
            G[u].push_back(v);
            G[v].push_back(u);
        }
        
        vector<int> visited(n, 0); // Track visited nodes
        
        function<bool(int, int)> dfs = [&](int u, int prev) {
            visited[u] = 1; // Mark the current node as visited
            for (int v : G[u]) {
                if (v == prev) continue; // Skip the parent node
                if (visited[v]) return false; // Cycle detected
                if (!dfs(v, u)) return false; // Visit neighbors
            }
            return true;
        };
        
        if (!dfs(0, -1)) return false; // Start DFS from node 0, check for cycles
        
        // Check if all nodes are visited
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) return false; // If any node is unvisited, the graph is disconnected
        }
        
        return true; // No cycles, and the graph is connected
    }
};

```

## Solution 3. BFS

	Graph Construction: It first constructs an adjacency list from the edge list to represent the graph.
	BFS Initialization: A queue is initialized with the first node (node 0), and a depth array is used to track the levels of each node (starting from 1).
	BFS Traversal: As it processes each node, it checks that neighboring nodes are at different levels (to prevent cycles). If a neighboring node is at the same level, it indicates a cycle, and the function returns false.
	Total Count Check: After the BFS, it counts the total number of visited nodes. If this count equals n, all nodes are connected, confirming the graph is a valid tree; otherwise, it returns false.

Starting from a random node, `0` for example:
* Can visit `n` nodes
* No cycle

```cpp
// OJ: https://leetcode.com/problems/graph-valid-tree/
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N + E)

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& E) {
        vector<vector<int>> G(n); // Adjacency list for the graph
        for (auto &e : E) {
            G[e[0]].push_back(e[1]); // Add edge in both directions
            G[e[1]].push_back(e[0]);
        }
        vector<int> depth(n); // Depth array to track visited nodes
        int level = 1, total = 0; // Level tracker and total visited nodes
        queue<int> q{{0}}; // Initialize queue with the first node

        while (q.size()) {
            int cnt = q.size(); // Number of nodes to process at current level
            total += cnt; // Count total visited nodes
            while (cnt--) {
                int u = q.front(); // Current node
                q.pop();
                depth[u] = level; // Mark depth of the current node
                for (int v : G[u]) {
                    if (depth[v] == depth[u]) return false; // Cycle check (same level)
                    if (depth[v] == 0) q.push(v); // Visit unvisited neighbors
                }
            }
            ++level; // Increment level after processing the current level
        }
        return total == n; // Check if all nodes were visited
    }
};

```

## Solution 4. Topological Sort (BFS)

	Edge Count Check: The function first verifies that the number of edges is exactly n−1n−1. If not, it returns false.
	Single Node Check: It immediately returns true for a graph with only one node, as a single node is trivially a valid tree.
	Graph Construction: It builds an adjacency list and a degree array to count the number of edges connected to each node.
	Leaf Node Processing: It enqueues all leaf nodes (nodes with a degree of 1). The algorithm processes these nodes, reducing the degree of their neighbors.
	Count Reduction: For each processed leaf node, it decrements the total node count (n). If a neighbor's degree becomes 1, it is enqueued as a new leaf.
	Final Check: After processing all reachable nodes, it checks if n equals 0. If so, it means all nodes have been connected and processed, confirming the graph is a valid tree; otherwise, it returns false.

```cpp
// OJ: https://leetcode.com/problems/graph-valid-tree
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N + E)

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& E) {
        if (E.size() != n - 1) return false; // Check if the number of edges is n-1
        if (n == 1) return true; // A single node is a valid tree
        vector<vector<int>> G(n); // Adjacency list for the graph
        vector<int> degree(n); // Degree array to track the number of connections

        for (auto &e : E) {
            int u = e[0], v = e[1];
            G[u].push_back(v); // Add edge in both directions
            G[v].push_back(u);
            ++degree[u]; // Increment degree for both nodes
            ++degree[v];
        }

        queue<int> q; // Queue for leaf nodes
        for (int i = 0; i < n; ++i) {
            if (degree[i] == 1) q.push(i); // Enqueue leaf nodes
        }

        while (q.size()) {
            int u = q.front(); // Process leaf node
            q.pop();
            --degree[u]; // Mark as processed
            --n; // Decrease the node count
            for (int v : G[u]) {
                if (--degree[v] == 1) q.push(v); // Enqueue new leaf nodes
            }
        }

        return n == 0; // Check if all nodes have been processed
    }
};

```
