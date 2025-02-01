# [100. Same Tree (Easy)](https://leetcode.com/problems/same-tree/)

<p>Given two binary trees, write a function to check if they are the same or not.</p>

<p>Two binary trees are considered the same if they are structurally identical and the nodes have the same value.</p>

<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong>     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

<strong>Output:</strong> true
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong>     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

<strong>Output:</strong> false
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong>     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

<strong>Output:</strong> false
</pre>


**Related Topics**:  
[Tree](https://leetcode.com/tag/tree/), [Depth-first Search](https://leetcode.com/tag/depth-first-search/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/same-tree/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(H)
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // If both trees are empty, they are the same
        if (!p && !q) return true;
        
        // If one tree is empty and the other is not, they are not the same
        if (!p || !q) return false;
        
        // If the current nodes have different values, the trees are not the same
        if (p->val != q->val) return false;
        
        // Recursively check the left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
```

## Solution 2. Iterative

```cpp
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode*> queue;
        queue.push(p);
        queue.push(q);
        
        while (!queue.empty()) {
            TreeNode* nodeP = queue.front(); queue.pop();
            TreeNode* nodeQ = queue.front(); queue.pop();
            
            // If both nodes are null, continue to the next pair
            if (!nodeP && !nodeQ) continue;
            
            // If one node is null and the other is not, the trees are not the same
            if (!nodeP || !nodeQ) return false;
            
            // If the current nodes have different values, the trees are not the same
            if (nodeP->val != nodeQ->val) return false;
            
            // Add the left and right children to the queue
            queue.push(nodeP->left);
            queue.push(nodeQ->left);
            queue.push(nodeP->right);
            queue.push(nodeQ->right);
        }
        
        return true;
    }
};

```
