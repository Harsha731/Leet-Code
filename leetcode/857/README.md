# [857. Minimum Cost to Hire K Workers (Hard)](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/)

<p>There are <code>N</code> workers.&nbsp; The <code>i</code>-th worker has a <code>quality[i]</code> and a minimum wage expectation <code>wage[i]</code>.</p>

<p>Now we want to hire exactly <code>K</code>&nbsp;workers to form a <em>paid group</em>.&nbsp; When hiring a group of K workers, we must pay them according to the following rules:</p>

<ol>
	<li>Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.</li>
	<li>Every worker in the paid group must be paid at least their minimum wage expectation.</li>
</ol>

<p>Return the least amount of money needed to form a paid group satisfying the above conditions.</p>

<p>&nbsp;</p>

<ol>
</ol>

<div>
<p><strong>Example 1:</strong></p>

<pre><strong>Input: </strong>quality = <span id="example-input-1-1">[10,20,5]</span>, wage = <span id="example-input-1-2">[70,50,30]</span>, K = <span id="example-input-1-3">2</span>
<strong>Output: </strong><span id="example-output-1">105.00000
<strong>Explanation</strong>: </span><span>We pay 70 to 0-th worker and 35 to 2-th worker.</span>
</pre>

<div>
<p><strong>Example 2:</strong></p>

<pre><strong>Input: </strong>quality = <span id="example-input-2-1">[3,1,10,10,1]</span>, wage = <span id="example-input-2-2">[4,8,2,2,7]</span>, K = <span id="example-input-2-3">3</span>
<strong>Output: </strong><span id="example-output-2">30.66667
<strong>Explanation</strong>: </span><span>We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.</span> 
</pre>

<p>&nbsp;</p>

<p><strong>Note:</strong></p>

<ol>
	<li><code>1 &lt;= K &lt;= N &lt;= 10000</code>, where <code>N = quality.length = wage.length</code></li>
	<li><code>1 &lt;= quality[i] &lt;= 10000</code></li>
	<li><code>1 &lt;= wage[i] &lt;= 10000</code></li>
	<li>Answers within <code>10^-5</code> of the correct answer will be considered correct.</li>
</ol>
</div>
</div>


**Related Topics**:  
[Heap](https://leetcode.com/tag/heap/)



## Solution 1. Max Heap

```cpp

/*
Time Complexity
O(NlogN) for sort.
O(NlogK) for priority queue. Both are needed for this problem

wi : wj :: qi : qj    =>    wi / qi  =  wj / qj   => We select the minimum wi/qi ration
we need to provide the minimum wage to all the k workers

We are simply multiplying the current wi/qi value with the sum of the min k quality workers till now

What is we are supposed to remove the worker[1] and we are multiplying with worker[0]
No problem, it will be more than the earlier, as sum is same with more value of worker[0]
causes it to ingore while applying the min function

What is the problem ?
Min cost to hire k workers, (sum of all the qualities) * (min w/q ratio) = answer

why sorted asc ?
We want to have the min w/q first, we add the first qualities, and the w/q at that point (as it will be the big one among the k)

why max Heap ?
We want to remove the max quality worker, to have the min cost

what if the one entered is popped out ?
qsum_new = qsum_old, but the w/q will be more, so it will be ignored while we are using min(ans, ...)
*/

class Solution {
public:
    double mincostToHireWorkers(vector<int> q, vector<int> w, int K) {
        vector<vector<double>> workers;

        // Calculate the ratio of wage to quality for each worker
        for (int i = 0; i < q.size(); ++i)
            workers.push_back({(double)(w[i]) / q[i], (double)q[i]});

        // Sort workers by their wage-to-quality ratio
        sort(workers.begin(), workers.end());

        double ans = DBL_MAX, qsum = 0;
        priority_queue<int> pq;  // Max-heap to store the largest quality workers

        // Iterate over the sorted workers
        for (auto worker: workers) {
            qsum += worker[1];  // Add the quality of the current worker
            pq.push(worker[1]); // Add the quality to the max-heap
            if (pq.size() > K) qsum -= pq.top(), pq.pop();  // Remove the highest quality if we exceed K workers
            if (pq.size() == K) ans = min(ans, qsum * worker[0]);  // Calculate minimum cost for K workers
        }
        
        return ans;
    }
};

```
