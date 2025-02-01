# [450. Delete Node in a BST (Medium)](https://leetcode.com/problems/delete-node-in-a-bst/)

<p>Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.</p>

<p>Basically, the deletion can be divided into two stages:</p>

<ol>
	<li>Search for a node to remove.</li>
	<li>If the node is found, delete the node.</li>
</ol>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/09/04/del_node_1.jpg" style="width: 800px; height: 214px;">
<pre><strong>Input:</strong> root = [5,3,6,2,4,null,7], key = 3
<strong>Output:</strong> [5,4,6,2,null,null,7]
<strong>Explanation:</strong> Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
<img alt="" src="https://assets.leetcode.com/uploads/2020/09/04/del_node_supp.jpg" style="width: 350px; height: 255px;">
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> root = [5,3,6,2,4,null,7], key = 0
<strong>Output:</strong> [5,3,6,2,4,null,7]
<strong>Explanation:</strong> The tree does not contain a node with value = 0.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> root = [], key = 0
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li>The number of nodes in the tree is in the range <code>[0, 10<sup>4</sup>]</code>.</li>
	<li><code>-10<sup>5</sup> &lt;= Node.val &lt;= 10<sup>5</sup></code></li>
	<li>Each node has a <strong>unique</strong> value.</li>
	<li><code>root</code> is a valid binary search tree.</li>
	<li><code>-10<sup>5</sup> &lt;= key &lt;= 10<sup>5</sup></code></li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up:</strong> Could you solve it with time complexity <code>O(height of tree)</code>?</p>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [LinkedIn](https://leetcode.com/company/linkedin), [Apple](https://leetcode.com/company/apple), [Google](https://leetcode.com/company/google), [Oracle](https://leetcode.com/company/oracle), [Facebook](https://leetcode.com/company/facebook)

**Related Topics**:  
[Tree](https://leetcode.com/tag/tree/), [Binary Search Tree](https://leetcode.com/tag/binary-search-tree/), [Binary Tree](https://leetcode.com/tag/binary-tree/)

**Similar Questions**:
* [Split BST (Medium)](https://leetcode.com/problems/split-bst/)

## Solution 1. Recursive

```cpp
// OJ: https://leetcode.com/problems/delete-node-in-a-bst/
// Author: github.com/lzl124631x
// Time: O(H)
// Space: O(H)
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;

        if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            // Case when the node to be deleted is found
            if (!root->right && !root->left) {
                return NULL;
            } else if (!root->right) {
                return root->left;
            } else if (!root->left) {
                return root->right;
            } else {
                TreeNode* temp = root->right;
                while (temp->left) {
                    temp = temp->left;
                }
                temp->left = root->left;
                return root->right;
            }
        }
        return root;
    }
};
```

## Solution 2. Iterative

```cpp
// OJ: https://leetcode.com/problems/delete-node-in-a-bst/
// Author: github.com/lzl124631x
// Time: O(H)
// Space: O(H)

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // Base case: If the tree is empty, return NULL
        if (!root) return NULL;

        TreeNode* parent = NULL; // Parent of the node to be deleted
        TreeNode* curr = root; // Current node being processed

        // Traverse the tree to find the node with the given key
        while (curr && curr->val != key) {
            parent = curr; // Update parent pointer
            if (key < curr->val) curr = curr->left; // Move left if key is smaller
            else curr = curr->right; // Move right if key is larger
        }

        // If the key is not found, return the original tree
        if (!curr) return root;

        // Handle different cases for deleting the node
        if (!curr->right && !curr->left) {
            // Case 1: Node has no children (leaf node)
            if (!parent) return NULL; // Deleting the root node
            if (parent->left == curr) parent->left = NULL; // Remove from parent's left
            else parent->right = NULL; // Remove from parent's right
            delete curr; // Free memory
            return root;
        } else if (!curr->right) {
            // Case 2: Node has only a left child
            if (!parent) return curr->left; // Deleting the root node
            if (parent->left == curr) parent->left = curr->left; // Replace with left child
            else parent->right = curr->left; // Replace with left child
            delete curr; // Free memory
            return root;
        } else if (!curr->left) {
            // Case 3: Node has only a right child
            if (!parent) return curr->right; // Deleting the root node
            if (parent->left == curr) parent->left = curr->right; // Replace with right child
            else parent->right = curr->right; // Replace with right child
            delete curr; // Free memory
            return root;
        } else {
            // Case 4: Node has both left and right children
            // Find the in-order successor (smallest node in the right subtree)
            TreeNode* temp = curr->right;
            while (temp->left) {
                temp = temp->left; // Move to the smallest node
            }
            // Attach the left child of the node to be deleted to the in-order successor
            temp->left = curr->left;
            if (!parent) return curr->right; // Deleting the root node
            if (parent->left == curr) parent->left = curr->right; // Replace with right subtree
            else parent->right = curr->right; // Replace with right subtree
            delete curr; // Free memory
            return root;
        }
    }
};

```

