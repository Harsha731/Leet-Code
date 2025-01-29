# [691. Stickers to Spell Word (Hard)](https://leetcode.com/problems/stickers-to-spell-word/)

<p>
We are given N different types of stickers.  Each sticker has a lowercase English word on it.
</p><p>
You would like to spell out the given <code>target</code> string by cutting individual letters from your collection of stickers and rearranging them.
</p><p>
You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
</p><p>
What is the minimum number of stickers that you need to spell out the <code>target</code>?  If the task is impossible, return -1.
</p>

<p><b>Example 1:</b></p>
<p>Input:</p><pre>["with", "example", "science"], "thehat"
</pre><p></p>

<p>Output:</p><pre>3
</pre><p></p>

<p>Explanation:</p><pre>We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
</pre><p></p>

<p><b>Example 2:</b></p>
<p>Input:</p><pre>["notice", "possible"], "basicbasic"
</pre><p></p>

<p>Output:</p><pre>-1
</pre><p></p>

<p>Explanation:</p><pre>We can't form the target "basicbasic" from cutting letters from the given stickers.
</pre><p></p>

<p><b>Note:</b>
</p><li><code>stickers</code> has length in the range <code>[1, 50]</code>.</li>
<li><code>stickers</code> consists of lowercase English words (without apostrophes).</li>
<li><code>target</code> has length in the range <code>[1, 15]</code>, and consists of lowercase English letters.</li>
<li>In all test cases, all words were chosen <u>randomly</u> from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.</li>
<li>The time limit may be more challenging than usual.  It is expected that a 50 sticker test case can be solved within 35ms on average.</li>
<p></p>

**Related Topics**:  
[Dynamic Programming](https://leetcode.com/tag/dynamic-programming/), [Backtracking](https://leetcode.com/tag/backtracking/)

**Similar Questions**:
* [Ransom Note (Easy)](https://leetcode.com/problems/ransom-note/)

## Solution 1. Bitmask DP

```cpp
// OJ: https://leetcode.com/problems/stickers-to-spell-word/
// Author: github.com/lzl124631x
// Time: O(2^T * S * T)
// Space: O(2^T)
// Ref: https://leetcode.com/problems/stickers-to-spell-word/solution/
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int N = target.size();
        vector<int> dp(1 << N, -1);
        dp[0] = 0;
        for (int state = 0; state < 1 << N; ++state) { // a state represents the target characters matched
            if (dp[state] == -1) continue; // this state is not reachable
            for (auto &s : stickers) { // try each sticker
                int next = state;
                for (char c : s) { // for each character in the current sticker
                    for (int i = 0; i < N; ++i) {
                        if ((next >> i) & 1) continue; // if the current target character set doesn't contain the target[i], skip
                        if (target[i] == c) {
                            next |= 1 << i; // if they are matched, we can update the next state reachable
                            break;
                        }
                    }
                }
                if (dp[next] == -1 || dp[next] > dp[state] + 1) dp[next] = dp[state] + 1;
            }
        }
        return dp[(1 << N) - 1];
    }
};
```

```cpp

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        // Frequency array for the target string
        vector<int> targetFreq(26, 0);
        for (char c : target) {
            targetFreq[c - 'a']++;
        }

        // Frequency arrays for each sticker
        vector<vector<int>> stickerFreq(stickers.size(), vector<int>(26, 0));
        for (const auto& sticker : stickers) {
            for (char c : sticker) {
                stickerFreq[&sticker - &stickers[0]][c - 'a']++;
            }
        }

        // BFS queue to store remaining target frequencies
        queue<vector<int>> myQueue;
        myQueue.push(targetFreq);

        int ans = 0; // Number of stickers used
        unordered_set<string> visited; // To avoid revisiting states

        while (!myQueue.empty()) {
            int currentLevelSize = myQueue.size(); // Size of current BFS level
            for (int k = 0; k < currentLevelSize; k++) {
                vector<int> curFreq = myQueue.front();
                myQueue.pop();

                // Convert current frequency array to a string for visited check
                string curStr;
                for (int j = 0; j < 26; j++) {
                    curStr += string(curFreq[j], 'a' + j);
                }

                // If no characters are left, return the answer
                if (curStr.empty()) {
                    return ans;
                }

                // Skip if this state has already been visited
                if (visited.count(curStr)) continue;
                visited.insert(curStr);

                // Try applying each sticker to the current state
                for (int i = 0; i < stickers.size(); i++) {
                    if (stickerFreq[i][curStr[0] - 'a'] > 0) { // Only consider stickers that can help
                        vector<int> nextFreq = curFreq; // Copy current frequency array
                        for (char c : stickers[i]) {
                            if (nextFreq[c - 'a'] > 0) {
                                nextFreq[c - 'a']--; // Reduce covered letters
                            }
                        }
                        myQueue.push(nextFreq); // Push updated frequency array
                        //** We are not using another sticker for the nextFreq, instead we are using for the curFreq. 
                        // We push the nextFreq and do ans++ (or level++)
                    }
                }
            }
            ans++; // Increment sticker count after processing a level
        }

        return -1; // Return -1 if target cannot be formed
    }
};
/*
Why vector<int> is stored in queue ?
We are interested in dealing with frequencies, so if we insert string, then we have to again convert the string into frequency array to compute
So, we insert the fixed type of string for each frequency array (only one will be there) into visited array

if (stickerFreq[i][curStr[0] - 'a'] > 0) // Only consider stickers that can help
We want to remove the first letter at present, after this gets removed
we try to remove others, they may be removed with the same sticker or different sticker
So, we can ignore some stickers instanly without traversing through each character in sticker
*/
/*
The time complexity of the algorithm can be estimated by considering the following:

1. State Space: The breadth of the BFS can be approximated as 2^n, where n is the
length of the target string. This is because there are 2^n possible states in the worst
case (each character in the target can either be covered or not).

2. Processing Each State: For each state, the algorithm iterates over all stickers (let m
be the number of stickers). For each sticker, it processes its characters to update the
frequency array. The average length of a sticker is denoted as k.
3. Character Matching: During this process, for each sticker, the algorithm attempts to
match characters to the target's remaining characters, which can involve checking up
to n characters in total.

4. Counter Operations: The frequency counting and updating operations take O(k)
time for each sticker.

5. Overall Complexity: Therefore, the worst-case time complexity is:

O(2^n .m .n.k)

This assumes that every character in the target could potentially be matched with
characters from a sticker, representing a worst-case scenario for operations needed.

Space Complexity
The space complexity of the algorithm is determined by:

1. Visited States: The `visited` set tracks whether a state has been processed and
has a size of O(2^n), as it stores unique representations of all possible states.
2. Queue Storage: The BFS queue (`myQueue`) can also store up to O(2^n) states in the
worst case, corresponding to all possible configurations of remaining characters.

3. Sticker Frequency Arrays: The frequency arrays for stickers (`stickerFreq`) require
O(m . 26) space, where 26 represents the number of letters in the alphabet.
4. Target Frequency Array: The `targetFreq' array requires O(26) space.
5. Dominant Factor: However, since both `visited' and `myQueue` dominate the space
usage with their O(2^n) requirements, we conclude that:

O(2^n)

is the overall space complexity of the algorithm.
*/
```
