# [253. Meeting Rooms II (Medium)](https://leetcode.com/problems/meeting-rooms-ii/)

<p>Given an array of meeting time intervals <code>intervals</code> where <code>intervals[i] = [start<sub>i</sub>, end<sub>i</sub>]</code>, return <em>the minimum number of conference rooms required</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<pre><strong>Input:</strong> intervals = [[0,30],[5,10],[15,20]]
<strong>Output:</strong> 2
</pre><p><strong>Example 2:</strong></p>
<pre><strong>Input:</strong> intervals = [[7,10],[2,4]]
<strong>Output:</strong> 1
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;=&nbsp;intervals.length &lt;= 10<sup>4</sup></code></li>
	<li><code>0 &lt;= start<sub>i</sub> &lt; end<sub>i</sub> &lt;= 10<sup>6</sup></code></li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Facebook](https://leetcode.com/company/facebook), [Bloomberg](https://leetcode.com/company/bloomberg), [Microsoft](https://leetcode.com/company/microsoft), [Google](https://leetcode.com/company/google), [Oracle](https://leetcode.com/company/oracle), [Walmart Labs](https://leetcode.com/company/walmart-labs), [ByteDance](https://leetcode.com/company/bytedance), [Uber](https://leetcode.com/company/uber), [Twitter](https://leetcode.com/company/twitter), [Snapchat](https://leetcode.com/company/snapchat), [Yahoo](https://leetcode.com/company/yahoo), [VMware](https://leetcode.com/company/vmware), [Quora](https://leetcode.com/company/quora), [Visa](https://leetcode.com/company/visa), [Swiggy](https://leetcode.com/company/swiggy)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Two Pointers](https://leetcode.com/tag/two-pointers/), [Greedy](https://leetcode.com/tag/greedy/), [Sorting](https://leetcode.com/tag/sorting/), [Heap (Priority Queue)](https://leetcode.com/tag/heap-priority-queue/)

**Similar Questions**:
* [Merge Intervals (Medium)](https://leetcode.com/problems/merge-intervals/)
* [Meeting Rooms (Easy)](https://leetcode.com/problems/meeting-rooms/)
* [Minimum Number of Arrows to Burst Balloons (Medium)](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)
* [Car Pooling (Medium)](https://leetcode.com/problems/car-pooling/)

## Solution 1.

```cpp
/*
	Time Complexity: O(N logN)
	Space complexity: O(N)
	
	where N is the number of elements in array.
*/

int minRooms(vector<vector<int>> intervals){
    int n = intervals.size();

    // Storing start time and end time in different arrays.
    int startTime[n];
    int endTime[n];

    for (int i = 0; i < n; i++)    {
        startTime[i] = intervals[i][0];
        endTime[i] = intervals[i][1];
    }

    sort(startTime, startTime + n);
    sort(endTime, endTime + n);

    int result = 1;
    int roomRequired = 0;

    int i = 0, j = 0;
    while (i < n && j < n) {
        if (startTime[i] < endTime[j])  {
            roomRequired++;
            i++;
        } else {
            roomRequired--;
            j++;
        }
        result = max(result, roomRequired);
    }
    return result;
}
```

## Solution 2. Heap

```cpp
// OJ: https://leetcode.com/problems/meeting-rooms-ii/
// Author: github.com/lzl124631x
// Time: O(NlogN)
// Space: O(N)
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& A) {
        sort(begin(A), end(A), [](auto &a, auto &b) { return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1]; });
        int ans = 0;
        priority_queue<int, vector<int>, greater<>> pq; // min heap of end times
        for (auto &v : A) {
            int s = v[0], e = v[1];
            while (pq.size() && pq.top() <= s) pq.pop();
            pq.push(e);
            ans = max(ans, (int)pq.size());
        }
        return ans;
    }
};
```
