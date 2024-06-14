#include <iostream>
#include <stack>
#include <vector>

/*
    Given an array of integers temperatures represents the daily temperatures,
    return an array answer such that answer[i] is the number of days you have to
    wait after the ith day to get a warmer temperature. If there is no future
    day for which this is possible, keep answer[i] == 0 instead.

    Steps:
    1. Initialize a stack of ints.
    Initialize answer vector with all zeros.
    2. For loop through input array i = 0:
        if stack is empty : add element; continue.
        count = 1
        curr = stack top;
        while (curr < ith):
            if (answer [i - count] != 0) :
                count++; continue;
            stack.pop()
            count ++;

        answer[i] = count;
        push ith into stack.
    3. return answer.
*/

class Solution {
public:
    /**
     * @brief Calculates array answer containing the number of days for each day as described.
     * @param temperatures Input array.
     * @returns Answer array.
     */
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        // Initialize stack.
        std::stack<int> temp_stack;
        // Initialize answer vector
        std::vector<int> answer(temperatures.size(), 0);

        for (int i = 0; i<temperatures.size(); i++){
            if (temp_stack.empty()){
                // If stack is empty, add the temperature and go
                // to next iteration.
                temp_stack.push(temperatures[i]); continue;
            }

            int days = 1;
            int last_unpopped_temp = temp_stack.top();
            while (last_unpopped_temp < temperatures[i]){
                // Skip element in answer if the value is non-zero.
                // Non zero value indicates that the corresponding temp is popped
                // before.
                if (answer[i - days] != 0){
                    // Increment days to last unpopped temp.
                    days++; continue;
                }
                // if ith answer is zero, it means it is unpopped.
                // Pop.
                temp_stack.pop();
                // The index of the popped element is i - days.
                answer[i - days] = days;

                // Assign the new top element in stack to last unpopped,
                // if the stack is non-empty.
                if (!temp_stack.empty()){
                    last_unpopped_temp = temp_stack.top();
                } else {
                    // If stack empty, break out of the loop.
                    break;
                }
            }

            // Add ith temperature to the stack.
            temp_stack.push(temperatures[i]);
        }
        return answer;
    }
};


int main() {
    Solution sol;

    // Test cases
    std::vector<std::vector<int>> testCases = {
        {73, 74, 75, 71, 69, 72, 76, 73},
        {30, 40, 50, 60},
        {30, 60, 90},
        {80, 70, 60, 50, 40, 30},
        {50, 50, 50, 50, 50},
        {},
        {100}
    };

    for (auto& temperatures : testCases) {
        std::vector<int> result = sol.dailyTemperatures(temperatures);
        std::cout << "Temperatures: ";
        for (int temp : temperatures) {
            std::cout << temp << " ";
        }
        std::cout << "\nDays to wait for warmer temperature: ";
        for (int days : result) {
            std::cout << days << " ";
        }
        std::cout << "\n\n";
    }

    return 0;
}