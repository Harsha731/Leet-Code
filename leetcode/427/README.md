# [427. Construct Quad Tree (Medium)](https://leetcode.com/problems/construct-quad-tree/)

<p>Given a <code>n * n</code> matrix <code>grid</code> of <code>0's</code> and <code>1's</code> only. We want to represent the <code>grid</code> with a Quad-Tree.</p>

<p>Return <em>the root of the Quad-Tree</em> representing the <code>grid</code>.</p>

<p>Notice that you can assign the value of a node to <strong>True</strong> or <strong>False</strong> when <code>isLeaf</code> is <strong>False</strong>, and both are <strong>accepted</strong> in the answer.</p>

<p>A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:</p>

<ul>
	<li><code>val</code>: True if the node represents a grid of 1's or False if the node represents a grid of 0's.&nbsp;</li>
	<li><code>isLeaf</code>: True if the node is leaf node on the tree or False if the node has the four children.</li>
</ul>

<pre>class Node {
    public boolean val;
&nbsp; &nbsp; public boolean isLeaf;
&nbsp; &nbsp; public Node topLeft;
&nbsp; &nbsp; public Node topRight;
&nbsp; &nbsp; public Node bottomLeft;
&nbsp; &nbsp; public Node bottomRight;
}</pre>

<p>We can construct a Quad-Tree from a two-dimensional area using the following steps:</p>

<ol>
	<li>If the current grid has the same value (i.e all <code>1's</code> or all <code>0's</code>)&nbsp;set <code>isLeaf</code>&nbsp;True and set <code>val</code> to the value of the grid and set the four children to Null and stop.</li>
	<li>If the current grid has different values, set <code>isLeaf</code> to False and&nbsp;set <code>val</code> to any value and divide the current grid into four sub-grids as shown in the photo.</li>
	<li>Recurse for each of the children with the proper sub-grid.</li>
</ol>
<img alt="" src="https://assets.leetcode.com/uploads/2020/02/11/new_top.png" style="width: 777px; height: 181px;">
<p>If you want to know more about the Quad-Tree, you can refer to the&nbsp;<a href="https://en.wikipedia.org/wiki/Quadtree">wiki</a>.</p>

<p><strong>Quad-Tree&nbsp;format:</strong></p>

<p>The output represents the serialized format of a Quad-Tree using level order traversal, where <code>null</code> signifies a path terminator where no node exists below.</p>

<p>It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list <code>[isLeaf, val]</code>.</p>

<p>If the value of <code>isLeaf</code> or <code>val</code> is True we represent it as <strong>1</strong> in the list&nbsp;<code>[isLeaf, val]</code> and if the value of <code>isLeaf</code> or <code>val</code> is False we represent it as <strong>0</strong>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/02/11/grid1.png" style="width: 777px; height: 99px;">
<pre><strong>Input:</strong> grid = [[0,1],[1,0]]
<strong>Output:</strong> [[0,1],[1,0],[1,1],[1,1],[1,0]]
<strong>Explanation:</strong> The explanation of this example is shown below:
Notice that 0 represnts False and 1 represents True in the photo representing the Quad-Tree.
<img alt="" src="https://assets.leetcode.com/uploads/2020/02/12/e1tree.png" style="width: 777px; height: 186px;">
</pre>

<p><strong>Example 2:</strong></p>

<p><img alt="" src="https://assets.leetcode.com/uploads/2020/02/12/e2mat.png" style="width: 777px; height: 343px;"></p>

