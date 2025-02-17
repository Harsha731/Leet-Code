# [1035. Uncrossed Lines (Medium)](https://leetcode.com/problems/uncrossed-lines/)

<p>We write the integers of <code>A</code> and <code>B</code>&nbsp;(in the order they are given) on two separate horizontal lines.</p>

<p>Now, we may draw <em>connecting lines</em>: a straight line connecting two numbers <code>A[i]</code> and <code>B[j]</code>&nbsp;such that:</p>

<ul>
	<li><code>A[i] == B[j]</code>;</li>
	<li>The line we draw does not intersect any other connecting (non-horizontal) line.</li>
</ul>

<p>Note that a connecting lines cannot intersect even at the endpoints:&nbsp;each number can only belong to one connecting line.</p>

<p>Return the maximum number of connecting lines we can draw in this way.</p>

<p>&nbsp;</p>

<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2019/04/26/142.png" style="width: 100px; height: 72px;">
<pre><strong>Input: </strong>A = <span id="example-input-1-1">[1,4,2]</span>, B = <span id="example-input-1-2">[1,2,4]</span>
<strong>Output: </strong><span id="example-output-1">2</span>
<strong>Explanation: </strong>We can draw 2 uncrossed lines as in the diagram.
We cannot draw 3 uncrossed lines, because the line from A[1]=4 to B[2]=4 will intersect the line from A[2]=2 to B[1]=2.
</pre>

<div>
<p><strong>Example 2:</strong></p>

<pre><strong>Input: </strong>A = <span id="example-input-2-1">[2,5,1,2,5]</span>, B = <span id="example-input-2-2">[10,5,2,1,5,2]</span>
<strong>Output: </strong><span id="example-output-2">3</span>
</pre>

<div>
<p><strong>Example 3:</strong></p>

<pre><strong>Input: </strong>A = <span id="example-input-3-1">[1,3,7,1,7,5]</span>, B = <span id="example-input-3-2">[1,9,2,5,1]</span>
<strong>Output: </strong><span id="example-output-3">2</span></pre>

<p>&nbsp;</p>
</div>
</div>

<p><strong>Note:</strong></p>

<ol>
	<li><code>1 &lt;= A.length &lt;= 500</code></li>
	<li><code>1 &lt;= B.length &lt;= 500</code></li>
	<li><code><font face="monospace">1 &lt;= A[i], B[i] &lt;= 2000</font></code></li>
</ol>


**Related Topics**:  
[Array](https://leetcode.com/tag/array/)

**Similar Questions**:
* [Edit Distance (Hard)](https://leetcode.com/problems/edit-distance/)

## Solution 1. DP
```cpp
class Solution {
public:
    int solve(int i, int j, vector<int>& A, vector<int>& B, vector<vector<int>>& memo) {
        if (i == 0 || j == 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        if (A[i - 1] == B[j - 1]) {
            memo[i][j] = 1 + solve(i - 1, j - 1, A, B, memo);
        } else {
            memo[i][j] = max(solve(i - 1, j, A, B, memo), solve(i, j - 1, A, B, memo));
        }
        return memo[i][j];
    }

    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int M = A.size(), N = B.size();
        vector<vector<int>> memo(M + 1, vector<int>(N + 1, -1));
        return solve(M, N, A, B, memo);
    }
};
```

## Solution 2. DP
This problem is equivalent to longest common subsequence.

Let `dp[i + 1][j + 1]` be the maximum number of connecting lines between `A[0..i]` and `B[0..j]`.

```
dp[i+1][j+1] = max( dp[i+1][j], dp[i][j+1] )         if A[i] != B[j]
               1 + dp[i][j]                          if A[i] == B[j]
dp[0][0] = 0
```

```cpp
// OJ: https://leetcode.com/problems/uncrossed-lines/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(MN)
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int M = A.size(), N = B.size();
        vector<vector<int>> dp(M + 1, vector<int>(N + 1));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i] == B[j]) dp[i + 1][j + 1] = 1 + dp[i][j];
                else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
        return dp[M][N];
    }
};
```

## Solution 2. DP + Space Optimization

```cpp
// OJ: https://leetcode.com/problems/uncrossed-lines/
// Author: github.com/lzl124631x
// Time: O(MN)
// Space: O(min(M, N))
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int M = A.size(), N = B.size();
        if (M < N) swap(M, N), swap(A, B);
        vector<int> dp(N + 1);
        for (int i = 0; i < M; ++i) {
            int prev = 0;
            for (int j = 0; j < N; ++j) {
                int cur = dp[j + 1];
                if (A[i] == B[j]) dp[j + 1] = 1 + prev;
                else dp[j + 1] = max(dp[j + 1], dp[j]);
                prev = cur;
            }
        }
        return dp[N];
    }
};
```
