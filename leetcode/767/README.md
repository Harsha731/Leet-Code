# [767. Reorganize String (Medium)](https://leetcode.com/problems/reorganize-string)

<p>Given a string <code>s</code>, rearrange the characters of <code>s</code> so that any two adjacent characters are not the same.</p>
<p>Return <em>any possible rearrangement of</em> <code>s</code> <em>or return</em> <code>""</code> <em>if not possible</em>.</p>
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> s = "aab"
<strong>Output:</strong> "aba"
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> s = "aaab"
<strong>Output:</strong> ""
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>1 &lt;= s.length &lt;= 500</code></li>
	<li><code>s</code> consists of lowercase English letters.</li>
</ul>

**Companies**:
[Amazon](https://leetcode.com/company/amazon), [Pinterest](https://leetcode.com/company/pinterest), [Google](https://leetcode.com/company/google)

**Related Topics**:  
[Hash Table](https://leetcode.com/tag/hash-table/), [String](https://leetcode.com/tag/string/), [Greedy](https://leetcode.com/tag/greedy/), [Sorting](https://leetcode.com/tag/sorting/), [Heap (Priority Queue)](https://leetcode.com/tag/heap-priority-queue/), [Counting](https://leetcode.com/tag/counting/)

**Similar Questions**:
* [Rearrange String k Distance Apart (Hard)](https://leetcode.com/problems/rearrange-string-k-distance-apart/)
* [Task Scheduler (Medium)](https://leetcode.com/problems/task-scheduler/)
* [Longest Happy String (Medium)](https://leetcode.com/problems/longest-happy-string/)

## Solution 1. Sequential Placing (Greedy)

Fill the characters at even postions first, then do at odd. By using (i>=s.size) i=1
The problem may arise if the mostFreq > n+1 / 2

```cpp

class Solution {
public:
    string reorganizeString(string s) {
        vector<int> cnt(26, 0);  
        int mostFreq = 0, i = 0; 

        // Count frequency of each character and track the most frequent one
        for (char c : s) {
            if (++cnt[c - 'a'] > cnt[mostFreq]) 
                mostFreq = c - 'a';
        }

        // If the most frequent character's count is more than half the size, return empty
        if (2 * cnt[mostFreq] - 1 > s.size()) 
            return "";

        while (cnt[mostFreq] > 0) {
            s[i] = 'a' + mostFreq;
            cnt[mostFreq]--;
            i += 2;
        }

        for (int j = 0; j < 26; ++j) {
            while (cnt[j] > 0) {
                if (i >= s.size())  i = 1;  // Switch to odd positions if even positions are filled
                s[i] = 'a' + j;
                cnt[j]--;
                i += 2;
            }
        }

        return s;
    }
};

```

## Solution 2. PQ

use hashmap and store the frequencies and push into PQ
Do while(pq.size > 1) pop the 1st and 2nd and add to string end
Push if still frequency is present
Atlast, if pq.size=1 and freq!=1, then invalid
Else, add that to string

```cpp
// TC : O(NlogM) and M=26
// SC : O(N)

class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> ump;
        priority_queue<pair<int, char>> pq;
        string res = "";
        
        for (char s : S) ump[s]++;
        for (auto it : ump) pq.push({it.second, it.first});
        
        while (pq.size() > 1) {
            auto [freq1, char1] = pq.top(); pq.pop();
            auto [freq2, char2] = pq.top(); pq.pop();
            
            res += char1; res += char2;
            if (--freq1 > 0) pq.push({freq1, char1});
            if (--freq2 > 0) pq.push({freq2, char2});
        }
        
        if (!pq.empty() && pq.top().first > 1) return "";       // a character have no place to fill
        if (!pq.empty()) res += pq.top().second;                // at last, only a character remains
        
        return res;
    }
};
```
