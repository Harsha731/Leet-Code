# [71. Simplify Path (Medium)](https://leetcode.com/problems/simplify-path/)

<p>Given a string <code>path</code>, which is an <strong>absolute path</strong> (starting with a slash <code>'/'</code>) to a file or directory in a Unix-style file system, convert it to the simplified <strong>canonical path</strong>.</p>

<p>In a Unix-style file system, a period <code>'.'</code> refers to the current directory, a double period <code>'..'</code> refers to the directory up a level, and any multiple consecutive slashes (i.e. <code>'//'</code>) are treated as a single slash <code>'/'</code>. For this problem, any other format of periods such as <code>'...'</code> are treated as file/directory names.</p>

<p>The <strong>canonical path</strong> should have the following format:</p>

<ul>
	<li>The path starts with a single slash <code>'/'</code>.</li>
	<li>Any two directories are separated by a single slash <code>'/'</code>.</li>
	<li>The path does not end with a trailing <code>'/'</code>.</li>
	<li>The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period <code>'.'</code> or double period <code>'..'</code>)</li>
</ul>

<p>Return <em>the simplified <strong>canonical path</strong></em>.</p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> path = "/home/"
<strong>Output:</strong> "/home"
<strong>Explanation:</strong> Note that there is no trailing slash after the last directory name.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> path = "/../"
<strong>Output:</strong> "/"
<strong>Explanation:</strong> Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> path = "/home//foo/"
<strong>Output:</strong> "/home/foo"
<strong>Explanation:</strong> In the canonical path, multiple consecutive slashes are replaced by a single one.
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= path.length &lt;= 3000</code></li>
	<li><code>path</code> consists of English letters, digits, period <code>'.'</code>, slash <code>'/'</code> or <code>'_'</code>.</li>
	<li><code>path</code> is a valid absolute Unix path.</li>
</ul>


**Companies**:  
[Facebook](https://leetcode.com/company/facebook), [Google](https://leetcode.com/company/google), [Amazon](https://leetcode.com/company/amazon), [VMware](https://leetcode.com/company/vmware)

**Related Topics**:  
[String](https://leetcode.com/tag/string/), [Stack](https://leetcode.com/tag/stack/)

## Solution 1.
```cpp
class Solution {
public:
    string simplifyPath(string p) {
        stack<string> s; // Directory stack
        string r; // Result
        
        for (int i = 0; i < p.size(); ++i) {
            if (p[i] == '/') continue; // Skip '/'
            
            string t; // Current dir
            while (i < p.size() && p[i] != '/') {
                t += p[i];
                ++i;
            }       // We find the variable name and then process it
            
            if (t == ".") continue; // Ignore '.'
            else if (t == "..") {
                if (!s.empty()) s.pop(); // Move up
            } else {
                s.push(t); // Add dir
            }
        }
        
        while (!s.empty()) {
            r = "/" + s.top() + r; // Build path
            s.pop();
        }
        
        return r.size() ? r : "/"; // Return path
    }
};
```

## Solution 1.

```cpp
// OJ: https://leetcode.com/problems/simplify-path/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(N)
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        string res, temp;
        stringstream p(path);
        
        while (getline(p, temp, '/')) {
            if (temp == "" or temp == ".") continue;
            if (!stack.empty() && temp == "..")
                stack.pop_back();
            else if (temp != "..")
                stack.push_back(temp);
        }
        
        for (auto s : stack)
            res += "/" + s;
        
        return stack.empty() ? "/" : res;
    }
};
```
