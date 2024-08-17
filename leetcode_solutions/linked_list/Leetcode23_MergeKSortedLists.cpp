#include <queue>
#include <vector>
/*
    Leetcode 32 Merge K Sorted Lists
    You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
    Merge all the linked-lists into one sorted linked-list and return it.

    Algorithm:
    Add all elements to a min -heap O(nlogn) and pop elements in succession to
    get the merged linked list O(nlogn)
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
     * @brief Merge all the linked-lists into one sorted linked-list and return it.
     * @param lists Vector of ListNode* representing heads of all linkedlists.
     * @returns ListNode* pointer to the head of merged linked list.
     */
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // Priority queue to hold elements from all lists.
        std::priority_queue<
            std::pair<int, ListNode*>,
            std::vector<std::pair<int, ListNode*>>,
            std::greater<std::pair<int, ListNode*>>> priority_queue;

        if (lists.empty()) {
            return nullptr;
        }

        // Add all nodes to a heap. O(nlog(n))
        for (const auto & list : lists) {
            auto current_node = list;
            while(current_node) {
                priority_queue.push(std::make_pair(current_node->val, current_node));
                current_node = current_node->next;
            }
        }

        // Get head of merged list. O(1).
        ListNode* head_merged_list = nullptr;
        if (!priority_queue.empty()) {
            auto top_priority_queue = priority_queue.top();
            priority_queue.pop();
            head_merged_list = top_priority_queue.second;
        }

        // Merge lists by popping elements from priority queue. O(nlogn).
        auto previous_node = head_merged_list;
        while(!priority_queue.empty()) {
            auto current = priority_queue.top();
            priority_queue.pop();
            auto current_node = current.second;
            previous_node->next = current_node;
            previous_node = current_node;
        }

        return head_merged_list;
    }
};