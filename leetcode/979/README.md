# [979. Distribute Coins in Binary Tree (Medium)](https://leetcode.com/problems/distribute-coins-in-binary-tree/)

<p>Given the <code>root</code> of a binary tree with <code>N</code> nodes, each <code>node</code>&nbsp;in the tree has <code>node.val</code> coins, and there are <code>N</code> coins total.</p>

<p>In one move, we may choose two adjacent nodes and move one coin from one node to another.&nbsp; (The move may be from parent to child, or from child to parent.)</p>

<p>Return the number of moves required to make every node have exactly one coin.</p>

<p>&nbsp;</p>

<div>
<p><strong>Example 1:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2019/01/18/tree1.png" style="width: 150px; height: 142px;"></strong></p>

<pre><strong>Input: </strong><span id="example-input-1-1">[3,0,0]</span>
<strong>Output: </strong><span id="example-output-1">2</span>
<strong>Explanation: </strong>From the root of the tree, we move one coin to its left child, and one coin to its right child.
</pre>

<div>
<p><strong>Example 2:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2019/01/18/tree2.png" style="width: 150px; height: 142px;"></strong></p>

<pre><strong>Input: </strong><span id="example-input-2-1">[0,3,0]</span>
<strong>Output: </strong><span id="example-output-2">3</span>
<strong>Explanation: </strong>From the left child of the root, we move two coins to the root [taking two moves].  Then, we move one coin from the root of the tree to the right child.
</pre>

<div>
<p><strong>Example 3:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2019/01/18/tree3.png" style="width: 150px; height: 142px;"></strong></p>

<pre><strong>Input: </strong><span id="example-input-3-1">[1,0,2]</span>
<strong>Output: </strong><span id="example-output-3">2</span>
</pre>

<div>
<p><strong>Example 4:</strong></p>

<p><strong><img alt="" src="https://assets.leetcode.com/uploads/2019/01/18/tree4.png" style="width: 155px; height: 156px;"></strong></p>

<pre><strong>Input: </strong><span id="example-input-4-1">[1,0,0,null,3]</span>
<strong>Output: </strong><span id="example-output-4">4</span>
</pre>

<p>&nbsp;</p>

<p><strong><span>Note:</span></strong></p>

<ol>
	<li><code>1&lt;= N &lt;= 100</code></li>
	<li><code>0 &lt;= node.val &lt;= N</code></li>
</ol>
</div>
</div>
</div>
</div>

**Companies**:  
[Google](https://leetcode.com/company/google), [Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[Tree](https://leetcode.com/tag/tree/), [Depth-first Search](https://leetcode.com/tag/depth-first-search/)

**Similar Questions**:
* [Sum of Distances in Tree (Hard)](https://leetcode.com/problems/sum-of-distances-in-tree/)
* [Binary Tree Cameras (Hard)](https://leetcode.com/problems/binary-tree-cameras/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/distribute-coins-in-binary-tree/
// Author: github.com/lzl124631x
class Solution {
public:
    int moves = 0;

    int dfs(TreeNode* node){
        if(!node) return 0;

        int left_excess = dfs(node->left);
        int right_excess = dfs(node->right);

        moves += abs(left_excess) + abs(right_excess);

        return (node->val) + left_excess + right_excess - 1;
    }

    int distributeCoins(TreeNode* root) {
        dfs(root);      
        return moves;
    }
};

/*
Time complexity: O(n)
Traversing the tree using DFS costs O(n), as we visit each node exactly once and perform O(1) of work at each visit.
Space complexity: O(n)
The space complexity of DFS, when implemented recursively, is determined by the maximum depth of the call stack, 
which corresponds to the depth of the tree. In the worst case, if the tree is entirely unbalanced (e.g., a linked list 
or a left/right skewed tree), the call stack can grow as deep as the number of nodes, resulting in a space complexity of O(n).
*/
```
