# [763. Partition Labels (Medium)](https://leetcode.com/problems/partition-labels/)

<p>You are given a string <code>s</code>. We want to partition the string into as many parts as possible so that each letter appears in at most one part.</p>

<p>Note that the partition is done so that after concatenating all the parts in order, the resultant string should be <code>s</code>.</p>

<p>Return <em>a list of integers representing the size of these parts</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> s = "ababcbacadefegdehijhklij"
<strong>Output:</strong> [9,7,8]
<strong>Explanation:</strong>
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> s = "eccbbbbdec"
<strong>Output:</strong> [10]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 500</code></li>
	<li><code>s</code> consists of lowercase English letters.</li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Facebook](https://leetcode.com/company/facebook), [Google](https://leetcode.com/company/google), [Oracle](https://leetcode.com/company/oracle)

**Related Topics**:  
[Hash Table](https://leetcode.com/tag/hash-table/), [Two Pointers](https://leetcode.com/tag/two-pointers/), [String](https://leetcode.com/tag/string/), [Greedy](https://leetcode.com/tag/greedy/)

**Similar Questions**:
* [Merge Intervals (Medium)](https://leetcode.com/problems/merge-intervals/)


## Solution 

```cpp
// OJ: https://leetcode.com/problems/partition-labels/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
// j gives the maximum of the last index possible for all the characters in the current partition
// i = j means all are covered in this part, so we do a cut here

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int lastIdx[26]; // Last index of each char
        for (int i = 0; i < s.size(); ++i) {
            lastIdx[s[i] - 'a'] = i;
        }

        int end = 0, start = 0; // Two pointers
        vector<int> result;

        for (int i = 0; i < s.size(); ++i) {
            end = max(end, lastIdx[s[i] - 'a']); // Update end

            if (i == end) {
                result.push_back(i - start + 1); // Add partition length
                start = i + 1; // Move start
            }
        }

        return result;
    }
};

```
