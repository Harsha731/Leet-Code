# [879. Profitable Schemes (Hard)](https://leetcode.com/problems/profitable-schemes/)

<p>There is a group of <code>n</code> members, and a list of various crimes they could commit. The <code>i<sup>th</sup></code> crime generates a <code>profit[i]</code> and requires <code>group[i]</code> members to participate in it. If a member participates in one crime, that member can't participate in another crime.</p>

<p>Let's call a <strong>profitable scheme</strong> any subset of these crimes that generates at least <code>minProfit</code> profit, and the total number of members participating in that subset of crimes is at most <code>n</code>.</p>

<p>Return the number of schemes that can be chosen. Since the answer may be very large, <strong>return it modulo</strong> <code>10<sup>9</sup> + 7</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> n = 5, minProfit = 3, group = [2,2], profit = [2,3]
<strong>Output:</strong> 2
<strong>Explanation:</strong> To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
<strong>Output:</strong> 7
<strong>Explanation:</strong> To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 100</code></li>
	<li><code>0 &lt;= minProfit &lt;= 100</code></li>
	<li><code>1 &lt;= group.length &lt;= 100</code></li>
	<li><code>1 &lt;= group[i] &lt;= 100</code></li>
	<li><code>profit.length == group.length</code></li>
	<li><code>0 &lt;= profit[i] &lt;= 100</code></li>
</ul>


**Companies**:  
[Google](https://leetcode.com/company/google)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. Top-down DP

Let `dp(i,j,k)` be the number of profitable schemas using crimes whose indexes are in range `[i, M)`, `j` member allowance, and `k` as profit goal (i.e. minimum total profit).

```
dp(i, j, k) = dp(i+1, j, k)                    // skip crime `i`
              dp(i+1, j-group[i], k-profit[i]) // use crime `i`
```

Special cases:
* `dp(i, j, k) = 0` if `j < 0` (no member allowance)
* If `i == M`, `dp(i, j, k) = k <= 0 ? 1 : 0` (If profit goal `<= 0`, it's achievable)

Note that when `k < 0`, we need to do `k = max(0, k)` because negative profit goal has the same schema as `0` profit goal.

```cpp
// OJ: https://leetcode.com/problems/profitable-schemes/
// Author: github.com/lzl124631x
// Time: O(MNP) where `M` is the number of crimes, `N` is the number of members, and `P` is `minProfit`
// Space: O(MNP)
// When committing a crime, the profit gained can exceed the required profit (k), and the code uses 
// max(0, k - profitGained) to ensure that any excess profit is treated as if the requirement is already met.
// If minProfit = 5, and a scheme achieves 7 profit, it will still be counted in dp[i][j][5] because 7 ≥ 5.
// (i, j, k) => (crimeIndex, membersLeft, profitNeeded)

class Solution {
private:
    long mod = 1e9 + 7; 
    long dp[101][101][101]; // DP table for memoization

    long countSchemes(int i, int j, int k, vector<int>& group, vector<int>& profit) {

        if (j < 0) return 0L; // If we don't have enough members, return 0
        
        if (i == group.size()) return k <= 0 ? 1L : 0L; // If the profit goal is not positive, it's achievable and we return 1; otherwise, return 0.

        k = max(0, k); // Negative profit goal is the same as 0 profit goal         
        // This is done for storing it in the dp[][][] vector

        if (dp[i][j][k] != -1) return dp[i][j][k]; // Return memoized result

        return dp[i][j][k] = (countSchemes(i + 1, j, k, group, profit) + countSchemes(i + 1, j - group[i], k - profit[i], group, profit)) % mod; 
        // skip crime `i` or pick crime `i`.
    }

public:
    int profitableSchemes(int N, int minProfit, vector<int>& group, vector<int>& profit) {

        int M = group.size();
        memset(dp, -1, sizeof(dp)); // Initialize DP table with -1

        return countSchemes(0, N, minProfit, group, profit); // Start DFS from the first crime, all members, and the minimum profit goal
    }
};
```

## Solution 2. Bottom-up DP

```cpp
// OJ: https://leetcode.com/problems/profitable-schemes/
// Author: github.com/lzl124631x
// Time: O(MNP)
// Space: O(MNP)
class Solution {
public:
    int profitableSchemes(int N, int minProfit, vector<int>& group, vector<int>& profit) {
        const long MOD = 1e9 + 7;
        int M = group.size();

        // DP table: dp[crimeIndex][membersLeft][profitNeeded]
        long dp[101][101][101] = {0};

        // Base case: 1 way to achieve 0 profit with 0 members and 0 crimes
        dp[0][0][0] = 1;

        // Fill the DP table
        for (int i = 1; i <= M; i++) { // Iterate over crimes
            int membersRequired = group[i - 1];
            int profitGained = profit[i - 1];

            for (int j = 0; j <= N; j++) { // Iterate over members, 0 members is also possible in dp table
                for (int k = 0; k <= minProfit; k++) { // Iterate over profit,  0 profit is also possible in dp table. But i=0 crime is not, so keep it 0.
                    // Option 1: Skip the current crime
                    dp[i][j][k] = dp[i - 1][j][k];

                    // Option 2: Commit the current crime (if enough members are available)
                    if (j >= membersRequired) {
                        int remainingMembers = j - membersRequired;
                        int remainingProfit = max(0, k - profitGained);     // Important
                        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][remainingMembers][remainingProfit]) % MOD;
                    }
                }
            }
        }

        // Sum all valid schemes with at least `minProfit` and at most `N` members
        long result = 0;
        for (int j = 0; j <= N; j++) {
            result = (result + dp[M][j][minProfit]) % MOD;
        }

        return result;
    }
};
```

Since `dp[i+1]` values only depends on `dp[i]`, we can reduce the space complexity to `O(NP)`.

```cpp
// OJ: https://leetcode.com/problems/profitable-schemes/
// Author: github.com/lzl124631x
// Time: O(MNP)
// Space: O(NP)

class Solution {
public:
    int profitableSchemes(int N, int minProfit, vector<int>& group, vector<int>& profit) {
        const long MOD = 1e9 + 7;
        int M = group.size();

        // prev[j][k]: Number of ways to achieve at least k profit using j members (for the previous crime)
        // curr[j][k]: Number of ways to achieve at least k profit using j members (for the current crime)
        long prev[101][101] = {0};
        long curr[101][101] = {0};

        // Base case: 1 way to achieve 0 profit with 0 members
        prev[0][0] = 1;

        // Fill the DP table
        for (int i = 1; i <= M; i++) { // Iterate over crimes
            int membersRequired = group[i - 1];
            int profitGained = profit[i - 1];

            // Reset curr for the current crime
            for (int j = 0; j <= N; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    // Option 1: Skip the current crime
                    curr[j][k] = prev[j][k];

                    // Option 2: Commit the current crime (if enough members are available)
                    if (j >= membersRequired) {
                        int remainingMembers = j - membersRequired;
                        int remainingProfit = max(0, k - profitGained);
                        curr[j][k] = (curr[j][k] + prev[remainingMembers][remainingProfit]) % MOD;
                    }
                }
            }

            // Update prev to curr for the next iteration
            for (int j = 0; j <= N; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    prev[j][k] = curr[j][k];
                }
            }
        }

        // Sum all valid schemes with at least `minProfit` and at most `N` members
        long result = 0;
        for (int j = 0; j <= N; j++) {
            result = (result + prev[j][minProfit]) % MOD;
        }

        return result;
    }
};

```
