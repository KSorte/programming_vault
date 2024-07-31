/*
    Leetcode 141 Linked List Cycle

    Given head, the head of a linked list, determine if the linked list has a cycle in it.
    There is a cycle in a linked list if there is some node in the list that can be reached again by continuously
    following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to.
    Note that pos is not passed as a parameter.
    Return true if there is a cycle in the linked list. Otherwise, return false.

    Algorithm:
        1. Move a fast pointer that jumps ahead to the next to next node.
        2. Move a slow pointer that moves one at a time.
        3. Their relative speed is one which ensures that if there is a cycle, the fast pointer will meet
            the slow at the exact same node.
        4.Once that happens, declare that a cycle exists.
*/

// Definition for singly-linked list.
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
     * @brief Determine whether a linked list has a cycle.
     * @param head ListNode* pointer to the head of the linked list.
     * @returns Boolean indicating whether the linked list contains a cycle.
     */
    bool hasCycle(ListNode *head) {
        if (head == nullptr) {
            return false;
        }

        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;

        // While condition ensures that both transitions of fast pointer are valid.
        while(fast_pointer->next != nullptr && fast_pointer->next->next != nullptr) {
            // Update pointers.
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;

            // Cycle detected.
            if (fast_pointer == slow_pointer) {
                return true;
            }
        }
        return false;
    }

    // Incrementing slow pointer every two iterations as opposed to taking jumps of two.
    // Both methods are equivalent.

    bool hasCycleSecondMethod(ListNode *head) {
        if (head == nullptr) {
            return false;
        }

        if (head->next == nullptr) {
            return false;
        }

        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head->next;

        int count = 0;
        while(fast_pointer != nullptr) {
            if (fast_pointer == slow_pointer) {
                return true;
            }

            if (count % 2 == 0) {
                slow_pointer = slow_pointer->next;
            }
            fast_pointer = fast_pointer->next;
            count ++;
        }

        return false;
    }
};