#include <iostream>
#include <stack>
#include <unordered_map>

/**
 * @brief Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * An input string is valid if:
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 *
 * Steps:
 * 1. Add all the parentheses pairs to an unordered map.
 * 2. Initialize a stack.
 * 3. For loop
 *      a. if ith is in the map keys-> add to stack
 *      b. if ith is not in map keys
 *              if ith is a partner to the stack top -> false
 *              else stack pop.
 *      if stack.size() is zero -> return true.
 * return true.
 *
 * @param s Input string
 * @returns Boolean indicating whether the parentheses are correct.
*/

class Solution {
public:
    bool isValid(std::string s) {

        // Stack to store open parentheses.
        std::stack<char> open_par_stack;

        // Unordered map storing parentheses mapping.
        std::unordered_map<char, char> parentheses_map = {
            {'(', ')'},
            {'[', ']'},
            {'{', '}'},
        };

        for (auto & str: s){
            // .count faster than .find
            if (parentheses_map.count(str) > 0) {
                // If str found in the map keys, add to stack.
                open_par_stack.push(str);
            } else {
                // If str is not value to the stack top as key or is stack is empty, return false.
                // First check handles the possibility of a closing brace being present at start.
                if (open_par_stack.empty() || parentheses_map[open_par_stack.top()] != str){
                    return false;
                } else {
                    // If str is value to stack top as kep, stack pop.
                    open_par_stack.pop();
                }
            }
        }

        // Return true if stack is empty, else false.
        if (open_par_stack.empty()){
            return true;
        } else {
            return false;
        }
    }
};