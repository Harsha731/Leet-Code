# [2218. Maximum Value of K Coins From Piles (Hard)](https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/)

<p>There are <code>n</code> <strong>piles</strong> of coins on a table. Each pile consists of a <strong>positive number</strong> of coins of assorted denominations.</p>

<p>In one move, you can choose any coin on <strong>top</strong> of any pile, remove it, and add it to your wallet.</p>

<p>Given a list <code>piles</code>, where <code>piles[i]</code> is a list of integers denoting the composition of the <code>i<sup>th</sup></code> pile from <strong>top to bottom</strong>, and a positive integer <code>k</code>, return <em>the <strong>maximum total value</strong> of coins you can have in your wallet if you choose <strong>exactly</strong></em> <code>k</code> <em>coins optimally</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2019/11/09/e1.png" style="width: 600px; height: 243px;">
<pre><strong>Input:</strong> piles = [[1,100,3],[7,8,9]], k = 2
<strong>Output:</strong> 101
<strong>Explanation:</strong>
The above diagram shows the different ways we can choose k coins.
The maximum total we can obtain is 101.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
<strong>Output:</strong> 706
<strong>Explanation:
</strong>The maximum total can be obtained if we choose all coins from the last pile.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>n == piles.length</code></li>
	<li><code>1 &lt;= n &lt;= 1000</code></li>
	<li><code>1 &lt;= piles[i][j] &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= k &lt;= sum(piles[i].length) &lt;= 2000</code></li>
</ul>


**Companies**:  
[Google](https://leetcode.com/company/google)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Prefix Sum](https://leetcode.com/tag/prefix-sum/)

**Similar Questions**:
* [Coin Change (Medium)](https://leetcode.com/problems/coin-change/)
* [Coin Change 2 (Medium)](https://leetcode.com/problems/coin-change-2/)

## Solution 1. Top-down DP

Let `dp[i][j]` be the max value of `j` coins using piles `i ~ N-1`. The answer is `dp[0][k]`.

For `dp[i][j]`, we can try using `t` elements from `A[i]` (`0 <= t <= min(j, A[i].size())`), getting `A[i][0] + ... + A[i][t-1]` value plus `dp[i+1][j-t]` value (the max value of `j-t` coins using piles `i+1 ~ N-1`). We try different `t`s and assign the max value to `dp[i][j]`.

```
dp[i][j] = max( dp[i+1][j-t] + sum(i, t) | 0 <= t <= min(j, A[i].size()) )
            where sum(i, t) = A[i][0] + ... + A[i][t-1]
```

The trivial case is `dp[N][j] = 0`, i.e. we can't get any value from the nonexistent `A[N]`.

```cpp
// OJ: https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
// Author: github.com/lzl124631x
// Time: O(NM) where `M = sum(A[i].size())`
// Space: O(NK)

// dp[i][j] represents the maximum value achievable using the first i piles and j coins.

class Solution {
public:
    int solve(int i, int j, vector<vector<int>>& A, int m[1001][2001]) {
        if (i == A.size()) return 0; // Base case: no more piles
        if (m[i][j] != -1) return m[i][j]; // Return cached result

        int ans = solve(i + 1, j, A, m); // Option 1: skip the current pile
        int sum = 0;

        // Option 2: take coins from the current pile
        for (int t = 1; t <= j && t <= A[i].size(); ++t) {
            sum += A[i][t - 1]; // Add the value of the t-th coin in the pile
            ans = max(ans, solve(i + 1, j - t, A, m) + sum); // Recur for the remaining piles and coins
        }

        return m[i][j] = ans; // Cache and return the result
    }

    int maxValueOfCoins(vector<vector<int>>& A, int k) {
        int N = A.size();
        int m[1001][2001]; // Memoization table
        memset(m, -1, sizeof(m)); // Initialize the table with -1

        return solve(0, k, A, m); // Start the DP from the first pile and all k coins
    }
};
```

## Solution 2. Bottom-up DP

```cpp
// OJ: https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
// Author: github.com/lzl124631x
// Time: O(NK)
// Space: O(NK)
// dp[i][j] represents the maximum value achievable using the first i piles and j coins.

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& A, int K) {
        int N = A.size(), dp[1001][2001] = {}; 
        for (int i = 0; i < N; ++i) { 			// Iterate through each pile
            for (int k = 1; k <= K; ++k) {		 // Iterate through each possible number of coins
                dp[i + 1][k] = dp[i][k]; 		// Option 1: Skip the current pile
                for (int j = 0, sum = 0; j < k && j < A[i].size(); ++j) { 		// Option 2: Take coins from the current pile
                    sum += A[i][j]; // Add the value of the j-th coin
                    dp[i + 1][k] = max(dp[i + 1][k], sum + dp[i][k - j - 1]); // If we take till j=2 means, j=0,1,2. [3 coins]. So k - (j+1)
                }
            }
        }
        return dp[N][K]; // Return the result for N piles and K coins
    }
};
```

The space complexity can be reduced to `O(K)`.

```cpp
// OJ: https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
// Author: github.com/lzl124631x
// Time: O(NK)
// Space: O(K)

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& A, int K) {
        int N = A.size();
        vector<int> prev(K + 1, 0); // Represents dp[i-1][k]
        vector<int> curr(K + 1, 0); // Represents dp[i][k]

        for (int i = 0; i < N; ++i) { 
            for (int k = 1; k <= K; ++k) { 
                curr[k] = prev[k]; 
                for (int j = 0, sum = 0; j < k && j < A[i].size(); ++j) { 
                    sum += A[i][j]; 
                    curr[k] = max(curr[k], sum + prev[k - j - 1]); 
                }
            }
            prev = curr; // Update prev to curr for the next iteration
        }

        return prev[K]; 
    }
};
```

## Discuss

https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/discuss/1886910
