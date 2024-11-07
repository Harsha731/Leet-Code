# [983. Minimum Cost For Tickets (Medium)](https://leetcode.com/problems/minimum-cost-for-tickets/)

<p>In a country popular for train travel, you&nbsp;have planned some train travelling one year in advance.&nbsp; The days of the year that you will travel is given as an array <code>days</code>.&nbsp; Each day is an integer from <code>1</code> to <code>365</code>.</p>

<p>Train tickets are sold in 3 different ways:</p>

<ul>
	<li>a 1-day pass is sold for <code>costs[0]</code> dollars;</li>
	<li>a 7-day pass is sold for <code>costs[1]</code> dollars;</li>
	<li>a 30-day pass is sold for <code>costs[2]</code> dollars.</li>
</ul>

<p>The passes allow that many days of consecutive travel.&nbsp; For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.</p>

<p>Return the minimum number of dollars you need to travel every day in the given list of <code>days</code>.</p>

<p>&nbsp;</p>

<p><strong>Example 1:</strong></p>

<pre><strong>Input: </strong>days = <span id="example-input-1-1">[1,4,6,7,8,20]</span>, costs = <span id="example-input-1-2">[2,7,15]</span>
<strong>Output: </strong><span id="example-output-1">11</span>
<strong>Explanation: </strong>
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total you spent $11 and covered all the days of your travel.
</pre>

<div>
<p><strong>Example 2:</strong></p>

<pre><strong>Input: </strong>days = <span id="example-input-2-1">[1,2,3,4,5,6,7,8,9,10,30,31]</span>, costs = <span id="example-input-2-2">[2,7,15]</span>
<strong>Output: </strong><span id="example-output-2">17</span>
<strong>Explanation: </strong>
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total you spent $17 and covered all the days of your travel.
</pre>

<p>&nbsp;</p>
</div>

<p><strong>Note:</strong></p>

<ol>
	<li><code>1 &lt;= days.length &lt;= 365</code></li>
	<li><code>1 &lt;= days[i] &lt;= 365</code></li>
	<li><code>days</code> is in strictly increasing order.</li>
	<li><code>costs.length == 3</code></li>
	<li><code>1 &lt;= costs[i] &lt;= 1000</code></li>
</ol>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Coin Change (Medium)](https://leetcode.com/problems/coin-change/)

## Solution 1. DP Top-down

```cpp
// OJ: https://leetcode.com/problems/minimum-cost-for-tickets/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    int solve(int i, const vector<int>& days, const vector<int>& costs, vector<int>& memo) {
        int N = days.size();
        if (i >= N) return 0;
        if (memo[i] != -1) return memo[i];
        
        // 1-day pass: Take the current day and move to the next one
        int cost1 = solve(i + 1, days, costs, memo) + costs[0];
        
        // 7-day pass: Move to the first day that is outside the 7-day window
        int next7 = lower_bound(begin(days) + i, end(days), days[i] + 7) - begin(days);
        int cost7 = solve(next7, days, costs, memo) + costs[1];
        
        // 30-day pass: Move to the first day that is outside the 30-day window
        int next30 = lower_bound(begin(days) + i, end(days), days[i] + 30) - begin(days);
        int cost30 = solve(next30, days, costs, memo) + costs[2];
        
        return memo[i] = min({cost1, cost7, cost30});
    }

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int N = days.size();
        vector<int> memo(N, -1); 
        return solve(0, days, costs, memo);
    }
};

```

## Solution 2. DP Bottom-up

```cpp
// OJ: https://leetcode.com/problems/minimum-cost-for-tickets/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int N = days.size();
        vector<int> dp(N + 1, 0); // Initialize dp array with 0
        
        for (int i = N - 1; i >= 0; --i) {
            int cost1 = dp[i + 1] + costs[0]; // 1-day pass
            
            // 7-day pass
            int next7 = lower_bound(begin(days) + i, end(days), days[i] + 7) - begin(days);
            int cost7 = dp[next7] + costs[1];
            
            // 30-day pass
            int next30 = lower_bound(begin(days) + i, end(days), days[i] + 30) - begin(days);
            int cost30 = dp[next30] + costs[2];
            
            dp[i] = min({cost1, cost7, cost30});
        }
        
        return dp[0]; // Minimum cost to cover all days starting from day 0
    }
};

```
