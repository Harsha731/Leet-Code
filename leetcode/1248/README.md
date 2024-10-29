# [1248. Count Number of Nice Subarrays (Medium)](https://leetcode.com/problems/count-number-of-nice-subarrays/)

<p>Given an array of integers <code>nums</code> and an integer <code>k</code>. A continuous subarray is called <strong>nice</strong> if there are <code>k</code> odd numbers on it.</p>

<p>Return <em>the number of <strong>nice</strong> sub-arrays</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> nums = [1,1,2,1,1], k = 3
<strong>Output:</strong> 2
<strong>Explanation:</strong> The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> nums = [2,4,6], k = 1
<strong>Output:</strong> 0
<strong>Explanation:</strong> There is no odd numbers in the array.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> nums = [2,2,2,1,2,2,1,2,2,2], k = 2
<strong>Output:</strong> 16
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 50000</code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10^5</code></li>
	<li><code>1 &lt;= k &lt;= nums.length</code></li>
</ul>

**Companies**:  
[Booking.com](https://leetcode.com/company/bookingcom), [Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Hash Table](https://leetcode.com/tag/hash-table/), [Math](https://leetcode.com/tag/math/), [Sliding Window](https://leetcode.com/tag/sliding-window/)


## Solution 1. Prefix State Map

```cpp
class Solution {
public:
    int numberOfSubarrays(vector<int>& A, int k) {
        unordered_map<int, int> m{{0, 1}}; // cnt -> number of occurrences of this cnt
        int cnt = 0, ans = 0;
        for (int i = 0; i < A.size(); ++i) {
            cnt += A[i] % 2;
            ans += m.count(cnt - k) ? m[cnt - k] : 0;
            m[cnt]++;
        }
        return ans;
    }
};
```

## Solution 2. Two Pointers

```cpp
// OJ: https://leetcode.com/problems/count-number-of-nice-subarrays/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int numberOfSubarrays(vector<int>& A, int k) {
        int N = A.size(), i = 0, j = 0, prev = -1, ans = 0, ci = 0, cj = 0;
        while (j < N) {
            cj += A[j++] % 2;
            if (ci <= cj - k) {
                prev = i;
                while (ci <= cj - k) ci += A[i++] % 2;
            }
            if (cj >= k) ans += i - prev;
        }
        return ans;
    }
};
```

## Solution 3. AtMost to Equal + Find Maximum Sliding Window

Check out "[C++ Maximum Sliding Window Cheatsheet Template!](https://leetcode.com/problems/frequency-of-the-most-frequent-element/discuss/1175088/C%2B%2B-Maximum-Sliding-Window-Cheatsheet-Template!)"

Exactly `k` times = At Most `k` times - At Most `k - 1` times.

```cpp
class Solution {
public:
    int numberOfSubarrays(vector<int>& A, int goal) {
        int n = A.size();
        int i = 0, j = 0, cnt1 = 0, cnt2 = 0, count = 0;

        for (int end = 0; end < n; ++end) {
            cnt1 += A[end] % 2;
            cnt2 += A[end] % 2;

            // Adjust window `i` to have exactly `goal` odd numbers
            while (i <= end && cnt1 > goal) {
                cnt1 -= A[i++] % 2;
            }

            // Adjust window `j` to have at most `goal - 1` odd numbers
            while (j <= end && cnt2 > goal - 1) {
                cnt2 -= A[j++] % 2;
            }

            // If the cnt1 window has exactly `goal` odd numbers, all subarrays starting from indices in range [j, i] to `end` have `goal` odd numbers
            if (cnt1 == goal) {
                count += j - i;
            }
        }

        return count;
    }
};

```

## Discuss

https://leetcode.com/problems/count-number-of-nice-subarrays/discuss/1515501/C%2B%2B-Prefix-State-Map-Two-Pointers-Sliding-Window
