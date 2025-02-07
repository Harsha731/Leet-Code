# [39. Combination Sum (Medium)](https://leetcode.com/problems/combination-sum/)

<p>Given an array of <strong>distinct</strong> integers <code>candidates</code> and a target integer <code>target</code>, return <em>a list of all <strong>unique combinations</strong> of </em><code>candidates</code><em> where the chosen numbers sum to </em><code>target</code><em>.</em> You may return the combinations in <strong>any order</strong>.</p>

<p>The <strong>same</strong> number may be chosen from <code>candidates</code> an <strong>unlimited number of times</strong>. Two combinations are unique if the frequency of at least one of the chosen numbers is different.</p>

<p>It is <strong>guaranteed</strong> that the number of unique combinations that sum up to <code>target</code> is less than <code>150</code> combinations for the given input.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> candidates = [2,3,6,7], target = 7
<strong>Output:</strong> [[2,2,3],[7]]
<strong>Explanation:</strong>
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> candidates = [2,3,5], target = 8
<strong>Output:</strong> [[2,2,2,2],[2,3,3],[3,5]]
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> candidates = [2], target = 1
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= candidates.length &lt;= 30</code></li>
	<li><code>1 &lt;= candidates[i] &lt;= 200</code></li>
	<li>All elements of <code>candidates</code> are <strong>distinct</strong>.</li>
	<li><code>1 &lt;= target &lt;= 500</code></li>
</ul>


**Companies**:  
[Facebook](https://leetcode.com/company/facebook), [Amazon](https://leetcode.com/company/amazon), [Airbnb](https://leetcode.com/company/airbnb), [Microsoft](https://leetcode.com/company/microsoft), [Apple](https://leetcode.com/company/apple), [Snapchat](https://leetcode.com/company/snapchat), [Adobe](https://leetcode.com/company/adobe), [Goldman Sachs](https://leetcode.com/company/goldman-sachs), [Salesforce](https://leetcode.com/company/salesforce)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Backtracking](https://leetcode.com/tag/backtracking/)

**Similar Questions**:
* [Letter Combinations of a Phone Number (Medium)](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)
* [Combination Sum II (Medium)](https://leetcode.com/problems/combination-sum-ii/)
* [Combinations (Medium)](https://leetcode.com/problems/combinations/)
* [Combination Sum III (Medium)](https://leetcode.com/problems/combination-sum-iii/)
* [Factor Combinations (Medium)](https://leetcode.com/problems/factor-combinations/)
* [Combination Sum IV (Medium)](https://leetcode.com/problems/combination-sum-iv/)

## Solution 1. Backtracking

```cpp
// OJ: https://leetcode.com/problems/combination-sum
// Author: github.com/lzl124631x
// Time: O(N^(T/M+1)) where N is the length of A, T is target and M is the minimum value of A[i]
// Space: O(T/M)
// backtracking

class Solution {
public:
    vector<vector<int>> ans;

    void solve(int i, vector<int>& arr, vector<int>& temp, int target) {
        if (target == 0) {
            ans.push_back(temp);
            return;
        }
        if (target < 0) return;
        if (i == arr.size()) return;

        solve(i + 1, arr, temp, target);

        temp.push_back(arr[i]);
        solve(i, arr, temp, target - arr[i]);
        temp.pop_back();
    }

    vector<vector<int>> combinationSum(vector<int>& arr, int target) {
        ans.clear();
        vector<int> temp;
        solve(0, arr, temp, target);
        return ans;
    }
};
```

## Solution 2. Backtracking

```cpp
// OJ: https://leetcode.com/problems/combination-sum
// Author: github.com/lzl124631x
// Time: O(N^(T/M+1)) where N is the length of A, T is target and M is the minimum value of A[i]
// Space: O(T/M)
class Solution {
private:
    void dfs(int start, int target, vector<int>& A, vector<vector<int>>& ans, vector<int>& tmp) {
        if (target == 0) {
            ans.push_back(tmp);
            return;
        }
        if (target < 0) return;

        for (int i = start; i < A.size(); ++i) {
            tmp.push_back(A[i]);
            dfs(i, target - A[i], A, ans, tmp);
            tmp.pop_back(); // Backtrack
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& A, int target) {
        vector<vector<int>> ans;
        vector<int> tmp;
        dfs(0, target, A, ans, tmp);
        return ans;
    }
};

```
