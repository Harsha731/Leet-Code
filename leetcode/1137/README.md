# [1137. N-th Tribonacci Number (Easy)](https://leetcode.com/problems/n-th-tribonacci-number/)

<p>The Tribonacci sequence T<sub>n</sub> is defined as follows:&nbsp;</p>

<p>T<sub>0</sub> = 0, T<sub>1</sub> = 1, T<sub>2</sub> = 1, and T<sub>n+3</sub> = T<sub>n</sub> + T<sub>n+1</sub> + T<sub>n+2</sub> for n &gt;= 0.</p>

<p>Given <code>n</code>, return the value of T<sub>n</sub>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> n = 4
<strong>Output:</strong> 4
<strong>Explanation:</strong>
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> n = 25
<strong>Output:</strong> 1389537
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>0 &lt;= n &lt;= 37</code></li>
	<li>The answer is guaranteed to fit within a 32-bit integer, ie. <code>answer &lt;= 2^31 - 1</code>.</li>
</ul>

**Companies**:  
[Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[Math](https://leetcode.com/tag/math/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Memoization](https://leetcode.com/tag/memoization/)

**Similar Questions**:
* [Climbing Stairs (Easy)](https://leetcode.com/problems/climbing-stairs/)
* [Fibonacci Number (Easy)](https://leetcode.com/problems/fibonacci-number/)

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/n-th-tribonacci-number/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;
        int a = 0, b = 1, c = 1;
        for (int i = 3; i <= n; ++i) {
            int next = a + b + c;
            a = b;
            b = c;
            c = next;
        }
        return c;
    }
};
```

## Solution 2. Tabulation

```cpp
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;

        // Create a table to store the Tribonacci numbers
        int dp[n + 1];

        // Base cases
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        // Fill the table iteratively
        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }

        // Return the nth Tribonacci number
        return dp[n];
    }
};
```

## Solution 3. Space Optimization

```cpp
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;

        // Initialize the first three Tribonacci numbers
        int a = 0, b = 1, c = 1;

        // Iterate to compute the nth Tribonacci number
        for (int i = 3; i <= n; ++i) {
            int next = a + b + c; // Compute the next Tribonacci number
            a = b; // Update a to b
            b = c; // Update b to c
            c = next; // Update c to the newly computed value
        }

        // Return the nth Tribonacci number
        return c;
    }
};
```
