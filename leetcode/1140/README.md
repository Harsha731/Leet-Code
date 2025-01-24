# [1140. Stone Game II (Medium)](https://leetcode.com/problems/stone-game-ii/)

<p>Alex&nbsp;and Lee continue their&nbsp;games with piles of stones.&nbsp; There are a number of&nbsp;piles&nbsp;<strong>arranged in a row</strong>, and each pile has a positive integer number of stones&nbsp;<code>piles[i]</code>.&nbsp; The objective of the game is to end with the most&nbsp;stones.&nbsp;</p>

<p>Alex and Lee take turns, with Alex starting first.&nbsp; Initially, <code>M = 1</code>.</p>

<p>On each player's turn, that player&nbsp;can take <strong>all the stones</strong> in the <strong>first</strong> <code>X</code> remaining piles, where <code>1 &lt;= X &lt;= 2M</code>.&nbsp; Then, we set&nbsp;<code>M = max(M, X)</code>.</p>

<p>The game continues until all the stones have been taken.</p>

<p>Assuming Alex and Lee play optimally, return the maximum number of stones Alex can get.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> piles = [2,7,9,4,4]
<strong>Output:</strong> 10
<strong>Explanation:</strong>  If Alex takes one pile at the beginning, Lee takes two piles, then Alex takes 2 piles again. Alex can get 2 + 4 + 4 = 10 piles in total. If Alex takes two piles at the beginning, then Lee can take all three piles left. In this case, Alex get 2 + 7 = 9 piles in total. So we return 10 since it's larger. 
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= piles.length &lt;= 100</code></li>
	<li><code>1 &lt;= piles[i]&nbsp;&lt;= 10 ^ 4</code></li>
</ul>

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. DP Tabulation

Let `dp[i][m]` be optimal result Alex can get on subarray `A[i..(N-1)]` and with inital `M = m`. It's a `pair<int, int>` where the first element is the stones Alex can get and the second is the stones Lee can get.

```
dp[i][m] = <p.second + A[i] + ... + A[i + x - 1], p.first>
           where p = dp[i + x][max(m, x)], 1 <= x <= 2m
```

The answer is `dp[0][1].first`.

```cpp

Time Complexity: O(N^3): Each subproblem (i, j) is computed once, and there are 0(N^2) subproblems. For each
subproblem, we iterate over 0(N) possible moves.
Space Complexity: O(N^2): The memo table uses 0(N^2) space, and the recursion stack can go up to 0(N) depth.

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>>dp(n + 1, vector<int>(n + 1,0));
        vector<int> sufsum (n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            sufsum[i] = sufsum[i + 1] + piles[i];
        }
        for (int i = 0; i <= n; i++) {
            dp[i][n] = sufsum[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 1; j--) {
                for (int X = 1; X <= 2 * j && i + X <= n; X++) {
                    dp[i][j] = max(dp[i][j], sufsum[i] - dp[i + X][max(j, X)]);
                }
            }
        }
        return dp[0][1];
    }
};
```

## Solution 2. DP Memoization

```cpp
class Solution {
    vector<vector<int>> memo;
    vector<int> sufsum;

    int solve(int i, int j) {
        if (i >= sufsum.size() - 1) return 0; // Base case: no piles left
        if (memo[i][j] != -1) return memo[i][j]; // Return cached result
        if (i + 2 * j >= sufsum.size() - 1) return sufsum[i]; // Take all remaining piles

        int res = 0;
        for (int X = 1; X <= 2 * j; X++) {
            res = max(res, sufsum[i] - solve(i + X, max(j, X))); // Maximize current player's stones
        }
        return memo[i][j] = res; 
    }

public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        memo.assign(n + 1, vector<int>(n + 1, -1)); 
        sufsum.assign(n + 1, 0); 

        for (int i = n - 1; i >= 0; i--) {
            sufsum[i] = sufsum[i + 1] + piles[i];
        }

        return solve(0, 1); // Start from the first pile with M = 1
    }
};
```
