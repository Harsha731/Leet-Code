# [23. Merge k Sorted Lists (Hard)](https://leetcode.com/problems/merge-k-sorted-lists/)

<p>You are given an array of <code>k</code> linked-lists <code>lists</code>, each linked-list is sorted in ascending order.</p>

<p><em>Merge all the linked-lists into one sorted linked-list and return it.</em></p>

<p>&nbsp;</p>
<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> lists = [[1,4,5],[1,3,4],[2,6]]
<strong>Output:</strong> [1,1,2,3,4,4,5,6]
<strong>Explanation:</strong> The linked-lists are:
[
  1-&gt;4-&gt;5,
  1-&gt;3-&gt;4,
  2-&gt;6
]
merging them into one sorted list:
1-&gt;1-&gt;2-&gt;3-&gt;4-&gt;4-&gt;5-&gt;6
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> lists = []
<strong>Output:</strong> []
</pre>

<p><strong>Example 3:</strong></p>

<pre><strong>Input:</strong> lists = [[]]
<strong>Output:</strong> []
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>k == lists.length</code></li>
	<li><code>0 &lt;= k &lt;= 10^4</code></li>
	<li><code>0 &lt;= lists[i].length &lt;= 500</code></li>
	<li><code>-10^4 &lt;= lists[i][j] &lt;= 10^4</code></li>
	<li><code>lists[i]</code> is sorted in <strong>ascending order</strong>.</li>
	<li>The sum of <code>lists[i].length</code> won't exceed <code>10^4</code>.</li>
</ul>


**Companies**:  
[Facebook](https://leetcode.com/company/facebook), [Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [Google](https://leetcode.com/company/google), [ByteDance](https://leetcode.com/company/bytedance), [Yandex](https://leetcode.com/company/yandex), [Apple](https://leetcode.com/company/apple), [Adobe](https://leetcode.com/company/adobe), [VMware](https://leetcode.com/company/vmware), [Bloomberg](https://leetcode.com/company/bloomberg), [eBay](https://leetcode.com/company/ebay), [tiktok](https://leetcode.com/company/tiktok), [Indeed](https://leetcode.com/company/indeed), [Oracle](https://leetcode.com/company/oracle), [Walmart Labs](https://leetcode.com/company/walmart-labs), [Qualtrics](https://leetcode.com/company/qualtrics), [Sprinklr](https://leetcode.com/company/sprinklr), [Cruise Automation](https://leetcode.com/company/cruise-automation)

**Related Topics**:  
[Linked List](https://leetcode.com/tag/linked-list/), [Divide and Conquer](https://leetcode.com/tag/divide-and-conquer/), [Heap (Priority Queue)](https://leetcode.com/tag/heap-priority-queue/), [Merge Sort](https://leetcode.com/tag/merge-sort/)

**Similar Questions**:
* [Merge Two Sorted Lists (Easy)](https://leetcode.com/problems/merge-two-sorted-lists/)
* [Ugly Number II (Medium)](https://leetcode.com/problems/ugly-number-ii/)

## Solution 0. Brute Force
```cpp
// Using merge 2 lists approach

// TC : O(NK)
// SC : O(1)

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Base cases
        if (!list1) return list2;
        if (!list2) return list1;

        // Recursive merge logic
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;

        // Start with the first list
        ListNode* mergedList = lists[0];

        // Recursively merge each list into the current merged list
        for (int i = 1; i < lists.size(); i++) {
            mergedList = mergeTwoLists(mergedList, lists[i]);
        }

        return mergedList;
    }
};
```

## Solution 2. Divide And Conquer (Merge Sort)

```cpp
// OJ: https://leetcode.com/problems/merge-k-sorted-lists/
// Author: github.com/lzl124631x
// Time: O(NlogK)
// Space: O(1)

// Here, there are merging of k/2, k/4, k/8, ... which is logk
// But above is k

class Solution {
private:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode head, *tail = &head;
        while (a && b) {
            if (a->val < b->val) { tail->next = a; a = a->next; }
            else { tail->next = b; b = b->next; }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        return head.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        for (int N = lists.size(); N > 1; N = (N + 1) / 2) {
            for (int i = 0; i < N / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[N - 1 - i]);
            }
        }
        return lists[0];
    }
};
```

## Solution 3. Heap

```cpp
// OJ: https://leetcode.com/problems/merge-k-sorted-lists/
// Author: github.com/lzl124631x
// Time: O(NlogK)
// Space: O(K)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy, *tail = &dummy;
        auto cmp = [](auto a, auto b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        for (auto list : lists) {
            if (list) q.push(list); // avoid pushing NULL list.
        }
        while (q.size()) {
            auto node = q.top();
            q.pop();
            if (node->next) q.push(node->next);
            tail->next = node;
            tail = node;
        }
        return dummy.next;
    }
};
```
