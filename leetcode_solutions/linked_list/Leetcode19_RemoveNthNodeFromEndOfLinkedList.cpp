/*
    Leetcode 19 Remove Nth Node From End of Linked List
    Given the head of a linked list, remove the nth node from the end of the list and return its head.

    Algorithm:
    Maintain two pointers - slow and fast -  such that the distance between them is always n - 1.
    If we need 2nd from behind, then the fast should be a step ahead always.

    The slow fast pointer method can also be used in Leetcode 143 Reorder List to find the middle of the
    linked list. There the fast always moves twice as fast as the slow pointer. When fast reaches the end,
    the slow has approximately reached the middle of the linked list.
    As usual, handle for loop conditions well.
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
     * @brief Given a LinkedList, remove the nth node from behind and return head
     * in a single pass.
     * @param head ListNode* head of LinkedList.
     * @param n Integer n corresponding to position of node from back to be removed.
     * @returns ListNode* head of modified linked list.
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* lagging_pointer = head;
        ListNode* fast_pointer = head;

        if (head == nullptr) {
            return head;
        }

        // Advance fast pointer.
        for (int i = 1; i <= n; i++) {
            fast_pointer = fast_pointer->next;
        }


        // Get node to be removed.
        ListNode* previous = nullptr;
        while (fast_pointer != nullptr) {
            fast_pointer = fast_pointer->next;
            previous = lagging_pointer;
            lagging_pointer = lagging_pointer->next;
        }

        // If head is to be removed.
        if (previous == nullptr) {
            return lagging_pointer->next;
        }

        // Remove node.
        previous->next = lagging_pointer->next;
        lagging_pointer->next = nullptr;

        return head;
    }
};