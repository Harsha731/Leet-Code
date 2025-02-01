# [894. All Possible Full Binary Trees (Medium)](https://leetcode.com/problems/all-possible-full-binary-trees)

<p>Given an integer <code>n</code>, return <em>a list of all possible <strong>full binary trees</strong> with</em> <code>n</code> <em>nodes</em>. Each node of each tree in the answer must have <code>Node.val == 0</code>.</p>
<p>Each element of the answer is the root node of one possible tree. You may return the final list of trees in <strong>any order</strong>.</p>
<p>A <strong>full binary tree</strong> is a binary tree where each node has exactly <code>0</code> or <code>2</code> children.</p>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://s3-lc-upload.s3.amazonaws.com/uploads/2018/08/22/fivetrees.png" style="width: 700px; height: 400px;">
<pre><strong>Input:</strong> n = 7
<strong>Output:</strong> [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> n = 3
<strong>Output:</strong> [[0,0,0]]
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>1 &lt;= n &lt;= 20</code></li>
</ul>

**Companies**:
[Adobe](https://leetcode.com/company/adobe), [Amazon](https://leetcode.com/company/amazon), [Google](https://leetcode.com/company/google)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Tree](https://leetcode.com/tag/tree/), [Recursion](https://leetcode.com/tag/recursion/), [Memoization](https://leetcode.com/tag/memoization/), [Binary Tree](https://leetcode.com/tag/binary-tree/)

## Solution 1. Memoization

```cpp
// OJ: https://leetcode.com/problems/all-possible-full-binary-trees/
// Author: github.com/lzl124631x
// Time: O(2^(N/2))
// Space: O(N * 2^N)
class Solution {
    unordered_map<int, vector<TreeNode*>> m;
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        if (n % 2 == 0) return {};
	// A full binary tree is a tree where every node has either 0 or 2 children.
        if (n == 1) return { new TreeNode() };
        if (m.count(n)) return m[n];
        vector<TreeNode*> ans;
        for (int i = 1; i < n; i += 2) {
            auto left = allPossibleFBT(i);
            auto right = allPossibleFBT(n - i - 1);
            for (auto L : left) {
                for (auto R : right) {
                    auto root = new TreeNode(0, L, R);
                    ans.push_back(root);
                }
            }
        }
        return m[n] = ans;
    }
};
```

## Solution 2. Iterative

```cpp
class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        if (n % 2 == 0) return {}; // No full binary trees can be formed with an even number of nodes.

        // Map to store results for different node counts
        unordered_map<int, vector<TreeNode*>> m;
        m[1] = { new TreeNode() }; // Base case: one node tree

        // Iterate over odd numbers from 3 to n
        for (int nodes = 3; nodes <= n; nodes += 2) {
            vector<TreeNode*> ans;
            // Split the nodes into left and right subtrees
            for (int leftNodes = 1; leftNodes < nodes; leftNodes += 2) {
                int rightNodes = nodes - leftNodes - 1; // Remaining nodes for the right subtree
                for (auto L : m[leftNodes]) {
                    for (auto R : m[rightNodes]) {
                        ans.push_back(new TreeNode(0, L, R)); // Create a new root with left and right subtrees
                    }
                }
            }
            m[nodes] = ans; // Store the result for this number of nodes
        }

        return m[n]; // Return the result for n nodes
    }
};

```
