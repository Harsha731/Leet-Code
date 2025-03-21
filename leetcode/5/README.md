# [5. Longest Palindromic Substring (Medium)](https://leetcode.com/problems/longest-palindromic-substring/)

<p>Given a string <code>s</code>, return&nbsp;<em>the longest palindromic substring</em> in <code>s</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> s = "babad"
<strong>Output:</strong> "bab"
<strong>Note:</strong> "aba" is also a valid answer.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> s = "cbbd"
<strong>Output:</strong> "bb"
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> s = "a"
<strong>Output:</strong> "a"
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> s = "ac"
<strong>Output:</strong> "a"
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 1000</code></li>
	<li><code>s</code> consist of only digits and English letters.</li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [Adobe](https://leetcode.com/company/adobe), [Apple](https://leetcode.com/company/apple), [Wayfair](https://leetcode.com/company/wayfair), [Facebook](https://leetcode.com/company/facebook), [Goldman Sachs](https://leetcode.com/company/goldman-sachs), [Oracle](https://leetcode.com/company/oracle), [Yahoo](https://leetcode.com/company/yahoo), [Google](https://leetcode.com/company/google), [Docusign](https://leetcode.com/company/docusign), [eBay](https://leetcode.com/company/ebay), [Uber](https://leetcode.com/company/uber), [Walmart Labs](https://leetcode.com/company/walmart-labs), [Salesforce](https://leetcode.com/company/salesforce), [Zoho](https://leetcode.com/company/zoho), [HBO](https://leetcode.com/company/hbo), [Tesla](https://leetcode.com/company/tesla)

**Related Topics**:  
[String](https://leetcode.com/tag/string/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Shortest Palindrome (Hard)](https://leetcode.com/problems/shortest-palindrome/)
* [Palindrome Permutation (Easy)](https://leetcode.com/problems/palindrome-permutation/)
* [Palindrome Pairs (Hard)](https://leetcode.com/problems/palindrome-pairs/)
* [Longest Palindromic Subsequence (Medium)](https://leetcode.com/problems/longest-palindromic-subsequence/)
* [Palindromic Substrings (Medium)](https://leetcode.com/problems/palindromic-substrings/)

## Solution 1. Brute Force

```cpp

/* TC : O(n^3). Assume that n is the length of the input string, there are a total of C(n, 2) = n(n-1)/2 substrings (excluding the trivial solution where a character itself is a palindrome). Since verifying each substring takes O(n) time, the run time complexity is O(n^3).
Space complexity : O(1).
*/
class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.length() <= 1) {
            return s;
        }
        
        int max_len = 1;
        std::string max_str = s.substr(0, 1);
        
        for (int i = 0; i < s.length(); ++i) {
            for (int j = i + max_len; j <= s.length(); ++j) {
                if (j - i > max_len && isPalindrome(s.substr(i, j - i))) {
                    max_len = j - i;
                    max_str = s.substr(i, j - i);
                }
            }
        }

        return max_str;
    }

private:
    bool isPalindrome(const std::string& str) {
        int left = 0;
        int right = str.length() - 1;
        
        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }
            ++left;
            --right;
        }
        
        return true;
    }
};
```

## Solution 2. DP

Let `dp[i][j]` be `true` if `s[i..j]` is a palindrome. The answer is the substring of the longest length that has `dp[i][j] = true`.

```
dp[i][j] = true 
dp[i][j] = s[i] == s[j] && (i+1 > j-1 || dp[i+1][j-1])
```

```cpp
// OJ: https://leetcode.com/problems/longest-palindromic-substring/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N^2)
class Solution {
public:
    string longestPalindrome(string s) {
        int N = s.size(), start = 0, len = 0;
        bool dp[1001][1001] = {};
        for (int i = N - 1; i >= 0; --i) {
            for (int j = i; j < N; ++j) {
                if (i == j) dp[i][j] = true;
                else dp[i][j] = s[i] == s[j] && (i + 1 > j - 1 || dp[i + 1][j - 1]);
                if (dp[i][j] && j - i + 1 > len) {
                    start = i;
                    len = j - i + 1;
                }
            }
        }
        return s.substr(start, len);
    }
};
```

Since `dp[i][j]` only depends on `dp[i + 1][j - 1]`, we can reduce the space complexity from `O(N^2)` to `O(N)`.

```cpp
// OJ: https://leetcode.com/problems/longest-palindromic-substring/
// Author: github.com/lzl124631x
// Time: O(N^2)

// OJ: https://leetcode.com/problems/longest-palindromic-substring/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(N)
class Solution {
public:
    string longestPalindrome(string s) {
        int N = s.size(), start = 0, len = 0;
        bool dp[1001] = {};
        for (int i = N - 1; i >= 0; --i) {
            for (int j = N - 1; j >= i; --j) {
                if (i == j) dp[j] = true;
                else dp[j] = s[i] == s[j] && (i + 1 > j - 1 || dp[j - 1]);
                if (dp[j] && j - i + 1 > len) {
                    start = i;
                    len = j - i + 1;
                }
            }
        }
        return s.substr(start, len);
    }
};

```


## Solution 3. Expanding from Middle

```cpp
// OJ: https://leetcode.com/problems/longest-palindromic-substring/
// Author: github.com/lzl124631x
// Time: O(N^2)
// Space: O(1)
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.length() <= 1) {
            return s;
        }

        string max_str = s.substr(0, 1); // Initial longest palindrome is the first character

        for (int i = 0; i < s.length(); i++) {
            string odd = expand_from_center(s, i, i);       // Odd length palindrome
            string even = expand_from_center(s, i, i + 1);  // Even length palindrome

            if (odd.length() > max_str.length()) {
                max_str = odd;
            }
            if (even.length() > max_str.length()) {
                max_str = even;
            }
        }

        return max_str;
    }

private:
    string expand_from_center(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return s.substr(left + 1, right - left - 1);
    }
};
```

## Solution 3. Manacher

```cpp
// OJ: https://leetcode.com/problems/longest-palindromic-substring/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    string longestPalindrome(string s) {
        int N = s.size();
        string t = "^*";
        for (char c : s) {
            t += c;
            t += '*';
        }
        t += '$'; // inflating the `s` ( example: "abc" becomes "^*a*b*c*$" )
        int M = t.size();
        
        vector<int> r(M); // `r[i]` is the number of palindromes with `t[i]` as the center (aka. the radius of the longest palindrome centered at `t[i]`)
        r[1] = 1;
        int j = 1; // `j` is the index with the furthest reach `j + r[j]`
        for (int i = 2; i <= 2 * N; ++i) {
            int cur = j + r[j] > i ? min(r[2 * j - i], j + r[j] - i) : 1; // `t[2*j-i]` is the symmetry point to `t[i]`
            while (t[i - cur] == t[i + cur]) ++cur; // expanding the current radius
            if (i + cur > j + r[j]) j = i;
            r[i] = cur;
        }
        
        int len = 1, start = 0;
        for (int i = 2; i <= 2 * N; ++i) {
            if (r[i] - 1 > len) {
                len = r[i] - 1;
                start = (i - r[i]) / 2;
            }
        }
        return s.substr(start, len);
    }
};
```
