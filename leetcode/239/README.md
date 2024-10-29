# [239. Sliding Window Maximum (Hard)](https://leetcode.com/problems/sliding-window-maximum)

<p>You are given an array of integers&nbsp;<code>nums</code>, there is a sliding window of size <code>k</code> which is moving from the very left of the array to the very right. You can only see the <code>k</code> numbers in the window. Each time the sliding window moves right by one position.</p>
<p>Return <em>the max sliding window</em>.</p>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> nums = [1,3,-1,-3,5,3,6,7], k = 3
<strong>Output:</strong> [3,3,5,5,6,7]
<strong>Explanation:</strong> 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       <strong>3</strong>
 1 [3  -1  -3] 5  3  6  7       <strong>3</strong>
 1  3 [-1  -3  5] 3  6  7      <strong> 5</strong>
 1  3  -1 [-3  5  3] 6  7       <strong>5</strong>
 1  3  -1  -3 [5  3  6] 7       <strong>6</strong>
 1  3  -1  -3  5 [3  6  7]      <strong>7</strong>
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> nums = [1], k = 1
<strong>Output:</strong> [1]
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>-10<sup>4</sup> &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
	<li><code>1 &lt;= k &lt;= nums.length</code></li>
</ul>

**Companies**:
[Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [Uber](https://leetcode.com/company/uber)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Queue](https://leetcode.com/tag/queue/), [Sliding Window](https://leetcode.com/tag/sliding-window/), [Heap (Priority Queue)](https://leetcode.com/tag/heap-priority-queue/), [Monotonic Queue](https://leetcode.com/tag/monotonic-queue/)

**Similar Questions**:
* [Minimum Window Substring (Hard)](https://leetcode.com/problems/minimum-window-substring/)
* [Min Stack (Medium)](https://leetcode.com/problems/min-stack/)
* [Longest Substring with At Most Two Distinct Characters (Medium)](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/)
* [Paint House II (Hard)](https://leetcode.com/problems/paint-house-ii/)
* [Jump Game VI (Medium)](https://leetcode.com/problems/jump-game-vi/)
* [Maximum Number of Robots Within Budget (Hard)](https://leetcode.com/problems/maximum-number-of-robots-within-budget/)
* [Maximum Tastiness of Candy Basket (Medium)](https://leetcode.com/problems/maximum-tastiness-of-candy-basket/)
* [Maximal Score After Applying K Operations (Medium)](https://leetcode.com/problems/maximal-score-after-applying-k-operations/)

## Solution 1. Mono-Deque

Use a deque and pop out all the elements less than current from back 
push the current element
If the front needs to be removed (q.front() = i-k), do pop_front
At last, push the q.front() value to the answer vector

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& A, int k) {
        vector<int> ans;
        deque<int> q;
        for (int i = 0; i < A.size(); ++i) {
            while (q.size() && A[q.back()] <= A[i]) q.pop_back();	// important
            q.push_back(i);
            if (q.front() == i - k) q.pop_front();
            if (i >= k - 1) ans.push_back(A[q.front()]);
        }
        return ans;
    }
};
```

## Solution 2. Mono-Deque

We can push the indices as well as values to the deque, indices are unique, while the values are not unique
The only difference come during    
while (q.size() && A[q.back()] <= A[i]) q.pop_back();	// important
if (q.front() == i - k) q.pop_front();

while (q.size() && A[q.back()] < A[i]) q.pop_back();	// important
if (i >= k && q.size() && q.front() == A[i - k]) q.pop_front();

Because in 2nd step of 2nd appraoch, we need to keep duplicates as if we pop_front, the element corresponding to that index needs to be popped, it should not affect the other. For index, it won't be problem, but during values, it will affect	

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& A, int k) {
        deque<int> q;
        vector<int> ans;
        for (int i = 0; i < A.size(); ++i) {
            while (q.size() && q.back() < A[i]) q.pop_back();	// important
            q.push_back(A[i]);
            if (i >= k && q.size() && q.front() == A[i - k]) q.pop_front();
            if (i >= k - 1) ans.push_back(q.front());
        }
        return ans;
    }
};
```