<pre><strong>Input:</strong> grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
<strong>Output:</strong> [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
<strong>Explanation:</strong> All values in the grid are not the same. We divide the grid into four sub-grids.
The topLeft, bottomLeft and bottomRight each has the same value.
The topRight have different values so we divide it into 4 sub-grids where each has the same value.
Explanation is shown in the photo below:
<img alt="" src="https://assets.leetcode.com/uploads/2020/02/12/e2tree.png" style="width: 777px; height: 328px;">
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> grid = [[1,1],[1,1]]
<strong>Output:</strong> [[1,1]]
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> grid = [[0]]
<strong>Output:</strong> [[1,0]]
</pre>

<p><strong>Example 5:</strong></p>

<pre><strong>Input:</strong> grid = [[1,1,0,0],[1,1,0,0],[0,0,1,1],[0,0,1,1]]
<strong>Output:</strong> [[0,1],[1,1],[1,0],[1,0],[1,1]]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>n == grid.length == grid[i].length</code></li>
	<li><code>n == 2^x</code> where <code>0 &lt;= x &lt;= 6</code></li>
</ul>


**Companies**:  
[Uber](https://leetcode.com/company/uber)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Divide and Conquer](https://leetcode.com/tag/divide-and-conquer/), [Tree](https://leetcode.com/tag/tree/), [Matrix](https://leetcode.com/tag/matrix/)

## Solution 1. Solution 1

```cpp
// OJ: https://leetcode.com/problems/construct-quad-tree/
// Author: github.com/lzl124631x

/*
Time Complexity:
O(n^2 log n): This is because at each level of the recursion, we potentially process the entire grid (n^2 operations), 
and there are log n levels due to the division of the grid into quarters at each step.
Space Complexity:
O(n^2): In the worst case, every cell in the grid could be a leaf node in the Quad Tree, resulting in a space complexity 
of O(n^2). However, the recursion stack itself has a space complexity of O(log n) due to the recursive calls.
*/

class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        return construct(grid, 0, 0, grid.size());
    }

    Node* construct(vector<vector<int>>& grid, int x, int y, int length) {
        if (isSame(grid, x, y, length)) {
            return new Node(grid[x][y], true);
        } else {
            Node* node = new Node(false, false);
            node->topLeft = construct(grid, x, y, length / 2);
            node->topRight = construct(grid, x, y + length / 2, length / 2);
            node->bottomLeft = construct(grid, x + length / 2, y, length / 2);
            node->bottomRight = construct(grid, x + length / 2, y + length / 2, length / 2);
            return node;
        }
    }

    bool isSame(vector<vector<int>>& grid, int x, int y, int length) {
        int val = grid[x][y];
        for (int i = x; i < x + length; i++) {
            for (int j = y; j < y + length; j++) {
                if (grid[i][j] != val) return false;
            }
        }
        return true;
    }
};

```

## Solution 2. Optimized

```cpp
// OJ: https://leetcode.com/problems/construct-quad-tree/
// Author: github.com/lzl124631x

/*
Time Complexity:
O(n^2): Each cell in the grid is visited once during the construction process.
Space Complexity:
O(n^2): In the worst case, every cell could be a leaf node in the Quad Tree, resulting in a space complexity of O(n^2).
*/

class Solution {
public:
    // Start constructing the quad tree from the root node.
    Node* construct(vector<vector<int>>& grid) {
        return construct(grid, 0, 0, grid.size());
    }

    // Recursively construct the quad tree for a given sub-grid.
    Node* construct(vector<vector<int>>& grid, int x, int y, int length) {
        // Base case: If the sub-grid is a single cell, create a leaf node.
        if (length == 1) {
            return new Node(grid[x][y], true);
        } else {
            // Create a new internal node.
            Node* node = new Node(false, false);    // val, isLeaf

            // Recursively construct the four child nodes.
            Node* topLeft = construct(grid, x, y, length / 2);
            Node* topRight = construct(grid, x, y + length / 2, length / 2);
            Node* bottomLeft = construct(grid, x + length / 2, y, length / 2);
            Node* bottomRight = construct(grid, x + length / 2, y + length / 2, length / 2);

            // Check if all child nodes are leaf nodes with the same value.
            if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf &&
                topLeft->val == topRight->val && topLeft->val == bottomRight->val && topLeft->val == bottomLeft->val) {
                // If so, merge them into a single leaf node.
                node->isLeaf = true;
                node->val = topLeft->val;
            } else {
                // Otherwise, keep the child nodes as separate nodes.
                node->topLeft = topLeft;
                node->topRight = topRight;
                node->bottomLeft = bottomLeft;
                node->bottomRight = bottomRight;
            }
            return node;
        }
    }
};

```
