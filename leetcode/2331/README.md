# [2331. Evaluate Boolean Binary Tree (Easy)](https://leetcode.com/problems/evaluate-boolean-binary-tree)

<p>You are given the <code>root</code> of a <strong>full binary tree</strong> with the following properties:</p>

<ul>
	<li><strong>Leaf nodes</strong> have either the value <code>0</code> or <code>1</code>, where <code>0</code> represents <code>False</code> and <code>1</code> represents <code>True</code>.</li>
	<li><strong>Non-leaf nodes</strong> have either the value <code>2</code> or <code>3</code>, where <code>2</code> represents the boolean <code>OR</code> and <code>3</code> represents the boolean <code>AND</code>.</li>
</ul>

<p>The <strong>evaluation</strong> of a node is as follows:</p>

<ul>
	<li>If the node is a leaf node, the evaluation is the <strong>value</strong> of the node, i.e. <code>True</code> or <code>False</code>.</li>
	<li>Otherwise, <strong>evaluate</strong> the node's two children and <strong>apply</strong> the boolean operation of its value with the children's evaluations.</li>
</ul>

<p>Return<em> the boolean result of <strong>evaluating</strong> the </em><code>root</code><em> node.</em></p>

<p>A <strong>full binary tree</strong> is a binary tree where each node has either <code>0</code> or <code>2</code> children.</p>

<p>A <strong>leaf node</strong> is a node that has zero children.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2022/05/16/example1drawio1.png" style="width: 700px; height: 252px;">
<pre><strong>Input:</strong> root = [2,1,3,null,null,0,1]
<strong>Output:</strong> true
<strong>Explanation:</strong> The above diagram illustrates the evaluation process.
The AND node evaluates to False AND True = False.
The OR node evaluates to True OR False = True.
The root node evaluates to True, so we return true.</pre>

<p><strong class="example">Example 2:</strong></p>

<pre><strong>Input:</strong> root = [0]
<strong>Output:</strong> false
<strong>Explanation:</strong> The root node is a leaf node and it evaluates to false, so we return false.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[1, 1000]</code>.</li>
	<li><code>0 &lt;= Node.val &lt;= 3</code></li>
	<li>Every node has either <code>0</code> or <code>2</code> children.</li>
	<li>Leaf nodes have a value of <code>0</code> or <code>1</code>.</li>
	<li>Non-leaf nodes have a value of <code>2</code> or <code>3</code>.</li>
</ul>


**Companies**:
[Google](https://leetcode.com/company/google)

**Related Topics**:  
[Tree](https://leetcode.com/tag/tree/), [Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Binary Tree](https://leetcode.com/tag/binary-tree/)

**Similar Questions**:
* [Check If Two Expression Trees are Equivalent (Medium)](https://leetcode.com/problems/check-if-two-expression-trees-are-equivalent/)
* [Design an Expression Tree With Evaluate Function (Medium)](https://leetcode.com/problems/design-an-expression-tree-with-evaluate-function/)
* [Minimum Flips in Binary Tree to Get Result (Medium)](https://leetcode.com/problems/minimum-flips-in-binary-tree-to-get-result/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/evaluate-boolean-binary-tree
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(H)
class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        if (!root->left && !root->right) return root->val;
        bool left = evaluateTree(root->left), right = evaluateTree(root->right);
        return root->val == 2 ? (left || right) : (left && right);
    }
};
```

## Solution 2. Short Circuit

```cpp
// OJ: https://leetcode.com/problems/evaluate-boolean-binary-tree
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(H)
class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        if (!root->left && !root->right) return root->val;
        bool left = evaluateTree(root->left);
        if (root->val == 2 && left) return true;
        if (root->val == 3 && !left) return false;
        return evaluateTree(root->right);
    }
};
```

## Solution 3. Stack

```cpp
class Solution {
public:
    bool evaluateTree(TreeNode* r) {
        stack<TreeNode*> s;
        s.push(r);
        unordered_map<TreeNode*, bool> m;

        while (!s.empty()) {
            TreeNode* n = s.top();

            // If the node is a leaf node, store its value in the map
            if (!n->left && !n->right) {
                s.pop();
                m[n] = n->val;
                continue;
            }

            // If both children have already been evaluated, use their values to evaluate the current node.
            if (m.find(n->left) != m.end() && m.find(n->right) != m.end()) {
                s.pop();
                if (n->val == 2) {
                    m[n] = m[n->left] || m[n->right];
                } else {
                    m[n] = m[n->left] && m[n->right];
                }
            } else {
                // If both children are not leaf nodes, push the current node
                // along with its left and right child back into the stack.
                s.push(n->right);
                s.push(n->left);
            }
        }

        return m[r] == 1;
    }
};

```
