/*
    Leetcode 21 Merge Two Sorted Lists
    You are given the heads of two sorted linked lists list1 and list2.

    Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

    Return the head of the merged linked list.

    Algorithm:
    - Mark as head as the head of the list with smaller value.
    - Create two more head pointers pointing to current start point of lists.
    - while (head1 not null AND head2 not null)
        - Add the the smaller list start point as child to head.
        - move the head1 or head2 forward.
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
     * @brief Merge two sorted LinkedLists.
     * @param list1 ListNode* head of first list.
     * @param list2 ListNode* head of second list.
     * @returns ListNode* head of the merged list.
     */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Handle edge cases.
        if (list1 == nullptr) {
            return list2;
        }

        if (list2 == nullptr) {
            return list1;
        }

        if (list1 == nullptr && list2 == nullptr) {
            return nullptr;
        }

        ListNode* head_merged_list;
        ListNode* current_node;
        ListNode* head_secondary_list;

        // If list1 head is smaller.
        if (list1->val <= list2->val) {
            current_node = list1;
            // List2 is secondary, will merge into list1.
            head_secondary_list = list2;
        }

        // If list2 head is smaller.
        if (list2->val < list1->val) {
            current_node = list2;
            // List1 is secondary, will merge into list2.
            head_secondary_list = list1;
        }

        head_merged_list = current_node;

        // Until secondary list is exhausted.
        while (head_secondary_list != nullptr) {
            if (current_node->next == nullptr) {
                current_node->next = head_secondary_list;
                break;
            }

            if (current_node->next->val < head_secondary_list->val) {
                current_node = current_node->next;
                continue;
            }

            // Merge node from secondary list into primary.
            if (current_node->next->val >= head_secondary_list->val) {
                auto next = head_secondary_list->next;
                head_secondary_list->next = current_node->next;
                current_node->next = head_secondary_list;
                head_secondary_list = next;
            }
        }
        return head_merged_list;
    }
};