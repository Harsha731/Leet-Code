# [1405. Longest Happy String (Medium)](https://leetcode.com/problems/longest-happy-string/)

<p>A string is called <em>happy</em> if it does&nbsp;not have any of the strings <code>'aaa'</code>, <code>'bbb'</code>&nbsp;or <code>'ccc'</code>&nbsp;as a substring.</p>

<p>Given three integers <code>a</code>, <code>b</code> and <code>c</code>, return <strong>any</strong> string <code>s</code>,&nbsp;which satisfies following conditions:</p>

<ul>
	<li><code>s</code> is <em>happy&nbsp;</em>and longest possible.</li>
	<li><code>s</code> contains <strong>at most</strong> <code>a</code>&nbsp;occurrences of the letter&nbsp;<code>'a'</code>, <strong>at most</strong> <code>b</code>&nbsp;occurrences of the letter <code>'b'</code> and <strong>at most</strong> <code>c</code> occurrences of the letter <code>'c'</code>.</li>
	<li><code>s&nbsp;</code>will only contain <code>'a'</code>, <code>'b'</code> and <code>'c'</code>&nbsp;letters.</li>
</ul>

<p>If there is no such string <code>s</code>&nbsp;return the empty string <code>""</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> a = 1, b = 1, c = 7
<strong>Output:</strong> "ccaccbcc"
<strong>Explanation:</strong> "ccbccacc" would also be a correct answer.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> a = 2, b = 2, c = 1
<strong>Output:</strong> "aabbc"
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> a = 7, b = 1, c = 0
<strong>Output:</strong> "aabaa"
<strong>Explanation:</strong> It's the only correct answer in this case.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>0 &lt;= a, b, c &lt;= 100</code></li>
	<li><code>a + b + c &gt; 0</code></li>
</ul>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Greedy](https://leetcode.com/tag/greedy/)

## Solution 1. Greedy

Not explained why even on LC editorial

```cpp
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        int curra = 0, currb = 0, currc = 0;
        // Maximum total iterations possible is given by the sum of a, b and c.
        int totalIterations = a + b + c;
        string ans = "";

        for (int i = 0; i < totalIterations; i++) {
            if ((a >= b and a >= c and curra != 2) || (a > 0 and (currb == 2 or currc == 2))) {
                // If 'a' is maximum and it's streak is less than 2, or if streak of 'b' or 'c' is 2, then 'a' will be the next character.
                ans += 'a';
                a--;
                curra++;
                currb = 0;
                currc = 0;
            } else if ((b >= a and b >= c and currb != 2) || (b > 0 and (currc == 2 or curra == 2))) {
                // If 'b' is maximum and it's streak is less than 2, or if streak of 'a' or 'c' is 2, then 'b' will be the next character.
                ans += 'b';
                b--;
                currb++;
                curra = 0;
                currc = 0;
            } else if ((c >= a and c >= b and currc != 2) || (c > 0 and (curra == 2 or currb == 2))) {
                // If 'c' is maximum and it's streak is less than 2, or if streak of 'a' or 'b' is 2, then 'c' will be the next character.
                ans += 'c';
                c--;
                currc++;
                curra = 0;
                currb = 0;
            }
        }
        return ans;
    }
};
```

## Solution 2. Priority Queue approach

```cpp
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if (a > 0) pq.push({a, 'a'});
        if (b > 0) pq.push({b, 'b'});
        if (c > 0) pq.push({c, 'c'});

        string result = "";

        while (!pq.empty()) {
            // Get the character with the most count.
            auto [count1, char1] = pq.top();
            pq.pop();

            if (result.size() >= 2 && result.back() == char1 && result[result.size() - 2] == char1) {
                if (pq.empty()) break;  // No valid characters left.

                auto [count2, char2] = pq.top();
                pq.pop();

                result += char2;
                count2--;

                if (count2 > 0) pq.push({count2, char2});

                pq.push({count1, char1});
            } else {
                result += char1;
                count1--;

                if (count1 > 0) pq.push({count1, char1});
            }
        }
        return result;
    }
};
```
