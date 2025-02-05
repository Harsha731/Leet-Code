# [17. Letter Combinations of a Phone Number (Medium)](https://leetcode.com/problems/letter-combinations-of-a-phone-number)

<p>Given a string containing digits from <code>2-9</code> inclusive, return all possible letter combinations that the number could represent. Return the answer in <strong>any order</strong>.</p>
<p>A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.</p>
<img alt="" src="https://assets.leetcode.com/uploads/2022/03/15/1200px-telephone-keypad2svg.png" style="width: 300px; height: 243px;">
<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<pre><strong>Input:</strong> digits = "23"
<strong>Output:</strong> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
</pre>
<p><strong class="example">Example 2:</strong></p>
<pre><strong>Input:</strong> digits = ""
<strong>Output:</strong> []
</pre>
<p><strong class="example">Example 3:</strong></p>
<pre><strong>Input:</strong> digits = "2"
<strong>Output:</strong> ["a","b","c"]
</pre>
<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>
<ul>
	<li><code>0 &lt;= digits.length &lt;= 4</code></li>
	<li><code>digits[i]</code> is a digit in the range <code>['2', '9']</code>.</li>
</ul>

**Companies**:
[Amazon](https://leetcode.com/company/amazon), [Apple](https://leetcode.com/company/apple), [Google](https://leetcode.com/company/google)

**Related Topics**:  
[Hash Table](https://leetcode.com/tag/hash-table/), [String](https://leetcode.com/tag/string/), [Backtracking](https://leetcode.com/tag/backtracking/)

**Similar Questions**:
* [Generate Parentheses (Medium)](https://leetcode.com/problems/generate-parentheses/)
* [Combination Sum (Medium)](https://leetcode.com/problems/combination-sum/)
* [Binary Watch (Easy)](https://leetcode.com/problems/binary-watch/)
* [Count Number of Texts (Medium)](https://leetcode.com/problems/count-number-of-texts/)

## Solution 1. Backtracking - DFS kind

```cpp
// OJ: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Author: github.com/lzl124631x
/*
outer loop - O(n)
inner loop - 4^n combinations
Total - O(4^n)

SC - worst case - stores all - O(4^n)
*/
class Solution {
public:
    void solve(int i, string& s, string digits, vector<string> v, vector<string>& ans){
        if(i==digits.length()) {
            ans.push_back(s);
            return;
        }
        int a = digits[i]-'0';
        a = a-2;
        for(int j=0;j<v[a].size();j++){
            s.push_back(v[a].at(j)); // Push the character into the string
            solve(i+1, s, digits, v, ans); // Pass the modified string to the recursive call
            s.pop_back(); // Backtrack: remove the last character added   
        }   
    }

    vector<string> letterCombinations(string digits) {
        vector<string> v = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        string s = "";
        if(digits=="") return ans;
        solve(0, s, digits, v, ans);
        return ans;
    }
};
```

## Solution 2. ITerative

```cpp
// OJ: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Author: github.com/lzl124631x
// Time: O(4^N * N)
// Space: O(4^N)

/*
outer loop - O(n)
inner loop - 4^n combinations
Total - O(4^n)

SC - worst case - stores all - O(4^n)
*/

class Solution {
private:
    vector<string> M{ "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> ans{""};
        for (char c : digits) {
            vector<string> next;
            string m = M[c - '2'];
            for (string s : ans) {
                for (char c : m) {
                    next.push_back(s + c);
                }
            }
            ans = next;
        }
        return ans;
    }
};
```
