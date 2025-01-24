# [221. Maximal Square (Medium)](https://leetcode.com/problems/maximal-square/)

<p>Given an <code>m x n</code> binary <code>matrix</code> filled with <code>0</code>'s and <code>1</code>'s, <em>find the largest square containing only</em> <code>1</code>'s <em>and return its area</em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg" style="width: 400px; height: 319px;">
<pre><strong>Input:</strong> matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
<strong>Output:</strong> 4
</pre>

<p><strong>Example 2:</strong></p>
<img alt="" src="https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg" style="width: 165px; height: 165px;">
<pre><strong>Input:</strong> matrix = [["0","1"],["1","0"]]
<strong>Output:</strong> 1
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> matrix = [["0"]]
<strong>Output:</strong> 0
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>m == matrix.length</code></li>
	<li><code>n == matrix[i].length</code></li>
	<li><code>1 &lt;= m, n &lt;= 300</code></li>
	<li><code>matrix[i][j]</code> is <code>'0'</code> or <code>'1'</code>.</li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon), [Visa](https://leetcode.com/company/visa), [Microsoft](https://leetcode.com/company/microsoft), [IBM](https://leetcode.com/company/ibm), [Google](https://leetcode.com/company/google), [Twitter](https://leetcode.com/company/twitter), [Apple](https://leetcode.com/company/apple), [Booking.com](https://leetcode.com/company/bookingcom), [Indeed](https://leetcode.com/company/indeed)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Matrix](https://leetcode.com/tag/matrix/)

**Similar Questions**:
* [Maximal Rectangle (Hard)](https://leetcode.com/problems/maximal-rectangle/)
* [Largest Plus Sign (Medium)](https://leetcode.com/problems/largest-plus-sign/)

## Solution 1. Brute Force

```cpp
/*
Solution - I (Optimized Brute-Force)

Instead of checking each possible side length for a square starting at a given cell, we can optimze the process by starting from row of 
that cell and expanding the side length for that row till it is possible. We will continue this for below rows as well, till consecutive 
ones found along rows (denoted by allOnesRowLen) > current row number.

The process is similar to the one shown in below diagram which I had used in my post for 85. Maximal Rectangle with only change that
we stop further iteration as soon as allOnesRowLen exceeds current row number (because we need to form square in this case & max 
possible side length is already know by now).
*/

// The (row, col) will be the first cell of the maximal square we are checking

class Solution {
public:
    int getMaxSquareLen(vector<vector<char>>& matrix, int row, int col) {
        int maxLen = min(matrix.size() - row, matrix[0].size() - col);
        int squareLen = 0;
        for (int i = 0; i < maxLen; i++) {
            int j;
            for (j = 0; j < maxLen && matrix[row + i][col + j] != '0'; j++);
            maxLen = j;
            squareLen = min(maxLen, i + 1);
        }
        return squareLen;
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSquare = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                maxSquare = max(maxSquare, getMaxSquareLen(matrix, row, col));
            }
        }
        return maxSquare * maxSquare;
    }
};

// TC : O(MN*min(M,N)^2)
// SC : O(1)
```

## Solution 2. Use the 1D subproblem

This problem is trivial on 1D array.

Let `row[i][j]` be the length of consecutive 1s ending at `A[i][j]` in `i`th row.

Let `col[i][j]` be the length of consecutive 1s ending at `A[i][j]` in `j`th column.

With these two arrays, for each `matrix[i][j]`, the side length of the square whose bottom right corner is at `matrix[i][j]` is at most `min(row[i][j], col[i][j])`. Then we keep probing the `col[i][k]` where `k < j` to keep tighten the limit.

```cpp
// OJ: https://leetcode.com/problems/maximal-square/
// Author: github.com/lzl124631x
// Time: O(M * N^2)
// Space: O(MN)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& A) {
        if (A.empty() || A[0].empty()) return 0;
        int M = A.size(), N = A[0].size(), ans = 0;
        vector<vector<int>> row(M, vector<int>(N, 0)), col(M, vector<int>(N, 0));
        for (int i = 0; i < M; ++i) {
            int start = -1;
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == '0') start = j;
                row[i][j] = j - start;
            }
        }
        for (int j = 0; j < N; ++j) {
            int start = -1;
            for (int i = 0; i < M; ++i) {
                if (A[i][j] == '0') start = i;
                col[i][j] = i - start;
            }
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int end = min(row[i][j], col[i][j]), k = 0;
                while (k < end) {
                    ++k;
                    if (j - k < 0) break;
                    end = min(end, col[i][j - k]);
                }
                ans = max(ans, k);
            }
        }
        return ans * ans;
    }
};
```

## Solution 3. Bottom-up DP

Let `dp[i + 1][j + 1]` be the side length of the maximal square whose bottom right corner is at `matrix[i][j]`. Then we have:

```
dp[i + 1][j + 1] = min(dp[i][j], dp[i][j + 1], dp[i + 1][j]) + 1
```

```cpp

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSquare = 0;
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1));

        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = 1 + min({dp[i + 1][j], dp[i][j + 1], dp[i + 1][j + 1]});
                    maxSquare = max(maxSquare, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        return maxSquare * maxSquare;
    }
};

// TC : O(MN)
// SC : O(MN)
```

## Solution 4. Bottom-up DP with Space Optimization

Given the dependency above, we can use a `2 * N` array to store the DP values.

```cpp

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSquare = 0;

        // Use two 1D arrays: prevDp for the previous row and currDp for the current row
        vector<int> prevDp(cols + 1);
        vector<int> currDp(cols + 1);

        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    // Compute the value for the current cell
                    currDp[j] = 1 + min({currDp[j + 1], prevDp[j], prevDp[j + 1]});
                    // Update the maximum square length found so far
                    maxSquare = max(maxSquare, currDp[j]);
                } else {
                    // Reset the value for the current cell if it's '0'
                    currDp[j] = 0;
                }
            }
            // Swap prevDp and currDp for the next iteration
            swap(prevDp, currDp);
        }

        return maxSquare * maxSquare;
    }
};

// Time Complexity : O(MN)
// Space Complexity : O(1)
```
