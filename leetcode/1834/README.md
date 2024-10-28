# [1834. Single-Threaded CPU (Medium)](https://leetcode.com/problems/single-threaded-cpu/)

<p>You are given <code>n</code>​​​​​​ tasks labeled from <code>0</code> to <code>n - 1</code> represented by a 2D integer array <code>tasks</code>, where <code>tasks[i] = [enqueueTime<sub>i</sub>, processingTime<sub>i</sub>]</code> means that the <code>i<sup>​​​​​​th</sup></code>​​​​ task will be available to process at <code>enqueueTime<sub>i</sub></code> and will take <code>processingTime<sub>i</sub></code><sub> </sub>to finish processing.</p>

<p>You have a single-threaded CPU that can process <strong>at most one</strong> task at a time and will act in the following way:</p>

<ul>
	<li>If the CPU is idle and there are no available tasks to process, the CPU remains idle.</li>
	<li>If the CPU is idle and there are available tasks, the CPU will choose the one with the <strong>shortest processing time</strong>. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.</li>
	<li>Once a task is started, the CPU will <strong>process the entire task</strong> without stopping.</li>
	<li>The CPU can finish a task then start a new one instantly.</li>
</ul>

<p>Return <em>the order in which the CPU will process the tasks.</em></p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> tasks = [[1,2],[2,4],[3,2],[4,1]]
<strong>Output:</strong> [0,2,3,1]
<strong>Explanation: </strong>The events go as follows: 
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
<strong>Output:</strong> [4,3,2,0,1]
<strong>Explanation</strong><strong>: </strong>The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>tasks.length == n</code></li>
	<li><code>1 &lt;= n &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= enqueueTime<sub>i</sub>, processingTime<sub>i</sub> &lt;= 10<sup>9</sup></code></li>
</ul>


**Related Topics**:  
[Heap](https://leetcode.com/tag/heap/)

## Solution 1. Min-Heap

Use a min-heap `pq` to keep track of available tasks, sorted first by processing time then by index.

Sort the input array in ascending order of enqueue time.

Let `time` be the current time. When `time >= A[i][0]`, keep pushing `A[i]` into the min-heap.

Then we pop a task from the min-heap and handle it. Increase the `time` by the processing time of this task and add its index to the answer.

```cpp
    // We add the index to the pair <int, int>
    // We make the current time = 0th task enqueue time
    // In general, it have 2 cases if pq is empty
    // i) currentTime is more than the next task enqueue time, we let it be as more can be pushed into queue instead of only one
    // ii) If it is is less than the next task enqueue time, we shift it to the next task
    // We push all the available tasks according to the current time
    // We consider the one with minimum processing time by popping it out

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Min-heap for tasks
        long n = tasks.size();
        long currentTime = 0; 

        // We need index at the end, so we are appending it
        // Same like creating a pair if we have a value, but here we already have 2 values
        for (int j = 0; j < n; ++j) {
            tasks[j].push_back(j);
        }
        sort(begin(tasks), end(tasks)); // Sort by enqueue time
        
        vector<int> ans; 

        int i = 0; 
        while (i < n || !pq.empty()) {
            // If no tasks in the heap, then we have two cases
            // currentTime is more than the next task enqueue time, we let it be as more can be pushed into queue instead of only one
            // If it is is less than the next task enqueue time, we shift it to the next task
            if (pq.empty()) {
                currentTime = max(currentTime, (long)tasks[i][0]);
            }

            // Push all tasks whose enqueue time is <= current time into the heap
            while (i < n && currentTime >= tasks[i][0]) {
                pq.emplace(tasks[i][1], tasks[i][2]); // (processing time, index)
                ++i;
            }

            // Process the task with the smallest processing time
            auto [processingTime, index] = pq.top();
            pq.pop();
            currentTime += processingTime; 
            ans.push_back(index); 
        }

        return ans;
    }
};

```

## Note

Similar to [1353. Maximum Number of Events That Can Be Attended (Medium)](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/)
