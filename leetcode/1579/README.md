# [1579. Remove Max Number of Edges to Keep Graph Fully Traversable (Hard)](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)

<p>Alice and Bob have an undirected graph of&nbsp;<code>n</code>&nbsp;nodes&nbsp;and 3 types of edges:</p>

<ul>
	<li>Type 1: Can be traversed by Alice only.</li>
	<li>Type 2: Can be traversed by Bob only.</li>
	<li>Type 3: Can by traversed by both Alice and Bob.</li>
</ul>

<p>Given an array&nbsp;<code>edges</code>&nbsp;where&nbsp;<code>edges[i] = [type<sub>i</sub>, u<sub>i</sub>, v<sub>i</sub>]</code>&nbsp;represents a bidirectional edge of type&nbsp;<code>type<sub>i</sub></code>&nbsp;between nodes&nbsp;<code>u<sub>i</sub></code>&nbsp;and&nbsp;<code>v<sub>i</sub></code>, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.</p>

<p>Return <em>the maximum number of edges you can remove, or return</em> <code>-1</code> <em>if it's impossible for the graph to be fully traversed by Alice and Bob.</em></p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/08/19/ex1.png" style="width: 179px; height: 191px;"></strong></p>

<pre><strong>Input:</strong> n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
<strong>Output:</strong> 2
<strong>Explanation: </strong>If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
</pre>

<p><strong>Example 2:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/08/19/ex2.png" style="width: 178px; height: 190px;"></strong></p>

<pre><strong>Input:</strong> n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
<strong>Output:</strong> 0
<strong>Explanation: </strong>Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
</pre>

<p><strong>Example 3:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2020/08/19/ex3.png" style="width: 178px; height: 190px;"></strong></p>

<pre><strong>Input:</strong> n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
<strong>Output:</strong> -1
<b>Explanation: </b>In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.</pre>

<p>&nbsp;</p>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 10^5</code></li>
	<li><code>1 &lt;= edges.length &lt;= min(10^5, 3 * n * (n-1) / 2)</code></li>
	<li><code>edges[i].length == 3</code></li>
	<li><code>1 &lt;= edges[i][0] &lt;= 3</code></li>
	<li><code>1 &lt;= edges[i][1] &lt; edges[i][2] &lt;= n</code></li>
	<li>All tuples&nbsp;<code>(type<sub>i</sub>, u<sub>i</sub>, v<sub>i</sub>)</code>&nbsp;are distinct.</li>
</ul>


**Related Topics**:  
[Union Find](https://leetcode.com/tag/union-find/)

## Solution 1. Union Find

	Union-Find Initialization: Two Union-Find structures are created to manage connections between nodes, one for type 1 edges (Alice's edges) and one for type 2 edges (Bob's edges).
	
	Processing Type 3 Edges: The algorithm first processes edges of type 3, which can connect any two nodes. If two nodes are already connected, the edge is counted as removable. Otherwise, the nodes are connected in both Union-Find structures.
	
	Processing Type 1 and Type 2 Edges: Next, the algorithm processes type 1 and type 2 edges. If an edge connects two already connected nodes, it is counted as removable. If not, it connects the nodes in the respective Union-Find structure.
	
	Final Connectivity Check: Finally, the algorithm checks if both Union-Find structures indicate a single connected component. If either structure indicates multiple components, it returns -1 (indicating the graph is not fully connected). Otherwise, it returns the count of removable edges.

Create two UnionFinds `a` and `b` for Alice and Bob respectively.

We should take type 3 edges first, then type 1 and 2.

If two nodes are already connected, we increment the answer `ans`. Otherwise we connect them.

In the end, if `a.getSize() == 1 && b.size() == 1` meaning that the graph is all connected for both Alice and Bob, we return `ans`; otherwise return `-1`.

```cpp
// OJ: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
// Author: github.com/lzl124631x
// Time: O(N + E)
// Space: O(N)
class UnionFind {
    vector<int> id; // Array to hold the parent of each node
    int size; // Number of connected components
public:
    UnionFind(int N) : id(N), size(N) {
        iota(begin(id), end(id), 0); // Initialize the union-find structure
    }
    
    int find(int a) {
        return id[a] == a ? a : (id[a] = find(id[a])); // Path compression
    }
    
    int connected(int a, int b) {
        return find(a) == find(b); // Check if two nodes are connected
    }
    
    void connect(int a, int b) {
        int p = find(a), q = find(b);
        if (p == q) return; // No need to connect if already connected
        id[p] = q; // Union operation
        --size; // Reduce the number of components
    }
    
    int getSize() { return size; } // Return the number of connected components
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& E) {
        UnionFind a(n), b(n); // UnionFind instances for type 1 and 2 edges
        int ans = 0; // Counter for removable edges

        // Process type 3 edges (which can connect any two nodes)
        for (auto &e : E) {
            if (e[0] != 3) continue; // Only process type 3 edges
            int u = e[1] - 1, v = e[2] - 1;
            if (a.connected(u, v)) { // If already connected, increment removable counter
                ++ans;
                continue;
            }
            a.connect(u, v); // Connect the nodes in both UnionFind instances
            b.connect(u, v);
        }

        // Process type 1 and type 2 edges
        for (auto &e : E) {
            int u = e[1] - 1, v = e[2] - 1;
            if (e[0] == 1) {
                if (a.connected(u, v)) ++ans; // Increment counter if already connected
                else a.connect(u, v); // Connect the nodes
            } else if (e[0] == 2) {
                if (b.connected(u, v)) ++ans; // Same for type 2 edges
                else b.connect(u, v);
            }
        }

        // Check if both graphs are fully connected
        return a.getSize() != 1 || b.getSize() != 1 ? -1 : ans; // Return -1 if not connected, else return removable edge count
    }
};

```
