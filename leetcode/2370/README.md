# [2370. Longest Ideal Subsequence (Medium)](https://leetcode.com/problems/longest-ideal-subsequence)

<p>You are given a string <code>s</code> consisting of lowercase letters and an integer <code>k</code>. We call a string <code>t</code> <strong>ideal</strong> if the following conditions are satisfied:</p>

<ul>
	<li><code>t</code> is a <strong>subsequence</strong> of the string <code>s</code>.</li>
	<li>The absolute difference in the alphabet order of every two <strong>adjacent</strong> letters in <code>t</code> is less than or equal to <code>k</code>.</li>
</ul>

<p>Return <em>the length of the <strong>longest</strong> ideal string</em>.</p>

<p>A <strong>subsequence</strong> is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.</p>

<p><strong>Note</strong> that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of <code>&#39;a&#39;</code> and <code>&#39;z&#39;</code> is <code>25</code>, not <code>1</code>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;acfgbd&quot;, k = 2
<strong>Output:</strong> 4
<strong>Explanation:</strong> The longest ideal string is &quot;acbd&quot;. The length of this string is 4, so 4 is returned.
Note that &quot;acfgbd&quot; is not ideal because &#39;c&#39; and &#39;f&#39; have a difference of 3 in alphabet order.</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;abcd&quot;, k = 3
<strong>Output:</strong> 4
<strong>Explanation:</strong> The longest ideal string is &quot;abcd&quot;. The length of this string is 4, so 4 is returned.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 10<sup>5</sup></code></li>
	<li><code>0 &lt;= k &lt;= 25</code></li>
	<li><code>s</code> consists of lowercase English letters.</li>
</ul>


**Companies**:
[MakeMyTrip](https://leetcode.com/company/makemytrip)

**Related Topics**:  
[Hash Table](https://leetcode.com/tag/hash-table), [String](https://leetcode.com/tag/string), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming)

**Similar Questions**:
* [Longest Increasing Subsequence (Medium)](https://leetcode.com/problems/longest-increasing-subsequence)

**Hints**:
* How can you calculate the longest ideal subsequence that ends at a specific index i?
* Can you calculate it for all positions i? How can you use previously calculated answers to calculate the answer for the next position?

## Solution 1.

```cpp
// s[index] means it stores the ascii value
// 150 is used as there will 
// ('a' to 'z') ranges from 97 to 122
// ('A' to 'Z') ranges from 65 to 90.

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(150, -1)); 
        return solve(s, 0, 0, k, dp); // Start recursion from index 0 with prev = 0
    }

    int solve(string& s, int index, int prev, int& k, vector<vector<int>>& dp) {
        // Base case: if we reach the end of the string, return 0
        if (index >= s.size()) {
            return 0;
        }

        if (dp[index][prev] != -1) {
            return dp[index][prev];
        }

        int include = 0, exclude = 0;

        // Check if the current character can be included in the ideal string
        if (prev == 0 || abs(s[index] - prev) <= k) {
            include = 1 + solve(s, index + 1, s[index], k, dp); // Include current character
        }

        // Exclude the current character and move to the next index
        exclude = solve(s, index + 1, prev, k, dp);

        return dp[index][prev] = max(include, exclude);
    }
};
```

## Solution 2. Tabulation
```cpp
// We calculate the whole dp table here, for all the prev for 0 to 149 unlike in memoization

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(150, 0)); 

        // Iterate from the end of the string to the beginning
        for (int index = n - 1; index >= 0; index--) {
            for (int prev = 0; prev < 150; prev++) {
                int include = 0, exclude = 0;

                // Check if the current character can be included
                if (prev == 0 || abs(s[index] - prev) <= k) {
                    include = 1 + dp[index + 1][s[index]]; // Include current character
                }

                // Exclude the current character
                exclude = dp[index + 1][prev];

                // Store the result in the DP table
                dp[index][prev] = max(include, exclude);
            }
        }

        // The result is the maximum length starting from index 0 with prev = 0
        return dp[0][0];
    }
};
```

## Solution 3. Space Optimization
```cpp
class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        vector<int> curr(150, 0);
        vector<int> next(150, 0);

        for (int index = n - 1; index >= 0; index--) {
            for (int prev = 0; prev < 150; prev++) {
                int include = 0, exclude = 0;

                if (prev == 0 || abs(s[index] - prev) <= k) {
                    include = 1 + next[s[index]];
                }

                exclude = next[prev];
                curr[prev] = max(include, exclude);
            }
            next = curr;
        }

        return curr[0];
    }
};
```
