#include <cstddef>
#include <unordered_map>

/*
    Leetcode 138 Copy List with Random Pointer
    Description: https://leetcode.com/problems/copy-list-with-random-pointer/description/

    Algorithm:
    This is a similar problem to the Clone Graph problem (Leetcode 133).
    We need to traverse a graph essentially and make a deep copy.
    Since this is not a singly-linked list, a hashmap(from old to new) is needed because nodes previously visited
    would still be needed to be accessed because the random pointer connects to any node.

    Crux:
    - A linkedList traversal augmented with a map that maps from old nodes to clone nodes.
    - if the node doesn't exist in the hashmap, create one.
    - Regardless of its existence, establish the connection as in the next and random pointer.
*/

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    /**
     * @brief Create a deep copy of a LinkedList with next and random pointers.
     * @param head Node* pointer to the head of the list to be copied.
     * @returns Node* pointer to the head of the deep copy of the original linked list.
     */
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        std::unordered_map<Node*, Node*> map_old_to_new;

        map_old_to_new[head] = new Node(head->val);

        auto current_node = head;

        while (current_node != nullptr) {
            if (current_node->next != nullptr) {
                auto iterator_next_node = map_old_to_new.find(current_node->next);

                // If next node doesn't exist in the hashmap.
                if (iterator_next_node == map_old_to_new.end()) {
                    map_old_to_new[current_node->next] = new Node(current_node->next->val);
                }

                // Connect copy of current node to copy of next.
                map_old_to_new[current_node]->next = map_old_to_new[current_node->next];
            }

            if (current_node->random != nullptr) {
                auto iterator_random_node = map_old_to_new.find(current_node->random);

                // If random node doesn't exist in the hashmap.
                if (iterator_random_node == map_old_to_new.end()) {
                    map_old_to_new[current_node->random] = new Node(current_node->random->val);
                }

                // Connect copy of current node to the copy of random node.
                map_old_to_new[current_node]->random = map_old_to_new[current_node->random];
            }

            // Update step.
            current_node = current_node->next;
        }
        return map_old_to_new[head];
    }
};