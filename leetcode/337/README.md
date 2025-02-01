# [337. House Robber III (Medium)](https://leetcode.com/problems/house-robber-iii/)

<p>The thief has found himself a new place for his thievery again. There is only one entrance to this area, called <code>root</code>.</p>

<p>Besides the <code>root</code>, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if <strong>two directly-linked houses were broken into on the same night</strong>.</p>

<p>Given the <code>root</code> of the binary tree, return <em>the maximum amount of money the thief can rob <strong>without alerting the police</strong></em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/10/rob1-tree.jpg" style="width: 277px; height: 293px;">
<pre><strong>Input:</strong> root = [3,2,3,null,3,null,1]
<strong>Output:</strong> 7
<strong>Explanation:</strong> Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
</pre>

<p><strong>Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/10/rob2-tree.jpg" style="width: 357px; height: 293px;">
<pre><strong>Input:</strong> root = [3,4,5,1,3,null,1]
<strong>Output:</strong> 9
<strong>Explanation:</strong> Maximum amount of money the thief can rob = 4 + 5 = 9.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[1, 10<sup>4</sup>]</code>.</li>
	<li><code>0 &lt;= Node.val &lt;= 10<sup>4</sup></code></li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Google](https://leetcode.com/company/google), [Microsoft](https://leetcode.com/company/microsoft)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Tree](https://leetcode.com/tag/tree/), [Depth-First Search](https://leetcode.com/tag/depth-first-search/), [Binary Tree](https://leetcode.com/tag/binary-tree/)

**Similar Questions**:
* [House Robber (Medium)](https://leetcode.com/problems/house-robber/)
* [House Robber II (Medium)](https://leetcode.com/problems/house-robber-ii/)

```cpp
// Brute Force

class Solution {
public:
    int rob(TreeNode* root) {
        if(!root) return 0;
        int dontRob = rob(root -> left) + rob(root -> right), robRoot = root -> val;
        if(root -> left) robRoot += rob(root -> left -> left) + rob(root -> left -> right);
        if(root -> right) robRoot += rob(root -> right -> left) + rob(root -> right -> right);
        return max(dontRob, robRoot);
    }
};
```
```cpp
// Better

class Solution {
public:
    unordered_map<TreeNode*, int> dp;
    int rob(TreeNode* root) {
        if(!root) return 0;
        if(dp.count(root)) return dp[root];
        int dontRob = rob(root -> left) + rob(root -> right), robRoot = root -> val;
        if(root -> left) robRoot += rob(root -> left -> left) + rob(root -> left -> right);
        if(root -> right) robRoot += rob(root -> right -> left) + rob(root -> right -> right);
        return dp[root] = max(dontRob, robRoot);
    }
};
```


## Solution 3. DP

At each node, we have two options, rob or skip.

If we rob it, the best we can get is `node->val + skip(node->left) + skip(node->right)` where `skip(x)` means the best outcome we can get if we skip node  `x`.

If we skip it, the best we can get is `best(node->left) + best(node->right)`, where `best(x)` means the best outcome we can get at node `x` (`best(x) = max(rob(x), skip(x))`).

So we can do a postorder traversal and return a pair of `rob(x)` and `skip(x)` at each node `x`.

```cpp
// OJ: https://leetcode.com/problems/house-robber-iii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(H)

// Optimal

class Solution {
public:
    int rob(TreeNode* root) {
        auto result = robHelper(root);
        return max(result.first, result.second);
    }

private:
    // Returns pair {rob_current_node, skip_current_node}
    pair<int, int> robHelper(TreeNode* node) {
        if (!node) return {0, 0};
        
        auto left = robHelper(node->left);
        auto right = robHelper(node->right);
        
        int rob = node->val + left.second + right.second;
        int skip = max(left.first, left.second) + max(right.first, right.second);
        
        return {rob, skip};
    }
};

```

## Solution 4. DP - No need

When doing post-order traversal, return a pair of numbers indicating:
1. the maximum value we can get at the current node, including both rob and skip.
2. the maximum value we can get if we skip the current node.

```cpp
// OJ: https://leetcode.com/problems/house-robber-iii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(H)
class Solution {
    pair<int, int> dfs(TreeNode* root) {
        if (!root) return {0, 0};
        auto left = dfs(root->left), right = dfs(root->right);
        int prev = left.first + right.first;
        return { max(root->val + left.second + right.second, prev), prev };
    }
public:
    int rob(TreeNode* root) {
        return dfs(root).first;
    }
};
```
