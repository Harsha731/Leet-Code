# [1029. Two City Scheduling (Medium)](https://leetcode.com/problems/two-city-scheduling/)

<p>A company is planning to interview <code>2n</code> people. Given the array <code>costs</code> where <code>costs[i] = [aCost<sub>i</sub>, bCost<sub>i</sub>]</code>,&nbsp;the cost of flying the <code>i<sup>th</sup></code> person to city <code>a</code> is <code>aCost<sub>i</sub></code>, and the cost of flying the <code>i<sup>th</sup></code> person to city <code>b</code> is <code>bCost<sub>i</sub></code>.</p>

<p>Return <em>the minimum cost to fly every person to a city</em> such that exactly <code>n</code> people arrive in each city.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> costs = [[10,20],[30,200],[400,50],[30,20]]
<strong>Output:</strong> 110
<strong>Explanation: </strong>
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
<strong>Output:</strong> 1859
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> costs = [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
<strong>Output:</strong> 3086
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>2 * n == costs.length</code></li>
	<li><code>2 &lt;= costs.length &lt;= 100</code></li>
	<li><code>costs.length</code> is even.</li>
	<li><code>1 &lt;= aCost<sub>i</sub>, bCost<sub>i</sub> &lt;= 1000</code></li>
</ul>


**Companies**:  
[Bloomberg](https://leetcode.com/company/bloomberg)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Greedy](https://leetcode.com/tag/greedy/), [Sorting](https://leetcode.com/tag/sorting/)

## Solution 1. Bottom-up DP

Let `dp[i + 1][j]` be the min cost arranging the first `i + 1` people and when `j` of them go to city A, `0 <= i < N, 0 <= j <= i + 1`.

For `dp[i + 1][j]`, we have two options:
* The `i`-th person goes to city A. We get `dp[i][j - 1] + A[i][0]` (`j - 1 >= 0`).
* The `i`-th person goes to city B. We get `dp[i][j] + A[i][1]` (`j <= i`).

```
dp[i + 1][j] = min(
                    j - 1 >= 0 ? dp[i][j - 1] + A[i][0] : INF,       // the i-th person goes to city A
                    j <= i ? dp[i][j] + A[i][1] : INF                // the i-th person goes to city B
                  )
dp[0][0] = 0
```

The answer is `dp[2N][N]`.

```cpp
// OJ: https://leetcode.com/problems/two-city-scheduling/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N^2)
// Half to A, Half to B

class Solution {
    public:
        int twoCitySchedCost(vector<vector<int>>& costs) {
            int n = costs.size() / 2;
            vector<vector<int>> dp(2 * n + 1, vector<int>(n + 1, INT_MAX));
            dp[0][0] = 0;
    
            for (int i = 0; i < 2 * n; ++i) {
                for (int j = 0; j <= min(i + 1, n); ++j) {
                    // Cost of sending the ith person to city A
                    int costA = (j > 0) ? dp[i][j - 1] + costs[i][0] : INT_MAX;
                    
                    // Cost of sending the ith person to city B
                    int costB = (j <= i) ? dp[i][j] + costs[i][1] : INT_MAX;
    
                    dp[i + 1][j] = min(costA, costB);
                }
            }
    
            return dp[2 * n][n];
        }
    };
```

## Solution 2. DP with Space Optimization

```cpp
// OJ: https://leetcode.com/problems/two-city-scheduling/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N)
class Solution {
    public:
        int twoCitySchedCost(vector<vector<int>>& costs) {
            int n = costs.size() / 2;
            vector<int> prev(n + 1, INT_MAX);
            vector<int> curr(n + 1, INT_MAX);
            prev[0] = 0;
    
            for (int i = 0; i < 2 * n; ++i) {
                curr = vector<int>(n + 1, INT_MAX); // Reset curr for each iteration
                for (int j = 0; j <= min(i + 1, n); ++j) {
                    // Cost of sending the ith person to city A
                    int costA = (j > 0) ? prev[j - 1] + costs[i][0] : INT_MAX;
                    
                    // Cost of sending the ith person to city B
                    int costB = (j <= i) ? prev[j] + costs[i][1] : INT_MAX;
    
                    curr[j] = min(costA, costB);
                }
                prev = curr; // Update prev for the next iteration
            }
    
            return prev[n];
        }
    };
```

## Solution 3. Greedy

The smaller `cost[i][0] - cost[i][1]` is, the more likely `i`-th person should go to city A.

So we can sort the array in ascending order of `cost[i][0] - cost[i][1]`. The first half goes to city A, the second half goes to city B.

```cpp
// OJ: https://leetcode.com/problems/two-city-scheduling/
// Author: github.com/lzl124631x
// Time: O(NlogN)
// Space: O(1)
costs = [[10,20],[30,200],[400,50],[30,20]]
-10, -170, 350, 10
-170, -10, 10, 350
[30, 200] [10, 20] [30, 20] [400, 50]
 A    B    A   B    B   A    B    A
class Solution {
    public:
        int twoCitySchedCost(vector<vector<int>>& costs) {
            int n = costs.size() / 2;
            int totalCost = 0;
    
            // Sort based on the difference between cost to City A and City B
            sort(costs.begin(), costs.end(), [](const auto& a, const auto& b) {
                return (a[0] - a[1]) < (b[0] - b[1]);
            });
    
            // The first 'n' people go to City A, and the rest go to City B
            for (int i = 0; i < 2 * n; ++i) {
                totalCost += costs[i][(i >= n)]; // If i >= n, assign to city B (index 1)
            }
    
            return totalCost;
        }
    };
    
```
