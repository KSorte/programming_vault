/**

Leetcode 206 Reverse Linked List

while current node not null
    note next
    current.next = prev
    prev = current
    current = next
    current.next = previous.

In a single iteration you are altering connections from <- P C->N to <-P<-C<-N
 */

//  Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

    class Solution {
    public:
        ListNode* reverseList(ListNode* head) {

            if (!head || !head->next)
                return head;

            ListNode* current_node = head;
            ListNode* previous_node = nullptr;

            while(current_node != nullptr) {
                ListNode* next = current_node->next;
                current_node->next = previous_node;
                previous_node = current_node;
                current_node = next;
            }
            return previous_node;

            // METHOD 2.
            // // Initialize current node and next.
            // ListNode* current_node = head;
            // ListNode* next = head->next;
            // ListNode* previous_node = nullptr;
            // current_node->next = previous_node;

            // while(next != nullptr) {
            //     previous_node = current_node;

            //     // Update current node and next.
            //     current_node = next;
            //     next = current_node->next;

            //     // Point to previous node.
            //     current_node->next = previous_node;
            // }
            // return current_node;

            // CAN BE SOLVED RECURSIVELY.
        }
    };