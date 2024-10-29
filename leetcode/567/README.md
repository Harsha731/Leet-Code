# [567. Permutation in String (Medium)](https://leetcode.com/problems/permutation-in-string/)

<p>Given two strings <code>s1</code> and <code>s2</code>, return <code>true</code><em> if </em><code>s2</code><em> contains a permutation of </em><code>s1</code><em>, or </em><code>false</code><em> otherwise</em>.</p>

<p>In other words, return <code>true</code> if one of <code>s1</code>'s permutations is the substring of <code>s2</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> s1 = "ab", s2 = "eidbaooo"
<strong>Output:</strong> true
<strong>Explanation:</strong> s2 contains one permutation of s1 ("ba").
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> s1 = "ab", s2 = "eidboaoo"
<strong>Output:</strong> false
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s1.length, s2.length &lt;= 10<sup>4</sup></code></li>
	<li><code>s1</code> and <code>s2</code> consist of lowercase English letters.</li>
</ul>


**Companies**:  
[Yandex](https://leetcode.com/company/yandex), [Amazon](https://leetcode.com/company/amazon), [Oracle](https://leetcode.com/company/oracle), [Facebook](https://leetcode.com/company/facebook), [Bloomberg](https://leetcode.com/company/bloomberg)

**Related Topics**:  
[Hash Table](https://leetcode.com/tag/hash-table/), [Two Pointers](https://leetcode.com/tag/two-pointers/), [String](https://leetcode.com/tag/string/), [Sliding Window](https://leetcode.com/tag/sliding-window/)

**Similar Questions**:
* [Minimum Window Substring (Hard)](https://leetcode.com/problems/minimum-window-substring/)
* [Find All Anagrams in a String (Medium)](https://leetcode.com/problems/find-all-anagrams-in-a-string/)


## Solution 1. Fixed-length Sliding Window

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s2.size()<s1.size()) return false;
        vector<int> w(26,0), h(26,0);
        for(int i = 0; i<s1.size(); i++){
            w[s1[i]-'a']+=1;
            h[s2[i]-'a']+=1;
        }
        if(w==h) return true;
        for(int i = s1.size(); i<s2.size(); i++){
            h[s2[i-s1.size()]-'a']--;
            h[s2[i]-'a']++;
            if(w==h) return true;
        }
        return false;
    }
};
```

## Solution 2. Variable-length Sliding Window

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s2.size() < s1.size()) return false;

        vector<int> w(26, 0), h(26, 0);
        int matchCount = 0;

        // Initialize frequency arrays and initial match count
        for (int i = 0; i < s1.size(); i++) {
            w[s1[i] - 'a']++;
            h[s2[i] - 'a']++;
        }

        // Calculate the initial match count
        for (int i = 0; i < 26; i++) {
            if (w[i] == h[i]) matchCount++;
        }

        // Sliding window over the rest of s2
        for (int i = s1.size(); i < s2.size(); i++) {
            if (matchCount == 26) return true;

            int right = s2[i] - 'a';
            int left = s2[i - s1.size()] - 'a';

            // Add the new character in the window (right side)
            h[right]++;
            if (h[right] == w[right]) matchCount++;
            else if (h[right] == w[right] + 1) matchCount--;

            // Remove the old character from the window (left side)
            h[left]--;
            if (h[left] == w[left]) matchCount++;
            else if (h[left] == w[left] - 1) matchCount--;
        }

        // Final check after the loop
        return matchCount == 26;
    }
};

```
