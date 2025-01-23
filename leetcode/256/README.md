# [256. Paint House (Easy)](https://leetcode.com/problems/paint-house/)

<p>There are a row of <i>n</i> houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.</p>

<p>The cost of painting each house with a certain color is represented by a <code><i>n</i> x <i>3</i></code> cost matrix. For example, <code>costs[0][0]</code> is the cost of painting house 0 with color red; <code>costs[1][2]</code> is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.</p>

<p><b>Note:</b><br>
All costs are positive integers.</p>

<p><strong>Example:</strong></p>

<pre><strong>Input:</strong> [[17,2,17],[16,16,5],[14,3,19]]
<strong>Output:</strong> 10
<strong>Explanation: </strong>Paint house 0 into blue, paint house 1 into green, paint house 2 into blue. 
&nbsp;            Minimum cost: 2 + 5 + 3 = 10.
</pre>


**Companies**:  
[LinkedIn](https://leetcode.com/company/linkedin)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [House Robber (Easy)](https://leetcode.com/problems/house-robber/)
* [House Robber II (Medium)](https://leetcode.com/problems/house-robber-ii/)
* [Paint House II (Hard)](https://leetcode.com/problems/paint-house-ii/)
* [Paint Fence (Easy)](https://leetcode.com/problems/paint-fence/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/paint-house/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        for (int i = 1; i < costs.size(); ++i) {
            for (int j = 0; j < 3; ++j) costs[i][j] += min(costs[i - 1][(j + 1) % 3], costs[i - 1][(j + 2) % 3]);
        }
        return *min_element(costs.back().begin(), costs.back().end());
    }
};
```

## Solution 2. Space Optimization

```cpp
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;

        int prev0 = costs[0][0];
        int prev1 = costs[0][1];
        int prev2 = costs[0][2];

        for (int i = 1; i < n; ++i) {
            int curr0 = costs[i][0] + min(prev1, prev2);
            int curr1 = costs[i][1] + min(prev0, prev2);
            int curr2 = costs[i][2] + min(prev0, prev1);

            prev0 = curr0;
            prev1 = curr1;
            prev2 = curr2;
        }

        return min({prev0, prev1, prev2});
    }
};
```

## Solution 3. Memoization

```cpp
class Solution {
public:
    int solve(int i, int j, vector<vector<int>>& costs, vector<vector<int>>& dp) {
        int n = costs.size();
        if (i >= n) return 0; // Base case: no more houses to paint
        if (dp[i][j] != -1) return dp[i][j]; // Return memoized result if available

        // Calculate the minimum cost for the next house with a different color
        int nextCost1 = solve(i + 1, (j + 1) % 3, costs, dp); // Choose next color 1
        int nextCost2 = solve(i + 1, (j + 2) % 3, costs, dp); // Choose next color 2

        // Store the result in the memoization table
        dp[i][j] = costs[i][j] + min(nextCost1, nextCost2);
        return dp[i][j];
    }

    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;

        // Initialize memoization table with -1
        vector<vector<int>> dp(n, vector<int>(3, -1));

        // Calculate the minimum cost for the first house with each color
        int cost1 = solve(0, 0, costs, dp); // Start with color 0
        int cost2 = solve(0, 1, costs, dp); // Start with color 1
        int cost3 = solve(0, 2, costs, dp); // Start with color 2

        // Return the minimum cost among the three choices
        return min({cost1, cost2, cost3});
    }
};
```
