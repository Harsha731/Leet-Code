# [1335. Minimum Difficulty of a Job Schedule (Hard)](https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/)

<p>You want to schedule a list of jobs in <code>d</code> days. Jobs are dependent (i.e To work on the <code>i-th</code> job, you have to finish all the jobs <code>j</code> where <code>0 &lt;= j &lt; i</code>).</p>

<p>You have to finish <strong>at least</strong> one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the <code>d</code> days. The difficulty of a day is the maximum difficulty of a job done in that day.</p>

<p>Given an array of integers <code>jobDifficulty</code> and an integer <code>d</code>. The difficulty of the <code>i-th</code>&nbsp;job is&nbsp;<code>jobDifficulty[i]</code>.</p>

<p>Return <em>the minimum difficulty</em> of a job schedule. If you cannot find a schedule for the jobs return <strong>-1</strong>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/01/16/untitled.png" style="width: 365px; height: 230px;">
<pre><strong>Input:</strong> jobDifficulty = [6,5,4,3,2,1], d = 2
<strong>Output:</strong> 7
<strong>Explanation:</strong> First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7 
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> jobDifficulty = [9,9,9], d = 4
<strong>Output:</strong> -1
<strong>Explanation:</strong> If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> jobDifficulty = [1,1,1], d = 3
<strong>Output:</strong> 3
<strong>Explanation:</strong> The schedule is one job per day. total difficulty will be 3.
</pre>

<p><strong>Example 4:</strong></p>

<pre><strong>Input:</strong> jobDifficulty = [7,1,7,1,7,1], d = 3
<strong>Output:</strong> 15
</pre>

<p><strong>Example 5:</strong></p>

<pre><strong>Input:</strong> jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
<strong>Output:</strong> 843
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= jobDifficulty.length &lt;= 300</code></li>
	<li><code>0 &lt;=&nbsp;jobDifficulty[i] &lt;= 1000</code></li>
	<li><code>1 &lt;= d &lt;= 10</code></li>
</ul>

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. DP
```cpp
/*
Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).    
Input Validation:
Check if the number of jobs N is less than the number of days D. If so, return -1 because it's impossible to schedule the jobs.
memo[d][idx] means

i) Base Case:
If d == 1, it means there's only one day left. Compute the maximum difficulty of all remaining jobs from idx to N-1 and return it.

ii) Recursive Case:
Iterate over all possible partitions for the current day:
For each partition point i (from idx to N - d), compute the maximum difficulty of jobs from idx to i (this represents the difficulty of the current day).
Recursively compute the minimum difficulty for the remaining jobs (i + 1 to N-1) over the remaining d - 1 days.
Track the minimum sum of the current day's difficulty and the recursive result.
Store the result in the memoization table and return it.
```

```cpp
// OJ: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
// Author: github.com/lzl124631x
// Time: O(N^2 * D)
// Space: O(ND)
class Solution {
public:
    int minDifficulty(vector<int>& A, int D) {
        int N = A.size();
        if (D > N) return -1;

        // Initialize memoization table with -1 (uncomputed)
        vector<vector<int>> memo(D + 1, vector<int>(N, -1));

        // Call the helper function
        return helper(A, D, 0, memo);
    }

private:
    int helper(vector<int>& A, int d, int idx, vector<vector<int>>& memo) {
        int N = A.size();

        // If we have already computed this subproblem, return the result
        if (memo[d][idx] != -1) return memo[d][idx];

        // Base case: only one day left, so we have to do all remaining jobs
        if (d == 1) {
            int maxVal = 0;
            for (int i = idx; i < N; ++i) {
                maxVal = max(maxVal, A[i]);
            }
            return memo[d][idx] = maxVal;
        }

        int minDiff = INT_MAX;
        int currMax = 0;

        // Try all possible partitions for the current day
        for (int i = idx; i <= N - d; ++i) {
            currMax = max(currMax, A[i]);
            int nextDiff = helper(A, d - 1, i + 1, memo);
            minDiff = min(minDiff, currMax + nextDiff);
        }

        // Store the result in the memo table
        return memo[d][idx] = minDiff;
    }
};

```

## Solution 2. DP

We can compute the `mx` while computing `dp` instead of computing `mx` array beforehand.

```cpp
// OJ: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
// Author: github.com/lzl124631x
// Time: O(N^2 * D)
// Space: O(ND)

class Solution {
public:
    int minDifficulty(vector<int>& A, int D) {
        int N = A.size(); // Get the number of jobs
        if (D > N) return -1; // If there are more days than jobs, it's impossible

        // dp[d][i] will hold the minimum difficulty to schedule the first i jobs in d days
        vector<vector<long long>> dp(D + 1, vector<long long>(N, 1e9));

        // Base case: for 1 day, the difficulty is the maximum of the jobs up to i
        for (int i = 0; i < N; ++i) 
            dp[1][i] = i == 0 ? A[0] : max(dp[1][i - 1], (long long)A[i]);      // Important line

        // Fill the dp array for each day starting from the 2nd day
        for (int d = 2; d <= D; ++d) {
            for (int i = d - 1; i < N; ++i) { // Ensure we have enough jobs for the days. i.e, for d=3 => 3 jobs, we take dp[][2] onwards
                int currMax = 0;  // To store the maximum value in the current subarray
                // Iterate backwards to find the best partition point
                for (int j = i; j >= d - 1; --j) {
                    currMax = max(currMax, A[j]);  // Update the maximum for the current subarray
                    // Update the dp value considering the current partition
                    dp[d][i] = min(dp[d][i], dp[d - 1][j - 1] + currMax);
                }
            }
        }

        return dp[D][N - 1]; // Return the minimum difficulty for D days with all jobs
    }
};

```

## Solution 3. DP

Since `dp[d][i]` is dependent on `dp[d-1][j-1]` and `j <= i`, we can flip the loop direction and just need 1D `dp` array.

```cpp
// OJ: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
// Author: github.com/lzl124631x
// Time: O(NND)
// Space: O(N)
class Solution {
public:
    int minDifficulty(vector<int>& A, int D) {
        int N = A.size();
        if (D > N) return -1;

        // Initialize dp arrays with large values
        vector<long long> prev(N, 1e9), curr(N, 1e9);

        // Initialize the prev array for the first day
        for (int i = 0; i < N; ++i) prev[i] = i == 0 ? A[0] : max(prev[i - 1], (long long)A[i]);

        // Fill the dp array for each day
        for (int d = 2; d <= D; ++d) {
            // Reset curr for the current day
            fill(curr.begin(), curr.end(), 1e9);
            
            for (int i = d - 1; i < N; ++i) {
                int currMax = 0;  // To store the maximum value in the current subarray
                for (int j = i; j >= d - 1; --j) {
                    currMax = max(currMax, A[j]);  // Update the maximum for the current subarray
                    curr[i] = min(curr[i], prev[j - 1] + currMax);
                }
            }
            
            // Move current row to previous row for the next day
            swap(prev, curr);
        }

        return prev[N - 1];
    }
};
```

## Solution 4. DP + Monotonic Min Stack

TODO
https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/discuss/490316/JavaC%2B%2BPython3-DP-O(nd)-Solution

https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/discuss/495000/C%2B%2B-0ms!-O(d*n)-time-O(n)-space.-DP-%2B-MonotonicMinimum-Stack
