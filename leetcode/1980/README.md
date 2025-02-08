# [1980. Find Unique Binary String (Medium)](https://leetcode.com/problems/find-unique-binary-string)

<p>Given an array of strings <code>nums</code> containing <code>n</code> <strong>unique</strong> binary strings each of length <code>n</code>, return <em>a binary string of length </em><code>n</code><em> that <strong>does not appear</strong> in </em><code>nums</code><em>. If there are multiple answers, you may return <strong>any</strong> of them</em>.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [&quot;01&quot;,&quot;10&quot;]
<strong>Output:</strong> &quot;11&quot;
<strong>Explanation:</strong> &quot;11&quot; does not appear in nums. &quot;00&quot; would also be correct.
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [&quot;00&quot;,&quot;01&quot;]
<strong>Output:</strong> &quot;11&quot;
<strong>Explanation:</strong> &quot;11&quot; does not appear in nums. &quot;10&quot; would also be correct.
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [&quot;111&quot;,&quot;011&quot;,&quot;001&quot;]
<strong>Output:</strong> &quot;101&quot;
<strong>Explanation:</strong> &quot;101&quot; does not appear in nums. &quot;000&quot;, &quot;010&quot;, &quot;100&quot;, and &quot;110&quot; would also be correct.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>n == nums.length</code></li>
	<li><code>1 &lt;= n &lt;= 16</code></li>
	<li><code>nums[i].length == n</code></li>
	<li><code>nums[i] </code>is either <code>&#39;0&#39;</code> or <code>&#39;1&#39;</code>.</li>
	<li>All the strings of <code>nums</code> are <strong>unique</strong>.</li>
</ul>


**Related Topics**:  
[Array](https://leetcode.com/tag/array), [String](https://leetcode.com/tag/string), [Backtracking](https://leetcode.com/tag/backtracking)

**Similar Questions**:
* [Missing Number (Easy)](https://leetcode.com/problems/missing-number)
* [Find All Numbers Disappeared in an Array (Easy)](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array)
* [Random Pick with Blacklist (Hard)](https://leetcode.com/problems/random-pick-with-blacklist)

**Hints**:
* We can convert the given strings into base 10 integers.
* Can we use recursion to generate all possible strings?

## Solution 1.

```cpp
class Solution {
public:
    unordered_set<string> numsSet;
    
    string generate(string curr, int n) {
        if (curr.size() == n) {
            // Return if unique, else empty
            return numsSet.find(curr) == numsSet.end() ? curr : "";
        }
        
        // Try appending '0'
        string addZero = generate(curr + "0", n);
        if (!addZero.empty()) return addZero; // Found a unique string
        
        // If '0' doesn't work, try appending '1'
        return generate(curr + "1", n);
    }
    
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size(); 
        for (const auto& s : nums) numsSet.insert(s); 
        return generate("", n); 
    }
};

/*
Time complexity: O(n^2)
We require O(n^2) to convert nums to a hash set.
Due to the optimization, we check O(n) binary strings in our recursion. At each call, we perform some string concatenation 
operations, which costs up to O(n) (unless you have mutable strings like in C++).

Space complexity: O(n)
The recursion call stack when generating strings grows to a size of O(n). The hash set uses O(n) space.
*/
```

## Solution 2. Iterate Over Integer Equivalents
```cpp
// Time: O(N^2)
// Space: O(N)
class Solution {
    public:
        string findDifferentBinaryString(vector<string>& A) {
            int n = A.size();
            unordered_set<int> s; // Store the integer representation of strings in A
            for (auto &str : A) s.insert(stoi(str, 0, 2)); // Convert binary string to integer and insert into set
            for (int i = 0; i <= n; ++i) {
                if (s.count(i)) continue; // If i is present in set, continue to next number
    
                string ans(n, '0');  // Initialize the answer string with '0's. Size n
                int len = n;        // store n for easier access
                
                //Convert i to binary string of length n
                for (int j = 0; j < n; ++j) ans[len - j - 1] = '0' + (i >> j & 1); 
                return ans; // Return the unique binary string
            }
            return ""; // Should not reach here if a solution exists.
        }
    };
```

## Solution 3. Cantor's Diagonal Argument
```cpp

/*
Time complexity: O(n)
Space complexity: O(1)

Since ans differs from each string in nums at least at one position, it is guaranteed to be unique and not present in nums.
*/

class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        string ans;
        for (int i = 0; i < nums.size(); i++) {
            char curr = nums[i][i];
            ans += curr == '0' ? '1' : '0';
        }
        
        return ans;
    }
};
```
