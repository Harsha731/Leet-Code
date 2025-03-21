# [1383. Maximum Performance of a Team (Hard)](https://leetcode.com/problems/maximum-performance-of-a-team/)

<p>There are <code>n</code> engineers numbered from 1 to <code>n</code>&nbsp;and&nbsp;two arrays: <code>speed</code>&nbsp;and <code>efficiency</code>, where <code>speed[i]</code> and <code>efficiency[i]</code> represent the speed and efficiency for the i-th engineer respectively. <em>Return the maximum <strong>performance</strong> of a team composed of&nbsp;at most&nbsp;<code>k</code>&nbsp;engineers, since the answer can be a huge number, return this modulo&nbsp;10^9 + 7.</em></p>

<p>The <strong>performance</strong> of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among&nbsp;their engineers.&nbsp;</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
<strong>Output:</strong> 60
<strong>Explanation:</strong> 
We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
<strong>Output:</strong> 68
<strong>Explanation:
</strong>This is the same example as the first but k = 3. We can select engineer 1, engineer 2 and engineer 5 to get the maximum performance of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
<strong>Output:</strong> 72
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 10^5</code></li>
	<li><code>speed.length == n</code></li>
	<li><code>efficiency.length == n</code></li>
	<li><code>1 &lt;= speed[i] &lt;= 10^5</code></li>
	<li><code>1 &lt;= efficiency[i] &lt;= 10^8</code></li>
	<li><code>1 &lt;= k &lt;= n</code></li>
</ul>

**Related Topics**:  
[Greedy](https://leetcode.com/tag/greedy/), [Sort](https://leetcode.com/tag/sort/)

## Solution 1. Sort by one dimension, Greedy on the other dimension

### Intuition

The idea behind 

```cpp
// atMost, so here we are not calculating only when pq.size(), but from the start onwards
// Last question is minimum (min cost to hire k workers), here it is maximum
// So, we used sorted in desc order, minHeap, max is ans calculation
// We need to multiply the sum of speeds with min efficiency
// atMost can be useful only when we are i<k in efficiency ith index, as if i>=k, 
// then it is better to choose more k's for more sum of speeds as anyways the efficency is fixed


class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> engineers;

        // Pair efficiency and speed of each engineer
        for (int i = 0; i < n; ++i)
            engineers.push_back({efficiency[i], speed[i]});

        // Sort engineers by efficiency in descending order
        sort(engineers.rbegin(), engineers.rend());

        long ans = 0, speedSum = 0;
        priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap to store the smallest speeds

        // Iterate over the sorted engineers
        for (auto& engineer : engineers) {
            int currEfficiency = engineer.first;
            int currSpeed = engineer.second;

            // Add the current engineer's speed
            speedSum += currSpeed;
            pq.push(currSpeed);

            // Remove the engineer with the lowest speed if we exceed k engineers
            if (pq.size() > k) {
                speedSum -= pq.top();
                pq.pop();
            }

            // Calculate performance and update max performance
            ans = max(ans, speedSum * currEfficiency);
        }
        
        // Return result modulo 10^9 + 7
        return ans % (int)(1e9 + 7);
    }
};

```
