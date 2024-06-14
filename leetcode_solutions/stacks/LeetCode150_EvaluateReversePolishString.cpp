#include <iostream>
#include <stack>
#include <vector>

/*
    You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

    Evaluate the expression. Return an integer that represents the value of the expression.

    Note that:

    The valid operators are '+', '-', '*', and '/'.
    Each operand may be an integer or another expression.
    The division between two integers always truncates toward zero.
    There will not be any division by zero.
    The input represents a valid arithmetic expression in a reverse polish notation.
    The answer and all the intermediate calculations can be represented in a 32-bit integer.

    Steps:
    1. Initialize a stack to store the numbers read off from the input.
    2. If the current char is not a number, then evaluate the top two elements of the stack.
        Pop the two elements and push the new result.
    3. Return the last remaining element in the stack.
*/

class Solution {
public:
    /**
     * @brief Evaluates the vector of strings according the Reverse Polish Notation.
     * @param tokens Vector of strings containing numbers and operators to evaluate.
     * @returns Integer result of the RPN evaluation.
     */
    int evalRPN(std::vector<std::string>& tokens) {
        // Stack to store all the operands as we get them.
        std::stack<int> operand_stack;

        for (auto &str : tokens) {
            /*
                It is assumed that strings like "1%2" won't appear.
                if the last element in the str is a digit, we can be sure it is not
                an operator.
            */
            if (!std::isdigit(str.back())) {
                // Str is an operator.
                // Extract both numbers from the stack.
                auto num2 = operand_stack.top();
                operand_stack.pop();
                auto num1 = operand_stack.top();
                operand_stack.pop();
                // Result after the operation.
                int result;
                if (str == "+"){
                    result = num1 + num2;
                } else if (str == "-"){
                    result = num1 - num2;
                } else if (str == "*") {
                    result = num1*num2;
                } else if (str == "/"){
                    result = num1/num2;
                }
                // This implementation assumes that non-digits would only be operators
                // and no irregular characters will appear.
                // Hence that case is not handled.
                operand_stack.push(result);
            } else {
                // it is a number.
                operand_stack.push(std::stoi(str)); }
        }
        return operand_stack.top();
    }
};

int main() {
    Solution sol;

    // Test cases
    std::vector<std::vector<std::string>> testCases = {
        {"2", "3", "+"},        // 5
        {"5", "2", "-"},        // 3
        {"4", "6", "*"},        // 24
        {"10", "2", "/"},       // 5
        {"4", "13", "5", "/", "+"},  // 6
        {"-12", "3", "/"},      // -4
        {"5"},                  // 5
        {"123456789", "987654321", "+"},  // 1111111110
        {"10", "3", "/"}        // 3
    };

    for (auto& tokens : testCases) {
        int result = sol.evalRPN(tokens);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}