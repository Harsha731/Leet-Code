# [152. Maximum Product Subarray (Medium)](https://leetcode.com/problems/maximum-product-subarray/)

<p>Given an integer array&nbsp;<code>nums</code>, find the contiguous subarray within an array (containing at least one number) which has the largest product.</p>

<p><strong>Example 1:</strong></p>

<pre><strong>Input:</strong> [2,3,-2,4]
<strong>Output:</strong> <code>6</code>
<strong>Explanation:</strong>&nbsp;[2,3] has the largest product 6.
</pre>

<p><strong>Example 2:</strong></p>

<pre><strong>Input:</strong> [-2,0,-1]
<strong>Output:</strong> 0
<strong>Explanation:</strong>&nbsp;The result cannot be 2, because [-2,-1] is not a subarray.</pre>


**Companies**:  
[LinkedIn](https://leetcode.com/company/linkedin), [Google](https://leetcode.com/company/google), [Amazon](https://leetcode.com/company/amazon), [Microsoft](https://leetcode.com/company/microsoft), [Adobe](https://leetcode.com/company/adobe)

**Related Topics**:  
[Array](https://leetcode.com/tag/array/), [Dynamic Programming](https://leetcode.com/tag/dynamic-programming/)

**Similar Questions**:
* [Maximum Subarray (Easy)](https://leetcode.com/problems/maximum-subarray/)
* [House Robber (Easy)](https://leetcode.com/problems/house-robber/)
* [Product of Array Except Self (Medium)](https://leetcode.com/problems/product-of-array-except-self/)
* [Maximum Product of Three Numbers (Easy)](https://leetcode.com/problems/maximum-product-of-three-numbers/)
* [Subarray Product Less Than K (Medium)](https://leetcode.com/problems/subarray-product-less-than-k/)

## Solution 1. Two Pointers

Approach 3: Two pointer Approach
```cpp
Explanation :
1.) Through intution explanation we know that if all the elements are positive or the negative elements are even then ur 
answer will be product of complete array which u will get in variable l and r at the last iteration.
2.) But if negative elements are odd then u have to remove one negative element and it is sure that it will be either 
right of max prefix product or left of max suffix product. So u need not to modify anything in your code as u are 
getting prefix product in l and suffix prduxt in r.
3.) If array also contains 0 then your l and r will become 0 at that point...then just update it to 1(or else u 
will keep multiplying with 0) to get the product ahead making another subarray.
```
```cpp
// OJ: https://leetcode.com/problems/maximum-product-subarray/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0; // Edge case: empty array

        int leftProduct = 1;  // Tracks the prefix product
        int rightProduct = 1; // Tracks the suffix product
        int result = nums[0]; // Stores the final result (maximum product found so far)

        for (int i = 0; i < n; i++) {
            // If leftProduct or rightProduct becomes 0, reset it to 1
            leftProduct = (leftProduct == 0) ? 1 : leftProduct;
            rightProduct = (rightProduct == 0) ? 1 : rightProduct;

            // Update prefix product (left to right)
            leftProduct *= nums[i];

            // Update suffix product (right to left)
            rightProduct *= nums[n - 1 - i];

            // Update the result with the maximum of prefix and suffix products
            result = std::max(result, std::max(leftProduct, rightProduct));
        }

        return result;
    }
};
```

## Solution 2. DP

```
Case 1: All Elements are Positive
maxProd is enough

Case 2: Array Has Both Positive and Negative Elements
Even Number of Negatives: maxProd and minProd keeps getting swapped, at the end maxProd is answer
Odd: swapping helps us

Case 3: Array Contains Zeros
maxProd, minProd becomes 0

Taking nums[i] in max consideration is important when the previous product (either maxProd or minProd) is zero or negative, and starting fresh with the current element yields a better result.

```

```cpp
// OJ: https://leetcode.com/problems/maximum-product-subarray/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
class Solution {
public:
    int maxProduct(vector<int>& A) {
        int maxProd = 1, minProd = 1, ans = INT_MIN;
        for (int n : A) {
            int a = n * maxProd, b = n * minProd;
            maxProd = max({n, a, b});
            minProd = min({n, a, b});
            ans = max(ans, maxProd);
        }
        return ans;
    }
};
```

## Note

Similar problem: [1567. Maximum Length of Subarray With Positive Product (Medium)](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/)
