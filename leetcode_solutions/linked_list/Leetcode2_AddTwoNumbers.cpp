/*
    Leetcode 2 Add Two Numbers.
    You are given two non-empty linked lists representing two non-negative integers.
    The digits are stored in reverse order, and each of their nodes contains a single digit.
    Add the two numbers and return the sum as a linked list.

    You may assume the two numbers do not contain any leading zero, except the number 0 itself.

    Algorithm:
    Iterate in a while loop until BOTH lists are exhausted (both numbers may have different number of digits).
    carry_over = 0;
    Each iteration:
        if (one list is over)
            Add carry over to number of other list and get result.

        if both list active:
            add both numbers and the carry over and get result.

        Get new carry over and go forward in both lists
*/

//  Definition for singly-linked list.
struct ListNode {
    // Value of the list node.
    int val;

    // Raw Pointer to the next ListNode.
    ListNode *next;

    /**
     * @brief Constructor.
     */
    ListNode() : val(0), next(nullptr) {}

    /**
     * @brief Constructor.
     * @param x Integer value.
     */
    ListNode(int x) : val(x), next(nullptr) {}

    /**
     * @brief Constructor.
     * @param x Integer value.
     * @param next ListNode* pointer to next node.
     */
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    /**
     * @brief Add two numbers represented as linked list in small endian format.
     * @param l1 ListNode* head of first list.
     * @param l2 ListNode* head of second list.
     * @returns ListNode* head to the addition result linked list.
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry_over = 0;

        ListNode* result_list_head = new ListNode();

        auto current_result_node = result_list_head;

        while (l1 != nullptr || l2 != nullptr) {
            auto addition_result = 0;
            if (l1 == nullptr) {
                // List 1 is exhausted.
                addition_result = carry_over + l2->val;
            } else if (l2 == nullptr) {
                // List 2 is exhausted.
                addition_result = carry_over + l1->val;
            } else {
                // Both lists still active.
                addition_result = carry_over + l1->val + l2->val;
            }

            carry_over = addition_result / 10;
            current_result_node->val = addition_result % 10;

            // Updates.
            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }

            // Create next node in result list only if required.
            if (carry_over > 0 || l1 != nullptr || l2 != nullptr) {
                current_result_node->next = new ListNode();
                current_result_node = current_result_node->next;
            }
        }

        // Account for carry over.
        if (carry_over > 0) {
            current_result_node->val = carry_over;
        }

        return result_list_head;
    }
};