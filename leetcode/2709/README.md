# [2709. Greatest Common Divisor Traversal (Hard)](https://leetcode.com/problems/greatest-common-divisor-traversal)

<p>You are given a <strong>0-indexed</strong> integer array <code>nums</code>, and you are allowed to <strong>traverse</strong> between its indices. You can traverse between index <code>i</code> and index <code>j</code>, <code>i != j</code>, if and only if <code>gcd(nums[i], nums[j]) &gt; 1</code>, where <code>gcd</code> is the <strong>greatest common divisor</strong>.</p>

<p>Your task is to determine if for <strong>every pair</strong> of indices <code>i</code> and <code>j</code> in nums, where <code>i &lt; j</code>, there exists a <strong>sequence of traversals</strong> that can take us from <code>i</code> to <code>j</code>.</p>

<p>Return <code>true</code><em> if it is possible to traverse between all such pairs of indices,</em><em> or </em><code>false</code><em> otherwise.</em></p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [2,3,6]
<strong>Output:</strong> true
<strong>Explanation:</strong> In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
To go from index 0 to index 1, we can use the sequence of traversals 0 -&gt; 2 -&gt; 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 &gt; 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 &gt; 1.
To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 &gt; 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 &gt; 1.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [3,9,5]
<strong>Output:</strong> false
<strong>Explanation:</strong> No sequence of traversals can take us from index 0 to index 2 in this example. So, we return false.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [4,3,12,8]
<strong>Output:</strong> true
<strong>Explanation:</strong> There are 6 possible pairs of indices to traverse between: (0, 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3). A valid sequence of traversals exists for each pair, so we return true.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>5</sup></code></li>
</ul>


**Related Topics**:  
[Array](https://leetcode.com/tag/array), [Math](https://leetcode.com/tag/math), [Union Find](https://leetcode.com/tag/union-find), [Number Theory](https://leetcode.com/tag/number-theory)

**Similar Questions**:
* [Graph Connectivity With Threshold (Hard)](https://leetcode.com/problems/graph-connectivity-with-threshold)

**Hints**:
* Create a (prime) factor-numbers list for all the indices.
* Add an edge between the neighbors of the (prime) factor-numbers list. The order of the numbers doesn’t matter. We only need edges between 2 neighbors instead of edges for all pairs.
* The problem is now similar to checking if all the numbers (nodes of the graph) are in the same connected component.
* Any algorithm (i.e., BFS, DFS, or Union-Find Set) should work to find or check connected components

## Solution 1.
	
	Union-Find Structure: The UnionFind class is initialized to manage connected components, allowing efficient union and find operations to determine if two indices are connected.
	
	Finding Factors: The factors function extracts all prime factors of a given number. These factors are used to establish connections between numbers in the main array.
	
	Connecting Indices:
	
	    For each number in the array, the code retrieves its factors.
	    It uses a hashmap to track the first occurrence of each factor and connects the current index to this first index using the union-find structure.
	
	Final Check: After processing all numbers, the method checks if there is only one connected component in the union-find structure. If there is only one component, it means all numbers can be traversed through shared factors; hence it returns true. If there are multiple components, it returns false.

```cpp
// OJ: https://leetcode.com/problems/greatest-common-divisor-traversal
// Author: github.com/lzl124631x
// Time: O(NlogN * Sqrt(D)) where D is the maximum number in `A`
// Space: O(N)
class UnionFind {
    vector<int> id; // Array to track the parent of each node
    int cnt; // Number of connected components
public:
    UnionFind(int n) : id(n), cnt(n) {
        iota(begin(id), end(id), 0); // Initialize the union-find structure
    }

    int find(int a) {
        return id[a] == a ? a : (id[a] = find(id[a])); // Path compression
    }

    void connect(int a, int b) {
        int p = find(a), q = find(b);
        if (p == q) return; // Already connected
        id[p] = q; // Union operation
        --cnt; // Decrease the number of components
    }

    int count() { return cnt; } // Return the number of connected components
};

class Solution {
    vector<int> factors(int n) {
        vector<int> ans;
        for (int d = 2; d * d <= n; ++d) {
            if (n % d == 0) ans.push_back(d); // Add factor to list
            while (n % d == 0) n /= d; // Remove all instances of the factor
        }
        if (n > 1) ans.push_back(n); // Add the remaining prime factor
        return ans;
    }

public:
    bool canTraverseAllPairs(vector<int>& A) {
        unordered_map<int, int> m; // Map from a factor to the index of the first number containing this factor
        int N = A.size();
        UnionFind uf(N); // Create union-find for all numbers
        for (int i = 0; i < N; ++i) {
            for (int f : factors(A[i])) { // Get factors of A[i]
                if (m.count(f) == 0) m[f] = i; // Store the first occurrence of the factor
                uf.connect(i, m[f]); // Connect numbers sharing a factor
            }
        }
        return uf.count() == 1; // Check if all numbers are connected
    }
};

```
