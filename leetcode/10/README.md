# [10. Regular Expression Matching (Hard)](https://leetcode.com/problems/regular-expression-matching/solution/)

<p>Given an input string (<code>s</code>) and a pattern (<code>p</code>), implement regular expression matching with support for <code>'.'</code> and <code>'*'</code>.</p>

<pre>'.' Matches any single character.
'*' Matches zero or more of the preceding element.
</pre>

<p>The matching should cover the <strong>entire</strong> input string (not partial).</p>

<p><strong>Note:</strong></p>

<ul>
	<li><code>s</code>&nbsp;could be empty and contains only lowercase letters <code>a-z</code>.</li>
	<li><code>p</code> could be empty and contains only lowercase letters <code>a-z</code>, and characters like&nbsp;<code>.</code>&nbsp;or&nbsp;<code>*</code>.</li>
</ul>

<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong>
s = "aa"
p = "a"
<strong>Output:</strong> false
<strong>Explanation:</strong> "a" does not match the entire string "aa".
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong>
s = "aa"
p = "a*"
<strong>Output:</strong> true
<strong>Explanation:</strong>&nbsp;'*' means zero or more of the preceding&nbsp;element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong>
s = "ab"
p = ".*"
<strong>Output:</strong> true
<strong>Explanation:</strong>&nbsp;".*" means "zero or more (*) of any character (.)".
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong>
s = "aab"
p = "c*a*b"
<strong>Output:</strong> true
<strong>Explanation:</strong>&nbsp;c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
</pre>

<p><strong>Example 5:</strong></p>

<pre><strong>Input:</strong>
s = "mississippi"
p = "mis*is*p*."
<strong>Output:</strong> false
</pre>


**Related Topics**:  
[String](https://leetcode.com/tag/string/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Backtracking](https://leetcode.com/tag/backtracking/)

**Similar Questions**:
* [Wildcard Matching (Hard)](https://leetcode.com/problems/wildcard-matching/)

## Solution 1. Memoization

```cpp

/*
Wild Card Matching : '*' Matches any sequence of characters (including the empty sequence).
?

Regular Expression Matching : '*' Matches zero or more of the preceding element.
. id used instead of ?

p has * and ? / .

*/

// TC : O(MN) and SC : O(MN)

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1)); // DP table for memoization
        return solve(0, 0, s, p, dp); // Start recursion from the beginning of both strings
    }

    bool solve(int i, int j, string& s, string& p, vector<vector<int>>& dp) {
        // Base case: if pattern is fully processed, check if string is also fully processed
        if (j == p.size()) {
            return i == s.size();
        }

        // If the result is already computed, return it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Check if the current characters match (or pattern has '.')
        bool isMatch = (i < s.size() && (s[i] == p[j] || p[j] == '.'));

        // Handle '*' in the pattern
        if (j + 1 < p.size() && p[j + 1] == '*') {
            // Two choices:
            // 1. Skip the '*' and its preceding character (match zero occurrences)
            // 2. Use the '*' to match one or more occurrences (if current characters match)
            dp[i][j] = solve(i, j + 2, s, p, dp) || (isMatch && solve(i + 1, j, s, p, dp));
        } else {
            // No '*', simply move to the next characters in both strings
            dp[i][j] = isMatch && solve(i + 1, j + 1, s, p, dp);
        }

        return dp[i][j];
    }
};
```

## Solution 2. Tabulation

```cpp
/*
The DP table must handle the case where the string s is empty (i = 0), but the pattern p is non-empty.
If s = "" and p = "a*"
So, we kept i=0 onwards in   for (int i = 0; i <= m; i++)
*/

// TC : O(MN) and SC : O(MN)

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false)); // DP table

        // Base case: empty string and empty pattern match
        dp[0][0] = true;

        // Fill the DP table
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // Case 1: '*' matches zero occurrences of the preceding character
                    dp[i][j] = dp[i][j - 2];
                    // Case 2: '*' matches one or more occurrences of the preceding character
                    if (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else if (i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
                    // Current characters match, move to the next characters
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        // The result is whether the entire string matches the entire pattern
        return dp[m][n];
    }
};
```

## Solution 3. DP Space Optimization

```cpp

// TC : O(MN) and SC : O(N)

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<bool> prev(n + 1, false); // Represents dp[i-1][...]
        vector<bool> curr(n + 1, false); // Represents dp[i][...]

        // Base case: empty string and empty pattern match
        prev[0] = true;

        // Fill the DP table
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                // '*' can match zero occurrences of the preceding character
                prev[j] = prev[j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // Case 1: '*' matches zero occurrences of the preceding character
                    curr[j] = curr[j - 2];
                    // Case 2: '*' matches one or more occurrences of the preceding character
                    if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        curr[j] = curr[j] || prev[j];
                    }
                } else if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    // Current characters match, move to the next characters
                    curr[j] = prev[j - 1];
                } else {
                    // Characters don't match
                    curr[j] = false;
                }
            }
            // Update prev to curr for the next iteration
            prev = curr;
            fill(curr.begin(), curr.end(), false); // Reset curr
        }

        // The result is whether the entire string matches the entire pattern
        return prev[n];
    }
};
```

