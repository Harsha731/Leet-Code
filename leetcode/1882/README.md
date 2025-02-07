# [1882. Process Tasks Using Servers (Medium)](https://leetcode.com/problems/process-tasks-using-servers/)

<p>You are given two <strong>0-indexed</strong> integer arrays <code>servers</code> and <code>tasks</code> of lengths <code>n</code>​​​​​​ and <code>m</code>​​​​​​ respectively. <code>servers[i]</code> is the <strong>weight</strong> of the <code>i<sup>​​​​​​th</sup></code>​​​​ server, and <code>tasks[j]</code> is the <strong>time needed</strong> to process the <code>j<sup>​​​​​​th</sup></code>​​​​ task <strong>in seconds</strong>.</p>

<p>You are running a simulation system that will shut down after all tasks are processed. Each server can only process one task at a time. You will be able to process the <code>j<sup>th</sup></code> task starting from the <code>j<sup>th</sup></code> second beginning with the <code>0<sup>th</sup></code> task at second <code>0</code>. To process task <code>j</code>, you assign it to the server with the <strong>smallest weight</strong> that is free, and in case of a tie, choose the server with the <strong>smallest index</strong>. If a free server gets assigned task <code>j</code> at second <code>t</code>,​​​​​​ it will be free again at the second <code>t + tasks[j]</code>.</p>

<p>If there are no free servers, you must wait until one is free and execute the free tasks <strong>as soon as possible</strong>. If <strong>multiple</strong> tasks need to be assigned, assign them in order of <strong>increasing index</strong>.</p>

<p>You may assign multiple tasks at the same second if there are multiple free servers.</p>

<p>Build an array <code>ans</code>​​​​ of length <code>m</code>, where <code>ans[j]</code> is the <strong>index</strong> of the server the <code>j<sup>​​​​​​th</sup></code> task will be assigned to.</p>

<p>Return <em>the array </em><code>ans</code>​​​​.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> servers = [3,3,2], tasks = [1,2,3,2,1,2]
<strong>Output:</strong> [2,2,0,2,1,2]
<strong>Explanation: </strong>Events in chronological order go as follows:
- At second 0, task 0 is added and processed using server 2 until second 1.
- At second 1, server 2 becomes free. Task 1 is added and processed using server 2 until second 3.
- At second 2, task 2 is added and processed using server 0 until second 5.
- At second 3, server 2 becomes free. Task 3 is added and processed using server 2 until second 5.
- At second 4, task 4 is added and processed using server 1 until second 5.
- At second 5, all servers become free. Task 5 is added and processed using server 2 until second 7.</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> servers = [5,1,4,3,2], tasks = [2,1,2,4,5,2,1]
<strong>Output:</strong> [1,4,1,4,1,3,2]
<strong>Explanation: </strong>Events in chronological order go as follows: 
- At second 0, task 0 is added and processed using server 1 until second 2.
- At second 1, task 1 is added and processed using server 4 until second 2.
- At second 2, servers 1 and 4 become free. Task 2 is added and processed using server 1 until second 4. 
- At second 3, task 3 is added and processed using server 4 until second 7.
- At second 4, server 1 becomes free. Task 4 is added and processed using server 1 until second 9. 
- At second 5, task 5 is added and processed using server 3 until second 7.
- At second 6, task 6 is added and processed using server 2 until second 7.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>servers.length == n</code></li>
	<li><code>tasks.length == m</code></li>
	<li><code>1 &lt;= n, m &lt;= 2 * 10<sup>5</sup></code></li>
	<li><code>1 &lt;= servers[i], tasks[j] &lt;= 2 * 10<sup>5</sup></code></li>
</ul>


**Related Topics**:  
[Heap](https://leetcode.com/tag/heap/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/process-tasks-using-servers/
// Author: github.com/lzl124631x
// Time: O((S + T) * logS)
// Space: O(S + T)


// Smallest weight server will be assigned first
// If tie, then smallest index server
// We have to assign the server which is free at that particular time (or more)
// At a time 1 is sent to busy from idle, more than 1 can be sent to idle from busy at a time

class Solution {
public:
    vector<int> assignTasks(vector<int>& S, vector<int>& T) {
        // Vector to store the next available time for each server
        vector<int> avail(S.size());
        
        // Vector to store the server assigned to each task
        vector<int> ans(T.size());
        
        // The idle server with smallest weight and index is at the top
        auto idleCmp = [&](int a, int b) { 
            return S[a] != S[b] ? S[a] > S[b] : a > b; 
        };
        
        // The busy server with the smallest available time is at the top
        auto busyCmp = [&](int a, int b) { 
            return avail[a] > avail[b]; 
        };
        
        // Priority queue for idle servers
        priority_queue<int, vector<int>, decltype(idleCmp)> idle(idleCmp);
        
        // Priority queue for busy servers
        priority_queue<int, vector<int>, decltype(busyCmp)> busy(busyCmp);
        
        // Initialize idle servers
        for (int i = 0; i < S.size(); ++i) idle.push(i);
        
        int time = 0; // Current time
        
        // Assign tasks to servers
        for (int i = 0; i < T.size(); ++i) {
            // Ensure current time is at least the task index
            time = max(i, time);
            
            // If no idle servers, jump to the next available time
            if (idle.empty()) time = avail[busy.top()];
            
            // Move available busy servers back to idle queue
            while (busy.size() && avail[busy.top()] <= time) {
                idle.push(busy.top());
                busy.pop();
            }
            
            // Assign task to the next available server
            int s = idle.top();
            idle.pop();
            ans[i] = s; // Store assigned server
            
            // Update server's available time
            avail[s] = time + T[i];
            
            // Mark server as busy
            busy.push(s);
        }
        
        return ans; // Return assigned servers
    }
};

```
