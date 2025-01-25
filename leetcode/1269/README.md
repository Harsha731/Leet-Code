# [1269. Number of Ways to Stay in the Same Place After Some Steps (Hard)](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)

<p>You have a pointer at index <code>0</code> in an array of size <code><font face="monospace">arrLen</font></code>. At each step, you can move 1 position to the left, 1 position to the right&nbsp;in the array or stay in the same place&nbsp; (The pointer should not be placed outside the array at any time).</p>

<p>Given two integers&nbsp;<code>steps</code> and <code>arrLen</code>, return the number of&nbsp;ways such that your pointer still at index <code>0</code> after <strong>exactly </strong><code><font face="monospace">steps</font></code>&nbsp;steps.</p>

<p>Since the answer&nbsp;may be too large,&nbsp;return it <strong>modulo</strong>&nbsp;<code>10^9 + 7</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> steps = 3, arrLen = 2
<strong>Output:</strong> 4
<strong>Explanation: </strong>There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> steps = 2, arrLen = 4
<strong>Output:</strong> 2
<strong>Explanation:</strong> There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> steps = 4, arrLen = 2
<strong>Output:</strong> 8
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= steps &lt;= 500</code></li>
	<li><code>1 &lt;= arrLen&nbsp;&lt;= 10^6</code></li>
</ul>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. Memoization

```cpp
// OJ: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
// Author: github.com/lzl124631x
/*
Time complexity: O(n⋅min(n,m))
There can be steps values of remain and min(steps, arrLen) values of curr. The reason curr is limited by steps 
is because if we were to only move right, we would eventually run out of moves. Thus, there are O(n⋅min(n,m)) 
states of curr, remain. Due to memoization, we never calculate a state more than once. To calculate a given 
state costs O(1) as we are simply adding up three options.
Space complexity: O(n⋅min(n,m))
The recursion call stack uses up to O(n) space, but this is dominated by memo which has a size of O(n⋅min(n,m))
*/

class Solution {
public:
    vector<vector<int>> dp;
    const int MOD = 1e9 + 7;
    int n;

    int solve(int i, int k) {
        if (k == 0) return i == 0 ? 1 : 0;
        if (dp[i][k] != -1) return dp[i][k];
        int ans = solve(i, k - 1);
        if (i > 0) ans = (ans + solve(i - 1, k - 1)) % MOD;
        if (i < n - 1) ans = (ans + solve(i + 1, k - 1)) % MOD;
        dp[i][k] = ans;
        return ans;
    }

    int numWays(int steps, int arrLen) {
        n = min(arrLen, steps);
        dp = vector<vector<int>>(n, vector<int>(steps + 1, -1));
        return solve(0, steps);
    }
};
```

## Solution 2. Tabulation

```cpp

/*
Given n as steps and m as arrLen,
Time complexity: O(n⋅min(n,m))
Our nested for-loops iterate over O(n⋅min(n,m)) states of curr, remain. Calculating each state is done in O(1).
Space complexity: O(n⋅min(n,m))
dp has a size of O(n⋅min(n,m)).
*/

class Solution {
public:
    int numWays(int steps, int arrLen) {
        int n = min(arrLen, steps + 1);
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(steps + 1, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int k = 1; k <= steps; ++k) {
            for (int i = 0; i < n; ++i) {
                dp[k][i] = dp[k - 1][i];
                if (i > 0) {
                    dp[k][i] = (dp[k][i] + dp[k - 1][i - 1]) % MOD;
                }
                if (i < n - 1) {
                    dp[k][i] = (dp[k][i] + dp[k - 1][i + 1]) % MOD;
                }
            }
        }

        return dp[steps][0];
    }
};
```

## Solution 3. Space Optimization

```cpp
// OJ: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
// Author: github.com/lzl124631x
Given n as steps and m as arrLen,
/*
Time complexity: O(n⋅min(n,m))
Our nested for-loops iterate over O(n⋅min(n,m)) states of curr, remain. Calculating each state is done in O(1).
Space complexity: O(min(n,m))
dp and prevDp have a size of O(min(n,m)).
*/
class Solution {
public:
    int numWays(int steps, int arrLen) {
        int n = min(arrLen, steps + 1);
        const int MOD = 1e9 + 7;
        vector<int> prev(n, 0);
        prev[0] = 1;

        for (int k = 1; k <= steps; ++k) {
            vector<int> curr(n, 0);
            for (int i = 0; i < n; ++i) {
                curr[i] = prev[i];
                if (i > 0) {
                    curr[i] = (curr[i] + prev[i - 1]) % MOD;
                }
                if (i < n - 1) {
                    curr[i] = (curr[i] + prev[i + 1]) % MOD;
                }
            }
            prev = curr;
        }

        return prev[0];
    }
};
```
