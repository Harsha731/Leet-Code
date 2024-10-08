# [785. Is Graph Bipartite? (Medium)](https://leetcode.com/problems/is-graph-bipartite/)

<p>There is an <strong>undirected</strong> graph with <code>n</code> nodes, where each node is numbered between <code>0</code> and <code>n - 1</code>. You are given a 2D array <code>graph</code>, where <code>graph[u]</code> is an array of nodes that node <code>u</code> is adjacent to. More formally, for each <code>v</code> in <code>graph[u]</code>, there is an undirected edge between node <code>u</code> and node <code>v</code>. The graph has the following properties:</p>

<ul>
	<li>There are no self-edges (<code>graph[u]</code> does not contain <code>u</code>).</li>
	<li>There are no parallel edges (<code>graph[u]</code> does not contain duplicate values).</li>
	<li>If <code>v</code> is in <code>graph[u]</code>, then <code>u</code> is in <code>graph[v]</code> (the graph is undirected).</li>
	<li>The graph may not be connected, meaning there may be two nodes <code>u</code> and <code>v</code> such that there is no path between them.</li>
</ul>

<p>A graph is <strong>bipartite</strong> if the nodes can be partitioned into two independent sets <code>A</code> and <code>B</code> such that <strong>every</strong> edge in the graph connects a node in set <code>A</code> and a node in set <code>B</code>.</p>

<p>Return <code>true</code><em> if and only if it is <strong>bipartite</strong></em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/21/bi2.jpg" style="width: 222px; height: 222px;">
<pre><strong>Input:</strong> graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
<strong>Output:</strong> false
<strong>Explanation:</strong> There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.</pre>

<p><strong>Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/10/21/bi1.jpg" style="width: 222px; height: 222px;">
<pre><strong>Input:</strong> graph = [[1,3],[0,2],[1,3],[0,2]]
<strong>Output:</strong> true
<strong>Explanation:</strong> We can partition the nodes into two sets: {0, 2} and {1, 3}.</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>graph.length == n</code></li>
	<li><code>1 &lt;= n &lt;= 100</code></li>
	<li><code>0 &lt;= graph[u].length &lt; n</code></li>
	<li><code>0 &lt;= graph[u][i] &lt;= n - 1</code></li>
	<li><code>graph[u]</code>&nbsp;does not contain&nbsp;<code>u</code>.</li>
	<li>All the values of <code>graph[u]</code> are <strong>unique</strong>.</li>
	<li>If <code>graph[u]</code> contains <code>v</code>, then <code>graph[v]</code> contains <code>u</code>.</li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [LinkedIn](https://leetcode.com/company/linkedin), [Google](https://leetcode.com/company/google), [ByteDance](https://leetcode.com/company/bytedance)

**Related Topics**:  
[Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Breadth-First Search](https://leetcode.com/tag/breadth-first-search/), [Union Find](https://leetcode.com/tag/union-find/), [Graph](https://leetcode.com/tag/graph/)

## Solution 1. DFS

	Graph Representation: Use an adjacency list to represent the graph as a vector of vectors.
	Coloring States: Maintain a vector id to track the coloring of each node:
	    0 for unvisited,     1 for one color,     -1 for the other color.
	DFS Function: Implement a recursive DFS function that:
	    Colors the current node.
	    Checks adjacent nodes to ensure they are colored with the opposite color.
	    Returns false if a conflict in coloring is found.
	Graph Traversal: Iterate through each node in the graph:
	    If unvisited, initiate a DFS call from that node to attempt coloring.
	Final Result: Return true if all nodes can be properly colored; return false if any DFS call indicates a conflict in coloring.

```cpp
// OJ: https://leetcode.com/problems/is-graph-bipartite/
// Author: github.com/lzl124631x
// Time: O(V + E)
// Space: O(V + E)

class Solution {
public:
    // Function to perform DFS and check for bipartiteness
    bool dfs(int u, int color, vector<int>& id, const vector<vector<int>>& G) {
        // If the node has been colored, check if it matches the expected color
        if (id[u]) return id[u] == color;
        // Color the node
        id[u] = color;
        // Check all adjacent nodes
        for (int v : G[u]) {
            // Recursively attempt to color the adjacent node with the opposite color
            if (!dfs(v, -color, id, G)) return false;
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& G) {
        int N = G.size();
        vector<int> id(N); // 0 = unseen, 1 = color 1, -1 = color 2
        for (int i = 0; i < N; ++i) {
            // If the node hasn't been colored, start DFS from it
            if (!id[i] && !dfs(i, 1, id, G)) return false;
        }
        return true; // If all nodes can be colored correctly, the graph is bipartite
    }
};

```

## Solution 2. BFS
	
	Initialization: Create an array id to track the color of each node (unseen as 0, color 1 or -1).
	BFS Traversal: For each unvisited node, initiate a BFS.
	    Assign the starting node a color (e.g., 1).
	    Use a queue to explore all connected nodes.
	Coloring Neighbors: For each current node, check its neighbors:
	    If a neighbor is uncolored, assign it the opposite color and enqueue it.
	    If a neighbor is already colored, check for conflicts (if it’s the same color as the current node).
	Conflict Detection: If a conflict is found, return false.
	Completion: If all nodes are processed without conflicts, return true, indicating the graph is bipartite.

```cpp
// OJ: https://leetcode.com/problems/is-graph-bipartite/
// Author: github.com/lzl124631x
// Time: O(V + E)
// Space: O(V + E)

class Solution {
public:
    bool isBipartite(vector<vector<int>>& G) {
        int N = G.size();
        vector<int> id(N); // 0: unseen, 1 and -1: different colors
        queue<int> q; // Queue for BFS
        for (int i = 0; i < N; ++i) {
            if (id[i]) continue; // Skip already colored nodes
            q.push(i);
            id[i] = 1; // Color the starting node
            while (q.size()) {
                int u = q.front(); // Current node
                q.pop();
                for (int v : G[u]) { // Check adjacent nodes
                    if (id[v]) {
                        if (id[v] != -id[u]) return false; // Conflict in coloring
                        continue;
                    }
                    id[v] = -id[u]; // Color adjacent node
                    q.push(v);
                }
            }
        }
        return true; // Graph is bipartite
    }
};

```
