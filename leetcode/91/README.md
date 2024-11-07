# [91. Decode Ways (Medium)](https://leetcode.com/problems/decode-ways/)

<p>A message containing letters from <code>A-Z</code> is being encoded to numbers using the following mapping:</p>

<pre>'A' -&gt; 1
'B' -&gt; 2
...
'Z' -&gt; 26
</pre>

<p>Given a <strong>non-empty</strong> string containing only digits, determine the total number of ways to decode it.</p>

<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> "12"
<strong>Output:</strong> 2
<strong>Explanation:</strong>&nbsp;It could be decoded as "AB" (1 2) or "L" (12).
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> "226"
<strong>Output:</strong> 3
<strong>Explanation:</strong>&nbsp;It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).</pre>


**Companies**:  
[Facebook](https://leetcode.com/company/facebook), [Google](https://leetcode.com/company/google), [Microsoft](https://leetcode.com/company/microsoft), [Amazon](https://leetcode.com/company/amazon), [Salesforce](https://leetcode.com/company/salesforce), [Uber](https://leetcode.com/company/uber), [Yahoo](https://leetcode.com/company/yahoo)

**Related Topics**:  
[String](https://leetcode.com/tag/string/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Decode Ways II (Hard)](https://leetcode.com/problems/decode-ways-ii/)

## Solution 1. DP

Denote `dp[i]` as the result for substring `S[0..i]` (`i` &isin; `[0, N - 1]`).

For each letter `S[i]`, we have two options:
1. Use `S[i]` to decode. `S[i]` shouldn't be `'0'`.
2. Use `S[i - 1]` and `S[i]` to decode. `S[i - 1]` shouldn't be `'0'` and the number `S[i - 1]` and `S[i]` formed shouldn't be greater than 26.

When `dp[i] == 0`, we should stop right away and return 0.

```
dp[i] = 0
dp[i] += dp[i - 1]  if S[i] != '0'
dp[i] += dp[i - 2]  if i != 0 && S[i - 1] != '0' && (S[i - 1] - '0') * 10 + S[i] - '0' <= 26
```

Since `dp[i]` only depends on `dp[i - 1]` and `dp[i - 2]`. We can reduce the space to just two variables storing `dp[i - 1]` and `dp[i - 2]`.


## Solution 2. DP
```
// OJ: https://leetcode.com/problems/decode-ways
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:

    int memo(int i, int n, vector<int> &dp, string s) {
        if(i >= n) return 1;
        if(s[i]-'0' == 0) return 0;
        if(dp[i] != -1) return dp[i];
        int n1 = memo(i+1, n, dp, s);
        int n2 = 0;
        if(i+1 <= n-1 && (s[i]-'0') != 0 && (s[i]-'0')*10 + (s[i+1]-'0') <= 26) n2 = memo(i+2, n, dp, s);
        return dp[i] = n1 + n2; 
    }

    int numDecodings(string s) {
        int n = s.length();
        vector<int> dp (n+1, -1);
        return memo(0, n, dp, s);
    }
};
```

cpp
```
class Solution {
public:
    int numDecodings(const string& s) {
        int n = s.size();
        if (n == 0) return 0;
        vector<int> dp(n + 1, 0);

        // Base cases
        dp[0] = 1; // There's one way to decode an empty string
        if (s[0] != '0') {
            dp[1] = 1; // There's one way to decode a single non-'0' character
        }

        for (int pos = 2; pos <= n; ++pos) {
            int way1 = 0;
            int way2 = 0;

            // Check single character decoding
            if (s[pos - 1] != '0') {
                way1 = dp[pos - 1];
            }

            // Check two-character decoding
            string twoDigit = s.substr(pos - 2, 2);
            if (stoi(twoDigit) >= 10 && stoi(twoDigit) <= 26) {
                way2 = dp[pos - 2];
            }

            dp[pos] = way1 + way2;
        }

        return dp[n];
    }
};

```
