# [1049. Last Stone Weight II (Medium)](https://leetcode.com/problems/last-stone-weight-ii/)

<p>You are given an array of integers <code>stones</code> where <code>stones[i]</code> is the weight of the <code>i<sup>th</sup></code> stone.</p>

<p>We are playing a game with the stones. On each turn, we choose any two stones and smash them together. Suppose the stones have weights <code>x</code> and <code>y</code> with <code>x &lt;= y</code>. The result of this smash is:</p>

<ul>
	<li>If <code>x == y</code>, both stones are destroyed, and</li>
	<li>If <code>x != y</code>, the stone of weight <code>x</code> is destroyed, and the stone of weight <code>y</code> has new weight <code>y - x</code>.</li>
</ul>

<p>At the end of the game, there is <strong>at most one</strong> stone left.</p>

<p>Return <em>the smallest possible weight of the left stone</em>. If there are no stones left, return <code>0</code>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> stones = [2,7,4,1,8,1]
<strong>Output:</strong> 1
<strong>Explanation:</strong>
We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> stones = [31,26,33,21,40]
<strong>Output:</strong> 5
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> stones = [1,2]
<strong>Output:</strong> 1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= stones.length &lt;= 30</code></li>
	<li><code>1 &lt;= stones[i] &lt;= 100</code></li>
</ul>


**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

```cpp
This question is same as DP on subseqeunces - striver - Partition Set Into 2 Subsets With Min Absolute Sum Diff (DP-16)
Here, We do 1 + 2 - 4 + 6 - 2 - 3 simply
So, 2 partitions are needed here
```

```cpp
// Memoization
/*
Time Complexity (TC): The TC is O(n . totalSum), where n is the number of elements and totalSum is the sum of all
elements, as we solve n · totalSum subproblems.

Space Complexity (SC): The SC is O(n . totalSum), due to the memoization table storing results for all subproblems. The
recursion stack uses O(n) space, which is dominated by the memoization table.
*/
int solve(int i, int sumA, int sumB, vector<int>& nums, vector<vector<int>>& dp) {
    // Base case: If all elements are processed, return the absolute difference
    if (i == nums.size()) {
        return abs(sumA - sumB);
    }

    if (dp[i][sumA] != -1) {
        return dp[i][sumA];
    }

    // Include the current element in subset A
    int includeInA = solve(i + 1, sumA + nums[i], sumB, nums, dp);

    // Include the current element in subset B
    int includeInB = solve(i + 1, sumA, sumB + nums[i], nums, dp);

    return dp[i][sumA] = min(includeInA, includeInB);
}

int minSubsetSumDifference(vector<int>& nums, int n) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));
    return solve(0, 0, 0, nums, dp);
}
```
_________________________________________

```cpp
// Tabulation

int minSubsetSumDifference(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int num : arr) {
        totalSum += num;
    }

    // Initialize DP array
    vector<bool> dp(totalSum + 1, false);
    dp[0] = true;

    // Fill the DP array
    for (int i = 0; i < n; i++) {
        for (int j = totalSum; j >= arr[i]; j--) {
            dp[j] = dp[j] || dp[j - arr[i]];
        }
    }

    // Find the largest j <= totalSum / 2 for which dp[j] is true
    int minDiff = INT_MAX;
    for (int j = totalSum / 2; j >= 0; j--) {
        if (dp[j]) {
            minDiff = totalSum - 2 * j;
            break;
        }
    }

    return minDiff;
}
```
_________________________________________

```cpp
// Space Optimization

int minSubsetSumDifference(vector<int>& arr, int n) {
    int totalSum = accumulate(arr.begin(), arr.end(), 0);

    // Initialize DP arrays
    vector<bool> prev(totalSum + 1, false);
    vector<bool> curr(totalSum + 1, false);
    prev[0] = true; // A sum of 0 is always possible with 0 elements

    // Fill the DP arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= totalSum; j++) {
            // Exclude the current element
            curr[j] = prev[j];
            // Include the current element
            if (j >= arr[i]) {
                curr[j] = curr[j] || prev[j - arr[i]];
            }
        }
        // Swap prev and curr for the next iteration
        swap(prev, curr);
    }

    // Find the largest j <= totalSum / 2 for which prev[j] is true
    int minDiff = INT_MAX;
    for (int j = totalSum / 2; j >= 0; j--) {
        if (prev[j]) {
            minDiff = totalSum - 2 * j;
            break;
        }
    }

    return minDiff;
}
```
