# [629. K Inverse Pairs Array (Hard)](https://leetcode.com/problems/k-inverse-pairs-array/)

<p>
Given two integers <code>n</code> and <code>k</code>, find how many different arrays consist of numbers from <code>1</code> to <code>n</code> such that there are exactly <code>k</code> inverse pairs. 
</p>
<p>
We define an inverse pair as following:
For <code>i<sub>th</sub></code> and <code>j<sub>th</sub></code> element in the array, if <code>i</code> &lt; <code>j</code> and <code>a[i]</code> &gt; <code>a[j]</code> then it's an inverse pair; Otherwise, it's not.
</p>

<p>
Since the answer may be very large, the answer should be modulo 10<sup>9</sup> + 7.
</p>

<p><b>Example 1:</b><br>
</p><pre><b>Input:</b> n = 3, k = 0
<b>Output:</b> 1
<b>Explanation:</b> 
Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
</pre>
<p></p>

<p><b>Example 2:</b><br>
</p><pre><b>Input:</b> n = 3, k = 1
<b>Output:</b> 2
<b>Explanation:</b> 
The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
</pre>
<p></p>

<p><b>Note:</b><br>
</p><ol>
<li>The integer <code>n</code> is in the range [1, 1000] and <code>k</code> is in the range [0, 1000].</li>
</ol>
<p></p>

**Companies**:  
[Works Applications](https://leetcode.com/company/works-applications)

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

## Solution 1.
```cpp
/*
Intuition :
Let's say we have n elements in our permutation then Depending on where we put the element (n+1) in our permutation, we may add 0, 1, 2, ..., n new inverse pairs. For example, if we have some permutation of 1...4, then:

5 x x x x creates 4 new inverse pairs
x 5 x x x creates 3 new inverse pairs
...
x x x x 5 creates 0 new inverse pairs

Approach : 
dp[n][k] = dp[n - 1][k - 0] + dp[n - 1][k - 1] + ... + dp[n - 1][k - (n - 1)]

Time complexity: O(n∗k∗k) to O(n∗k)
Space complexity:O(n∗k) to O(k)

Let dp[i][j] be the number ways to form j reverse pairs with i numbers.

If you place N in the last position (i = 0), it creates 0 new inverse pairs.            [Notice that it is i=0 for last position]
If you place N in the second-to-last position (i = 1), it creates 1 new inverse pair.
If you place N in the first position (i = N-1), it creates N-1 new inverse pairs.
However, you cannot create more than N-1 new inverse pairs by placing N in any position. 
Therefore, the maximum number of new inverse pairs you can create by placing N is N-1.
*/
```

```cpp
// OJ: https://leetcode.com/problems/k-inverse-pairs-array/
// Author: github.com/lzl124631x
// Time: O(N^2 * K)
// Space: O(N * K)
class Solution {
private:
    const int mod=int(1e9+7);
    int dp[1001][1001];
    int f(int n,int k) {
        //base case
        if(k<=0) return k==0;
        if(dp[n][k]!=-1) return dp[n][k];


        int ans=0;
        for(int i=0;i<n;++i) {
            ans+=f(n-1,k-i);
            ans%=mod;
        }
        return dp[n][k]=ans;
    }
public:
    int kInversePairs(int n, int k) {
        memset(dp,-1,sizeof(dp));
        return f(n,k);
    }
};
```

## Solution 2. Tabulation

```cpp
// Time: O(N * K * min(N, K))
// Space: O(N * K)

class Solution {
private:
    const int mod=int(1e9+7);
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        //base case
        for(int N=0;N<=n;++N) dp[N][0]=1;
        for(int N=1;N<=n;++N) {
            for(int K=0;K<=k;++K) {
                int ans=0;
                for(int i=0;i<min(N,K+1);++i) {
                    ans+=dp[N-1][K-i];
                    ans%=mod;
                }
                dp[N][K]=ans;
            }
        }
        return dp[n][k];
    }
};
```

## Solution 3. DP Time Optimized    

Denote `F(N, K)` as the result.

Observations:
* Valid range of `K` is `[0, N * (N - 1) / 2]`. `F(N, K) = 0` if `K` &notin; `[0, N * (N - 1) / 2]`.
* `F(N, 0) = F(N, N * (N - 1) / 2) = 1`.

For `F(N, K)`, let's pick 1, 2, ..., N as the first number:
* When 1 is picked, we need to compute `F(N - 1, K)`.
* When 2 is picked, we need to compute `F(N - 1, K - 1)`.
* ...
* When N is picked, we need to compute `F(N - 1, K - (N - 1))`.

Eventually `F(N, K) = Sum(F(N - 1, K) + F(N - 1, K - 1) + ... + F(N - 1, K - (N - 1))`.

We can use this formula to compute `F(n, K)` for `N = 1, 2, 3, ..., N`.

```cpp
// OJ: https://leetcode.com/problems/k-inverse-pairs-array/
// Author: github.com/lzl124631x
// Time: O(NK)
// Space: O(NK)
class Solution {
private:
    const int mod=int(1e9+7);
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        //base case
        for(int N=0;N<=n;++N) dp[N][0]=1;
        for(int N=1;N<=n;++N) {
            for(int K=0;K<=k;++K) {
                dp[N][K] = (dp[N - 1][K] + (K > 0 ? dp[N][K - 1] : 0)) % mod;
                dp[N][K] = (dp[N][K] + mod - (K >= N ? dp[N-1][K-N] : 0)) % mod;
            }
        }
        return dp[n][k];
    }
};
```

## Solution 4. DP Time + Space Optimization

```cpp
// OJ: https://leetcode.com/problems/k-inverse-pairs-array/
// Author: github.com/lzl124631x
// Time: O(NK)
// Space: O(K)
class Solution {
private:
    const int mod=int(1e9+7);
public:
    int kInversePairs(int n, int k) {
        vector<int> prev(k+1,0),curr(k+1,0);
        prev[0]=curr[0]=1;
        for(int N=1;N<=n;++N) {
            for(int K=0;K<=k;++K) {
                curr[K] = (prev[K] + (K > 0 ? curr[K - 1] : 0)) % mod;
                curr[K] = (curr[K] + mod - (K >= N ? prev[K-N] : 0)) % mod;
            }
            prev = curr;
        }
        return curr[k];
    }
};
```
