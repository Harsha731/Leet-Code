# [647. Palindromic Substrings (Medium)](https://leetcode.com/problems/palindromic-substrings/)

<p>Given a string <code>s</code>, return <em>the number of <strong>palindromic substrings</strong> in it</em>.</p>

<p>A string is a <strong>palindrome</strong> when it reads the same backward as forward.</p>

<p>A <strong>substring</strong> is a contiguous sequence of characters within the string.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> s = "abc"
<strong>Output:</strong> 3
<strong>Explanation:</strong> Three palindromic strings: "a", "b", "c".
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> s = "aaa"
<strong>Output:</strong> 6
<strong>Explanation:</strong> Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 1000</code></li>
	<li><code>s</code> consists of lowercase English letters.</li>
</ul>


**Companies**:  
[Facebook](https://leetcode.com/company/facebook), [Microsoft](https://leetcode.com/company/microsoft), [Salesforce](https://leetcode.com/company/salesforce), [Docusign](https://leetcode.com/company/docusign), [Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[String](https://leetcode.com/tag/string/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Longest Palindromic Substring (Medium)](https://leetcode.com/problems/longest-palindromic-substring/)
* [Longest Palindromic Subsequence (Medium)](https://leetcode.com/problems/longest-palindromic-subsequence/)

## Solution 1. Brute Force

```cpp

// TC : O(N^3) and SC : O(1)
// Because we have two for loops to iterate all possible substring and one loop to check if it is palindrome or not.

class Solution {

    public boolean isPalindrome(String s, int left, int right) {
        while(left < right) {
            if(s.charAt(left++) != s.charAt(right--)) return false;
        } 
        return true;
    }
    
    public int countSubstrings(String s) {
        int ans = 0;
        int n = s.length();
        for(int i=0;i<n;i++) {
            for(int j=i;j<n;j++) {
                if(isPalindrome(s, i, j)) ans++;
            }
        }
        return ans;
    }
}
```


## Solution 2. Better

```cpp

// TC : O(N^2) and SC : O(1)
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length(), ans = 0;
        for (int i = 0; i < n; ++i) {
            int even = palindromeCount(s, i, i + 1);
            int odd = palindromeCount(s, i, i);
            ans += even + odd;
        }
        return ans;
    }

    int palindromeCount(const string& s, int left, int right) {
        int count = 0;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            --left;
            ++right;
            ++count;
        }
        return count;
    }
};
```


## Solution 3. DP

```cpp

// TC : O(N^2) and SC : O(N^2)
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            palindrome[i][i] = true;
            ans++;
        }

        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                palindrome[i][i + 1] = true;
                ans++;
            }
        }

        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i < n - len + 1; ++i) {
                if (s[i] == s[i + len - 1] && palindrome[i + 1][i + len - 2]) {
                    palindrome[i][i + len - 1] = true;
                    ans++;
                }
            }
        }

        return ans;
    }
};
```

## Solution 4. Manacher

```cpp
// OJ: https://leetcode.com/problems/palindromic-substrings/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    int countSubstrings(string s) {
        string t = "^*";
        for (char c : s) {
            t += c;
            t += '*';
        }
        t += '$';
        int N = s.size(), M = t.size();
        vector<int> r(M);
        r[1] = 1;
        int j = 1, ans = 0;
        for (int i = 2; i <= 2 * N; ++i) {
            int cur = j + r[j] > i ? min(r[2 * j - i], j + r[j] - i) : 1;
            while (t[i - cur] == t[i + cur]) ++cur;
            if (i + cur > j + r[j]) j = i;
            r[i] = cur;
            ans += r[i] / 2;
        }
        return ans;
    }
};
```
