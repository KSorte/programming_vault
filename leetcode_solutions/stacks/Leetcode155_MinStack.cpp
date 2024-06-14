#include <iostream>
#include <stack>
/*
    Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
    Implement the MinStack class:
    MinStack() initializes the stack object.
    void push(int val) pushes the element val onto the stack.
    void pop() removes the element on the top of the stack.
    int top() gets the top element of the stack.
    int getMin() retrieves the minimum element in the stack.
    You must implement a solution with O(1) time complexity for each function.

    Steps:
    1. Create a new internal stack to store the minimum element with associated with each element pushed.
    2. When pushing element into stack, reevaluate min using the min stack.
        Push the determined min into the min stack
    3. When popping, pop both stacks.
    4. When retrieving min element, get the top of the min stack.
*/

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

class MinStack {
public:
    /**
     * @brief Constructor.
     */
    MinStack() {
    }

    /**
     * @brief Push element into the stack and keep track of minimum.
     * @param val Value to push.
     */
    void push(int val) {
        main_stack.push(val);
        // Check if min stack is empty.
        if (!min_stack.empty()){
            // Check if val is smaller than the current minimum.
            if (val > min_stack.top()){
                // Assign the min value to val.
                val = min_stack.top();
            }
        }
        // If min stack is empty, val is directly put into it.
        // If val is > min, then the min is assigned to val.
        min_stack.push(val);
    }

    /**
     * @brief Pop element from the main stack.
     * Pops element from the min stack too.
     */
    void pop() {
        // Pop elements from both stacks.
        main_stack.pop();
        min_stack.pop();
    }

    /**
     * @brief Returns top element of the main stack.
     * @returns Integer value at top of stack.
     */
    int top() {
        return main_stack.top();
    }

    /**
     * @brief Returns min element from the top of the minimum stack.
     * @returns Integer value at top of min stack.
     */
    int getMin() {
        return min_stack.top();
    }

private:
    // Main stack.
    std::stack<int> main_stack;
    // Stack holding the minimum element associated with each element pushed.
    std::stack<int> min_stack;

};