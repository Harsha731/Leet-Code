# [552. Student Attendance Record II (Hard)](https://leetcode.com/problems/student-attendance-record-ii/)

<p>Given a positive integer <b>n</b>, return the number of all possible attendance records with length n, which will be regarded as rewardable. The answer may be very large, return it after mod 10<sup>9</sup> + 7.</p>

<p>A student attendance record is a string that only contains the following three characters:</p>

<p>
</p><ol>
<li><b>'A'</b> : Absent. </li>
<li><b>'L'</b> : Late.</li>
<li> <b>'P'</b> : Present. </li>
</ol>
<p></p>

<p>
A record is regarded as rewardable if it doesn't contain <b>more than one 'A' (absent)</b> or <b>more than two continuous 'L' (late)</b>.</p>

<p><b>Example 1:</b><br>
</p><pre><b>Input:</b> n = 2
<b>Output:</b> 8 
<b>Explanation:</b>
There are 8 records with length 2 will be regarded as rewardable:
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" won't be regarded as rewardable owing to more than one absent times. 
</pre>
<p></p>

<p><b>Note:</b>
The value of <b>n</b> won't exceed 100,000.
</p>




**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Student Attendance Record I (Easy)](https://leetcode.com/problems/student-attendance-record-i/)

## Solution 1. Simulation

At each step, we have 3 options, append 'A', 'L', or 'P'.

Let `v[i][A][L]` is the number of all possible records that have `i + 1` charactors and only have `A` 'A's and consecutive `L` 'L's.

Assume we are visiting `v[i][A][L]` and `v[i][A][L] = val`.

If we append 'A', then the next state will be `[i + 1][A + 1][0]`, so `v[i + 1][A + 1][0] += val`. Note that we can't do this if `A == 1`.

If we append 'L', then the next state will be `[i + 1][A][L + 1]`, so `v[i + 1][A][L + 1] += val`. Note that we can't do this if `L == 2`.

If we append 'P', then the next state will be `[i + 1][A][0]`, so `v[i + 1][A][0] += val`.

```cpp
// OJ: https://leetcode.com/problems/student-attendance-record-ii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
// OJ: https://leetcode.com/problems/student-attendance-record-ii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    int checkRecord(int n) {
        const long long MOD = 1e9 + 7;
        // v[i][A][L] represents the number of valid records of length i
        // with A absences and L consecutive late days
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int A = 0; A <= 1; ++A) {
                for (int L = 0; L <= 2; ++L) {
                    if (A + L > i + 1) continue;

                    int val = (i == 0) ? 1 : dp[i][A][L];

                    // Append 'P' (Present) to records
                    dp[i + 1][A][0] = (dp[i + 1][A][0] + val) % MOD;

                    // Append 'A' (Absent) to records if we can add an additional absence
                    if (A != 1) {
                        dp[i + 1][A + 1][0] = (dp[i + 1][A + 1][0] + val) % MOD;
                    }

                    // Append 'L' (Late) to records if we can add another late day
                    if (L != 2) {
                        dp[i + 1][A][L + 1] = (dp[i + 1][A][L + 1] + val) % MOD;
                    }

                    // If it's the last day, add the valid records to the result
                    if (i == n - 1) {
                        ans = (ans + val) % MOD;
                    }
                }
            }
        }
        
        return ans;
    }
};
```

## Solution 2. Simulation + Space Optimization

Since only two layers are related (`i` and `i + 1`), we can reduce the array from `N * 2 * 3` to `2 * 2 * 3`.

```cpp
// OJ: https://leetcode.com/problems/student-attendance-record-ii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
// OJ: https://leetcode.com/problems/student-attendance-record-ii/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int checkRecord(int n) {
        const long long MOD = 1e9 + 7;
        
        // Initialize DP tables for the previous and current states
        vector<vector<int>> prev(2, vector<int>(3, 0));
        vector<vector<int>> curr(2, vector<int>(3, 0));
        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            // Reset the current DP table
            for (int A = 0; A <= 1; ++A) {
                for (int L = 0; L <= 2; ++L) {
                    curr[A][L] = 0;
                }
            }

            for (int A = 0; A <= 1; ++A) {
                for (int L = 0; L <= 2; ++L) {
                    if (A + L > i + 1) continue;

                    int val = (i == 0) ? 1 : prev[A][L];

                    // Append 'P' (Present) to records
                    curr[A][0] = (curr[A][0] + val) % MOD;

                    // Append 'A' (Absent) to records if we can add an additional absence
                    if (A != 1) {
                        curr[A + 1][0] = (curr[A + 1][0] + val) % MOD;
                    }

                    // Append 'L' (Late) to records if we can add another late day
                    if (L != 2) {
                        curr[A][L + 1] = (curr[A][L + 1] + val) % MOD;
                    }

                    // Update the result if it's the last day
                    if (i == n - 1) {
                        ans = (ans + val) % MOD;
                    }
                }
            }

            // Swap prev and curr
            swap(prev, curr);
        }

        return ans;
    }
};
```

## Solution 3. Memoization
```cpp
class Solution {
    const long long MOD = 1e9 + 7;

    // Memoization table: dp[i][A][L]
    // Represents the number of valid records of length i with A absences and L consecutive late days
    vector<vector<vector<int>>> memo;

    int solve(int i, int A, int L) {
        if (i == 0) return 1; // Base case: empty record is valid
        if (memo[i][A][L] != -1) return memo[i][A][L]; // Return cached result

        long long result = 0;

        // Append 'P' (Present)
        result = (result + solve(i - 1, A, 0)) % MOD;

        // Append 'A' (Absent) if we can add an additional absence
        if (A < 1) {
            result = (result + solve(i - 1, A + 1, 0)) % MOD;
        }

        // Append 'L' (Late) if we can add another late day
        if (L < 2) {
            result = (result + solve(i - 1, A, L + 1)) % MOD;
        }

        return memo[i][A][L] = result; // Cache and return the result
    }

public:
    int checkRecord(int n) {
        // Initialize memoization table with -1 (uncomputed)
        memo.assign(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

        // Start solving for records of length n with 0 absences and 0 consecutive late days
        return solve(n, 0, 0);
    }
};
```
