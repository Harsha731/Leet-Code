# [2140. Solving Questions With Brainpower (Medium)](https://leetcode.com/problems/solving-questions-with-brainpower/)

<p>You are given a <strong>0-indexed</strong> 2D integer array <code>questions</code> where <code>questions[i] = [points<sub>i</sub>, brainpower<sub>i</sub>]</code>.</p>

<p>The array describes the questions of an exam, where you have to process the questions <strong>in order</strong> (i.e., starting from question <code>0</code>) and make a decision whether to <strong>solve</strong> or <strong>skip</strong> each question. Solving question <code>i</code> will <strong>earn</strong> you <code>points<sub>i</sub></code> points but you will be <strong>unable</strong> to solve each of the next <code>brainpower<sub>i</sub></code> questions. If you skip question <code>i</code>, you get to make the decision on the next question.</p>

<ul>
	<li>For example, given <code>questions = [[3, 2], [4, 3], [4, 4], [2, 5]]</code>:

	<ul>
		<li>If question <code>0</code> is solved, you will earn <code>3</code> points but you will be unable to solve questions <code>1</code> and <code>2</code>.</li>
		<li>If instead, question <code>0</code> is skipped and question <code>1</code> is solved, you will earn <code>4</code> points but you will be unable to solve questions <code>2</code> and <code>3</code>.</li>
	</ul>
	</li>
</ul>

<p>Return <em>the <strong>maximum</strong> points you can earn for the exam</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> questions = [[3,2],[4,3],[4,4],[2,5]]
<strong>Output:</strong> 5
<strong>Explanation:</strong> The maximum points can be earned by solving questions 0 and 3.
- Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
- Unable to solve questions 1 and 2
- Solve question 3: Earn 2 points
Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
<strong>Output:</strong> 7
<strong>Explanation:</strong> The maximum points can be earned by solving questions 1 and 4.
- Skip question 0
- Solve question 1: Earn 2 points, will be unable to solve the next 2 questions
- Unable to solve questions 2 and 3
- Solve question 4: Earn 5 points
Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more points.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= questions.length &lt;= 10<sup>5</sup></code></li>
	<li><code>questions[i].length == 2</code></li>
	<li><code>1 &lt;= points<sub>i</sub>, brainpower<sub>i</sub> &lt;= 10<sup>5</sup></code></li>
</ul>


**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [House Robber (Medium)](https://leetcode.com/problems/house-robber/)
* [Frog Jump (Hard)](https://leetcode.com/problems/frog-jump/)

## Solution 1. DP Tabulation

```cpp
// OJ: https://leetcode.com/problems/solving-questions-with-brainpower/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    long long mostPoints(vector<vector<int>>& A) {
        int n = A.size();
        vector<long long> dp(n + 1, 0); // DP array: dp[i] = max points starting from question i

        // Traverse from the last question to the first
        for (int i = n - 1; i >= 0; --i) {
            int points = A[i][0]; // Points for current question
            int brainpower = A[i][1]; // Brainpower for current question

            // Calculate the next question after skipping brainpower questions
            int nextQuestion = i + brainpower + 1;

            // If next question is out of bounds, set it to n
            if (nextQuestion >= n) nextQuestion = n;

            // Choose max between solving or skipping the current question
            dp[i] = max(points + dp[nextQuestion], dp[i + 1]);
        }

        // Result is the max points starting from the first question
        return dp[0];
    }
};
```

Or

## Memoization
```cpp
// OJ: https://leetcode.com/problems/solving-questions-with-brainpower/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    long long solve(int i, vector<vector<int>>& A, vector<long long>& dp) {
        if (i >= A.size()) return 0;
        if (dp[i] != -1) return dp[i];
        int next = min(i + A[i][1] + 1, (int)A.size());
        dp[i] = max(solve(i + 1, A, dp), A[i][0] + solve(next, A, dp));
        return dp[i];
    }

    long long mostPoints(vector<vector<int>>& A) {
        int n = A.size();
        vector<long long> dp(n, -1);
        return solve(0, A, dp);
    }
};

```
