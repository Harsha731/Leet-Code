# [1481. Least Number of Unique Integers after K Removals (Medium)](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/)

<p>Given an array of integers&nbsp;<code>arr</code>&nbsp;and an integer <code>k</code>.&nbsp;Find the <em>least number of unique integers</em>&nbsp;after removing <strong>exactly</strong> <code>k</code> elements<b>.</b></p>

<ol>
</ol>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input: </strong>arr = [5,5,4], k = 1
<strong>Output: </strong>1
<strong>Explanation</strong>: Remove the single 4, only 5 is left.
</pre>
<strong>Example 2:</strong>

<pre><strong>Input: </strong>arr = [4,3,1,1,3,3,2], k = 3
<strong>Output: </strong>2
<strong>Explanation</strong>: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= arr.length&nbsp;&lt;= 10^5</code></li>
	<li><code>1 &lt;= arr[i] &lt;= 10^9</code></li>
	<li><code>0 &lt;= k&nbsp;&lt;= arr.length</code></li>
</ul>

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Sort](https://leetcode.com/tag/sort/)

## Solution 1. PQ approach

```cpp
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> count;
        for (int num : arr) count[num]++;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        for (auto& [num, freq] : count) minHeap.push({freq, num});

        // Remove elements starting with the smallest frequency
        while (k > 0 && !minHeap.empty()) {
            auto [freq, num] = minHeap.top();
            minHeap.pop();
            if (k >= freq) k -= freq; // Remove all occurrences
            else break;
        }
        
        return minHeap.size() + (k > 0);
    }
};

```


## Solution 2. Counting sort approach

```cpp
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for (int i : arr) freq[i]++;

        int n = arr.size(), uniqueCount = freq.size();
        vector<int> freqCounts(n + 1, 0);

        // Count occurrences of each frequency
        for (auto& [_, f] : freq) freqCounts[f]++;

        // Remove elements based on smallest frequencies
        for (int i = 1; i <= n; i++) {
            int removeCount = min(k / i, freqCounts[i]);
            k -= i * removeCount;
            uniqueCount -= removeCount;

            if (k < i) return uniqueCount;  // Stop if k is exhausted
        }

        return 0;  // All elements removed
    }
};


```
