# [93. Restore IP Addresses (Medium)](https://leetcode.com/problems/restore-ip-addresses)

<p>A <strong>valid IP address</strong> consists of exactly four integers separated by single dots. Each integer is between <code>0</code> and <code>255</code> (<strong>inclusive</strong>) and cannot have leading zeros.</p>

<ul>
	<li>For example, <code>&quot;0.1.2.201&quot;</code> and <code>&quot;192.168.1.1&quot;</code> are <strong>valid</strong> IP addresses, but <code>&quot;0.011.255.245&quot;</code>, <code>&quot;192.168.1.312&quot;</code> and <code>&quot;192.168@1.1&quot;</code> are <strong>invalid</strong> IP addresses.</li>
</ul>

<p>Given a string <code>s</code> containing only digits, return <em>all possible valid IP addresses that can be formed by inserting dots into </em><code>s</code>. You are <strong>not</strong> allowed to reorder or remove any digits in <code>s</code>. You may return the valid IP addresses in <strong>any</strong> order.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;25525511135&quot;
<strong>Output:</strong> [&quot;255.255.11.135&quot;,&quot;255.255.111.35&quot;]
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;0000&quot;
<strong>Output:</strong> [&quot;0.0.0.0&quot;]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> s = &quot;101023&quot;
<strong>Output:</strong> [&quot;1.0.10.23&quot;,&quot;1.0.102.3&quot;,&quot;10.1.0.23&quot;,&quot;10.10.2.3&quot;,&quot;101.0.2.3&quot;]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= s.length &lt;= 20</code></li>
	<li><code>s</code> consists of digits only.</li>
</ul>


**Companies**:
[Yandex](https://leetcode.com/company/yandex), [TikTok](https://leetcode.com/company/tiktok), [Oracle](https://leetcode.com/company/oracle), [Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [Yahoo](https://leetcode.com/company/yahoo), [Google](https://leetcode.com/company/google), [Facebook](https://leetcode.com/company/facebook), [Apple](https://leetcode.com/company/apple), [ByteDance](https://leetcode.com/company/bytedance), [Cisco](https://leetcode.com/company/cisco), [Arista Networks](https://leetcode.com/company/arista-networks), [Verkada](https://leetcode.com/company/verkada)

**Related Topics**:  
[String](https://leetcode.com/tag/string), [Backtracking](https://leetcode.com/tag/backtracking)

**Similar Questions**:
* [IP to CIDR (Medium)](https://leetcode.com/problems/ip-to-cidr)

## Solution 1. Backtracking

Plain backtracking. Maximum depth is 4. Be aware of the cases where ip segment starts with `0` or ip segment is greater than `255`.

```cpp
class Solution {
    public:
        // Helper function to check if a given string is a valid IP address segment
        bool valid(string temp){
            if(temp.size()>3 || temp.size()==0) return false; // segment length should be between 1 and 3
            if(temp.size()>1 && temp[0]=='0')   return false; // segment should not start with 0, unless it is a single digit
            if(temp.size() && stoi(temp)>255) return false; // segment should not be greater than 255
            return true;
        }
    
        // Backtracking function to generate all possible IP addresses
        void solve(vector<string>& ans, string output, int ind, string s, int dots){
            if(dots == 3){ // if we have already added 3 dots, check if the remaining segment is valid
                if(valid(s.substr(ind)))
                    ans.push_back(output+s.substr(ind));
                return;
            }
            int sz = s.size();
            for(int i=ind;i<min(ind+3, sz);i++){
                if(valid(s.substr(ind, i-ind+1))){
                    output.push_back(s[i]);
                    output.push_back('.');
                    solve(ans, output, i+1, s, dots+1);
                    output.pop_back(); //backtrack
                }
            }
    
        }
    
        vector<string> restoreIpAddresses(string s) {
            vector<string> ans;
            string res;
            solve(ans, res, 0, s, 0);
            return ans;
        }
    };
```
