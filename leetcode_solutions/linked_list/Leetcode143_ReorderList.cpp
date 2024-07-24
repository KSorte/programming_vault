/*
    Leetcode 143 Reorder List

    You are given the head of a singly linked-list. The list can be represented as:

    L0 → L1 → … → Ln - 1 → Ln
    Reorder the list to be on the following form:

    L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
    You may not modify the values in the list's nodes. Only nodes themselves may be changed.

    Algorithm:
    1. Find the length of the linked list O(N).
    2. Reverse the second half of the linked list. O(N) and place pointers at the opposite ends
    of the list.
    3. Iterate both pointers until the list is merged.

    Tricky part here is for loop conditions.

    When dealing with pointers it is always better to have loop condition
    dependent on nullptr conditions rather than number of iterations.
    The later will always make handling of nullptr edge cases very difficult.

    Thus, both the reverse list and merge list function use while loops and not for loops.
    For loops are error prone.

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
     * @brief Reorder linkedlists as described in the Reorder List Leetcode 143 question.
     * @param head ListNode* head to the linked list to be reordered.
     */
    void reorderList(ListNode* head) {
        if (head == nullptr) {
            return;
        }

        auto current_node = head;
        int length_linked_list = 0;

        // Get length O(N).
        while (current_node != nullptr) {
            length_linked_list ++;
            current_node = current_node->next;
        }


        int middle_of_list;
        if (length_linked_list % 2 == 0) {
            middle_of_list = length_linked_list/2;
        }

        if (length_linked_list % 2 == 1) {
            middle_of_list = length_linked_list/2 + 1;
        }

        current_node = head;
        ListNode* previous_node = nullptr;

        // Get the pointer to node sitting at middle_of_list + 1.
        for (int i = 1; i <= middle_of_list; i++) {
            previous_node = current_node;
            current_node = current_node->next;
        }

        // Disconnect first half from second half.
        previous_node->next = nullptr;

        auto right_pointer = reverse_list(current_node);
        auto left_pointer = head;

        merge_lists(left_pointer, right_pointer);

    }

private:
    /**
     * @brief Reverse linked list given by pointer to head.
     * @param head ListNode* pointer to the head of the linked list.
     * @returns ListNode* pointer to the head of the reversed linked list.
     */
    ListNode* reverse_list(ListNode* head) {
        ListNode* previous_node = nullptr;
        ListNode* current_node = head;
        while (current_node != nullptr) {
            auto next = current_node->next;
            current_node->next = previous_node;
            previous_node = current_node;
            current_node = next;
        }
        return previous_node;
    }

    /**
     * @brief Merge linkedlists (one longer and one shorter) alternatively.
     * @param head_long_list ListNode* pointer to the head of the longer list.
     * @param head_short_list ListNode* pointer to the head of the shorter list.
     */
    void merge_lists(ListNode* head_long_list, ListNode* head_short_list) {
        while (head_short_list != nullptr) {
            // Note successors.
            auto left_next = head_long_list->next;
            auto right_next = head_short_list->next;

            // Reorder.
            head_long_list->next = head_short_list;
            head_short_list->next = left_next;

            // Update pointers.
            head_long_list = left_next;
            head_short_list = right_next;
        }
    }
};