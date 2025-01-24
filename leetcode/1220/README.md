# [1220. Count Vowels Permutation (Hard)](https://leetcode.com/problems/count-vowels-permutation/)

<p>Given an integer <code>n</code>, your task is to count how many strings of length <code>n</code> can be formed under the following rules:</p>

<ul>
	<li>Each character is a lower case vowel&nbsp;(<code>'a'</code>, <code>'e'</code>, <code>'i'</code>, <code>'o'</code>, <code>'u'</code>)</li>
	<li>Each vowel&nbsp;<code>'a'</code> may only be followed by an <code>'e'</code>.</li>
	<li>Each vowel&nbsp;<code>'e'</code> may only be followed by an <code>'a'</code>&nbsp;or an <code>'i'</code>.</li>
	<li>Each vowel&nbsp;<code>'i'</code> <strong>may not</strong> be followed by another <code>'i'</code>.</li>
	<li>Each vowel&nbsp;<code>'o'</code> may only be followed by an <code>'i'</code> or a&nbsp;<code>'u'</code>.</li>
	<li>Each vowel&nbsp;<code>'u'</code> may only be followed by an <code>'a'.</code></li>
</ul>

<p>Since the answer&nbsp;may be too large,&nbsp;return it modulo <code>10^9 + 7.</code></p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> n = 1
<strong>Output:</strong> 5
<strong>Explanation:</strong> All possible strings are: "a", "e", "i" , "o" and "u".
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> n = 2
<strong>Output:</strong> 10
<strong>Explanation:</strong> All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
</pre>

<p><strong>Example 3:&nbsp;</strong></p>

<pre><strong>Input:</strong> n = 5
<strong>Output:</strong> 68</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= n &lt;= 2 * 10^4</code></li>
</ul>


**Companies**:  
[Amazon](https://leetcode.com/company/amazon)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1. Memoization

```cpp
class Solution {
    const int MOD = 1e9 + 7;
    const unordered_map<char, vector<char>> mappings{ {'s', {'a', 'e', 'i', 'o', 'u'} }, // start
                                                      {'a', {'e'}                     }, 
                                                      {'e', {'a', 'i'}                }, 
                                                      {'i', {'a', 'e', 'o', 'u'}      }, 
                                                      {'o', {'i', 'u'}                },
                                                      {'u', {'a'}                     }  };
    unordered_map<char, vector<int>> dp;

public:
    int countVowelPermutation(int n) {
        dp['s'] = dp['a'] = dp['e'] = dp['i'] = dp['o'] = dp['u'] = vector<int>(n+1);
        return solve(n, 's');                         // start with s
    }
    int solve(int rem, char prev) {
        if(rem == 0) return 1;                        // no need to pick further. We have formed 1 string of length = n.
        if(dp[prev][rem]) return dp[prev][rem];       // if result already calculated for current state, directly return it
        for(auto c : mappings.at(prev))               // try each vowel allowed after prev character
            dp[prev][rem] = (dp[prev][rem] + solve(rem - 1, c)) % MOD;  
        return dp[prev][rem];
    }
};
/*
Time Complexity : O(N), we will be calculating the total possible strings for a given vowels when rem characters are requried, only once. 
Thus, each vowel will make a max of N recursive calls. Hence the total time complexity becomes O(5*N) = O(N)
Space Complexity : O(N), O(N) space is required by recursive stack. Further, a total of O(5*N) space is used by dp. 
Thus the total space complexity becomes O(N) + O(5*N) = O(N)
*/
```


## Solution 2. Tabulation 

```cpp
0 (a)       =>  1
1 (e)       =>  0 / 2
2 (i)       =>  0 / 1 / 3 / 4
3 (o)       =>  2 / 4
4 (u)       =>  0

class Solution {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;
        long dp[5][n+1], ans = 0;
        dp[0][1] = dp[1][1] = dp[2][1] = dp[3][1] = dp[4][1] = 1;
        for(int i = 2; i <= n; i++) {
            dp[0][i] =  dp[1][i-1];
            dp[1][i] = (dp[0][i-1] + dp[2][i-1]) % MOD;
            dp[2][i] = (dp[0][i-1] + dp[1][i-1] + dp[3][i-1] + dp[4][i-1]) % MOD;
            dp[3][i] = (dp[2][i-1] + dp[4][i-1]) % MOD;
            dp[4][i] =  dp[0][i-1];
        }
        for(int i=0; i < 5; i++) 
            ans = (ans + dp[i][n]) % MOD;
        return ans;
    }
};

// Time Complexity : O(N)
// Space Complexity : O(N)
```

## Solution 3. Space Optimization 

```cpp
class Solution {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;
        long a = 1, e = 1, i = 1, o = 1, u = 1, a_new, e_new, i_new, o_new, u_new;
        for(int j = 2; j <= n; j++) {
            a_new =  e;
            e_new = (a + i) % MOD;
            i_new = (a + e + o + u) % MOD;
            o_new = (i + u) % MOD;
            u_new =  a;
            a = a_new, e = e_new, i = i_new, o = o_new, u = u_new;
        }
        return (a + e + i + o + u) % MOD;
    }
};

// Time Complexity : O(N)
// Space Complexity : O(1)
```
