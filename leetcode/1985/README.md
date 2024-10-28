# [1985. Find the Kth Largest Integer in the Array (Medium)](https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/)

<p>You are given an array of strings <code>nums</code> and an integer <code>k</code>. Each string in <code>nums</code> represents an integer without leading zeros.</p>

<p>Return <em>the string that represents the </em><code>k<sup>th</sup></code><em><strong> largest integer</strong> in </em><code>nums</code>.</p>

<p><strong>Note</strong>: Duplicate numbers should be counted distinctly. For example, if <code>nums</code> is <code>["1","2","2"]</code>, <code>"2"</code> is the first largest integer, <code>"2"</code> is the second-largest integer, and <code>"1"</code> is the third-largest integer.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> nums = ["3","6","7","10"], k = 4
<strong>Output:</strong> "3"
<strong>Explanation:</strong>
The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
The 4<sup>th</sup> largest integer in nums is "3".
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> nums = ["2","21","12","1"], k = 3
<strong>Output:</strong> "2"
<strong>Explanation:</strong>
The numbers in nums sorted in non-decreasing order are ["1","2","12","21"].
The 3<sup>rd</sup> largest integer in nums is "2".
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> nums = ["0","0"], k = 2
<strong>Output:</strong> "0"
<strong>Explanation:</strong>
The numbers in nums sorted in non-decreasing order are ["0","0"].
The 2<sup>nd</sup> largest integer in nums is "0".
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= k &lt;= nums.length &lt;= 10<sup>4</sup></code></li>
	<li><code>1 &lt;= nums[i].length &lt;= 100</code></li>
	<li><code>nums[i]</code> consists of only digits.</li>
	<li><code>nums[i]</code> will not have any leading zeros.</li>
</ul>


**Similar Questions**:
* [Kth Largest Element in an Array (Medium)](https://leetcode.com/problems/kth-largest-element-in-an-array/)

## Solution 1. Sorting

```cpp
// Note: Duplicate numbers should be counted distinctly. For example, if nums is ["1","2","2"], "2" is the first largest integer, 
// "2" is the second-largest integer, and "1" is the third-largest integer.

// Sorting
// TC : O(NlogN) ans SC : O(1)

class Solution {
public:
    static bool cmp(string &a,string &b) {
        if (a.size() == b.size()) return a < b;
        return a.size() < b.size();
    }
    
    string kthLargestNumber(vector<string>& nums, int k) {
        sort(nums.begin(), nums.end(), cmp);
        int n = nums.size();
        return nums[n-k];
    }
};
```


## Solution 2. PQ approach

```cpp
// TC : O(NlogK) and SC : O(K)

// If it is a number, no cmp is required. Automatically the smaller numbers will be on top
// But here, as it is strings we need to define what is high and small

class Solution {
public:
    // Custom cmp to order strings by length and lexicographically
    struct cmp {
        bool operator() (string &s1, string &s2) {
            return s1.length() > s2.length() || (s1.length() == s2.length() && s1 > s2);
        }
    };

    string kthLargestNumber(vector<string>& nums, int k) {
        // Declare a min-heap of strings using the custom cmp
        priority_queue<string, vector<string>, cmp> q;

        for (const auto& num : nums) {
            q.push(num);
            if (q.size() > k) {
                q.pop();
            }
        }

        return q.top(); // Return the k-th largest number
    }
};

```
