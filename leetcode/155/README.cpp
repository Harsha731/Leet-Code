/*
QUESTION:
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
Implement the MinStack class.
MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

Example:
Input:
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
Output:
[null,null,null,null,-3,null,0,-2]
Explanation:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

APPROACH:
- We can use an auxiliary stack to keep track of the difference of an element from the minimum element at each step.
- When pushing an element, we push the difference of an element from the minimum element at that time.
- When popping an element, we check stack top if it's -ve it means that this element is the minimum so we update the mini as we popping the current minimum.
- To get the top element, we add the current minimum to the top element of the main stack.
- To get the minimum element, we simply return the current minimum.

Mine :

Instead of directly storing each value, the stack stores an "offset" between the current value and the minimum (mini)

Push : If val > mini, we push +ve value val - mini and we remain mini as it is
If val < mini, we push -ve value val - mini and we change mini to val

Pop : If st.top is -ve, it means mini got changed to val and we update the mini by old_mini = new_mini (=val) - st.top() before pop out
If st.top is +ve, it means old_mini = new_mini, we simply pop the top value of stack

Top : If st.top is -ve, it means mini got changed and it got changed to val
If st.top is +ve, it means mini remained same and we can get the value using val = mini + st.top()

Here, we are not discussing about the last element present in stack

CODE:
*/

class MinStack {
private:
    stack<long long> st;
    int mini;
public:
    MinStack() {
        mini = -1;
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push(0);
            mini = val;
        } else {
            st.push((long long)val - mini);// to handle overflow case
            mini = min(val, mini);
        }
    }
    
    // If val < old mini, then new mini = val, so retrieve it we do [ old mini ] = [ new_mini ] - [ st.top() ]
    //                                                                   old mini   =  val         - ( val - old_mini )
    void pop() {
        if (st.top() < 0)           
            mini = mini - st.top();
        st.pop();
    }
    
    int top() {
        int ans = -1;
        if (st.top() < 0)           // If the st.top() is negative, it means minimum got changed top 'val' at this point, so the answer is the mini (i.e, min as min=val)
            ans = mini;
        else
            ans = mini + st.top();      // If not, we do we add mini to st.top() to get the val
        return ans;
    }
    
    int getMin() {
        return mini;
    }
};

/*
COMPLEXITY ANALYSIS:
- All the operations (push, pop, top, getMin) have O(1) time complexity as we are performing constant-time operations on the stack.
- The space complexity is O(n) as we use an auxiliary stack to store the minimum elements.
*/


// Handle the empoty stack situation in pop, top, getMin and update min to -1 after popping the last element

class MinStack {
private:
    stack<long long> st;
    int mini;

public:
    MinStack() {
        mini = -1;
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push(0);
            mini = val;
        } else {
            st.push((long long)val - mini); 
            mini = min(val, mini);
        }
    }
    
    void pop() {
        if (st.empty()) return;        

        if (st.top() < 0)           
            mini = mini - st.top();
        
        st.pop();

        // Reset mini if the stack becomes empty
        if (st.empty()) {
            mini = -1;  // Reset mini to initial value
        }
    }
    
    int top() {
        if (st.empty()) return -1; 

        if (st.top() < 0)           
            return mini;
        else
            return mini + st.top();
    }
    
    int getMin() {
        if (st.empty()) return -1;
        return mini;
    }
};
____________________________________________

// This is best approach
// Time: O(1) for all
// Space: O(N)
class MinStack {
    stack<int> mn, val;
public:
    MinStack() {}
    void push(int x) {
        val.push(x);
        if (mn.empty() || mn.top() >= x) mn.push(x);
    }
    void pop() {
        if (val.top() == mn.top()) mn.pop();
        val.pop();
    }
    int top() {
        return val.top();
    }
    int getMin() {
        return mn.top();
    }
};
