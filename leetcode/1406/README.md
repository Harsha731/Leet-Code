# [1406. Stone Game III (Hard)](https://leetcode.com/problems/stone-game-iii/)

<p>Alice and Bob continue their&nbsp;games with piles of stones. There are several stones&nbsp;<strong>arranged in a row</strong>, and each stone has an associated&nbsp;value which is an integer given in the array&nbsp;<code>stoneValue</code>.</p>

<p>Alice and Bob take turns, with <strong>Alice</strong> starting first. On each player's turn, that player&nbsp;can take <strong>1, 2 or 3 stones</strong>&nbsp;from&nbsp;the <strong>first</strong> remaining stones in the row.</p>

<p>The score of each player is the sum of values of the stones taken. The score of each player is <strong>0</strong>&nbsp;initially.</p>

<p>The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.</p>

<p>Assume&nbsp;Alice&nbsp;and Bob&nbsp;<strong>play optimally</strong>.</p>

<p>Return <em>"Alice"</em> if&nbsp;Alice will win, <em>"Bob"</em> if Bob will win or <em>"Tie"</em> if they end the game with the same score.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> values = [1,2,3,7]
<strong>Output:</strong> "Bob"
<strong>Explanation:</strong> Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> values = [1,2,3,-9]
<strong>Output:</strong> "Alice"
<strong>Explanation:</strong> Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. The next move Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. The next move Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> values = [1,2,3,6]
<strong>Output:</strong> "Tie"
<strong>Explanation:</strong> Alice cannot win this game. She can end the game in a draw if she decided to choose all the first three piles, otherwise she will lose.
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> values = [1,2,3,-1,-2,-3,7]
<strong>Output:</strong> "Alice"
</pre>

<p><strong>Example 5:</strong></p>

<pre><strong>Input:</strong> values = [-1,-2,-3]
<strong>Output:</strong> "Tie"
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= values.length &lt;= 50000</code></li>
	<li><code>-1000&nbsp;&lt;= values[i] &lt;= 1000</code></li>
</ul>

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. DP

This problem is similar to [1140. Stone Game II](https://leetcode.com/problems/stone-game-ii/).

For each round, my best option in this turn must be the worst option of the other player in the next turn.

Let `dp[i]` be the best result the current player can get at this `i`th element.

```
dp[i] = max(
            A[i] - dp[i+1],                    // If I only pick one
            A[i] + A[i+1] - dp[i+2]            // If I pick two
            A[i] + A[i+1] + A[i+2] - dp[i+3]   // If I pick three
)
```

So we can compute `dp[i]` from the end of the array. `dp[i] = 0` if `i >= N`.

```cpp
// OJ: https://leetcode.com/problems/stone-game-iii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    string stoneGameIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> dp(n + 1, INT_MIN); // dp[i] stores the maximum score difference the player can achieve starting from index i
        dp[n] = 0; // Base case: no stones left, score difference is 0

        // Process the array from right to left
        for (int i = n - 1; i >= 0; --i) {
            int currentSum = 0;

            // The player can pick 1 stone
            currentSum += stones[i];
            dp[i] = max(dp[i], currentSum - dp[i + 1]);

            // The player can pick 2 stones
            if (i + 1 < n) {
                currentSum += stones[i + 1];
                dp[i] = max(dp[i], currentSum - dp[i + 2]);
            }

            // The player can pick 3 stones
            if (i + 2 < n) {
                currentSum += stones[i + 2];
                dp[i] = max(dp[i], currentSum - dp[i + 3]);
            }
        }

        // Determine the result based on dp[0]
        if (dp[0] > 0) return "Alice";
        else if (dp[0] < 0) return "Bob";
        else return "Tie";
    }
};
```

## Solution 2. DP + Space Optimization

Since `dp[i]` is only dependent to the next 3 `dp` values. We can reduce the `dp` array side from `N` to `4`.

```cpp
// OJ: https://leetcode.com/problems/stone-game-iii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    string stoneGameIII(vector<int>& stones) {
        int n = stones.size();
        int dp1 = 0, dp2 = 0, dp3 = 0; // Variables to store dp[i + 1], dp[i + 2], dp[i + 3]
        int currentDP = 0; // Variable to store dp[i]

        // Process the array from right to left
        for (int i = n - 1; i >= 0; --i) {
            int currentSum = 0;
            currentSum += stones[i]; // Pick 1 stone
            currentDP = currentSum - dp1; // Update dp[i]

            if (i + 1 < n) { // Pick 2 stones
                currentSum += stones[i + 1];
                currentDP = max(currentDP, currentSum - dp2);
            }

            if (i + 2 < n) { // Pick 3 stones
                currentSum += stones[i + 2];
                currentDP = max(currentDP, currentSum - dp3);
            }

            // Shift the variables for the next iteration
            dp3 = dp2;
            dp2 = dp1;
            dp1 = currentDP;
        }

        // Determine the result based on dp[0] (stored in dp1)
        if (dp1 > 0) return "Alice";
        else if (dp1 < 0) return "Bob";
        else return "Tie";
    }
};
```

## Solution 3. Memoization
```cpp
class Solution {
    vector<int> memo;

    int solve(int i, vector<int>& stones) {
        int n = stones.size();
        if (i >= n) return 0; // Base case: no stones left
        if (memo[i] != INT_MIN) return memo[i]; // Return cached result

        int currentSum = 0;
        int maxDiff = INT_MIN;

        // Pick 1 stone
        currentSum += stones[i];
        maxDiff = max(maxDiff, currentSum - solve(i + 1, stones));

        // Pick 2 stones (if possible)
        if (i + 1 < n) {
            currentSum += stones[i + 1];
            maxDiff = max(maxDiff, currentSum - solve(i + 2, stones));
        }

        // Pick 3 stones (if possible)
        if (i + 2 < n) {
            currentSum += stones[i + 2];
            maxDiff = max(maxDiff, currentSum - solve(i + 3, stones));
        }

        return memo[i] = maxDiff; // Cache and return the result
    }

public:
    string stoneGameIII(vector<int>& stones) {
        int n = stones.size();
        memo.assign(n, INT_MIN); // Initialize memoization table with INT_MIN

        int result = solve(0, stones); // Start solving from the first stone

        // Determine the result based on the computed score difference
        if (result > 0) return "Alice";
        else if (result < 0) return "Bob";
        else return "Tie";
    }
};
```
