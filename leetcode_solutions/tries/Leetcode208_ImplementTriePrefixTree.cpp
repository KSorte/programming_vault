#include <string>
#include <unordered_map>

/*
    Leetcode 208 Implement Trie (Prefix Tree)

    A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store
    and retrieve keys in a dataset of strings. There are various applications of this data structure,
    such as autocomplete and spellchecker.

    Implement the Trie class:

    Trie() Initializes the trie object.
    void insert(String word) Inserts the string word into the trie.
    boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before),
    and false otherwise.
    boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has
    the prefix prefix, and false otherwise.

    Algorithm
    - First a TrieNode class needs to be implemented.
        - Children Hashmap - an unordered map mapping from characters to their TrieNode.
        (TrieNode for p in apple and that for 'epsilon' will be different entities.)
        -  is_last = A boolean indicating whether this TrieNode is the end of a word.

    - Trie Class.
        Insert(word)
            current = TrieNode at the root of Trie tree.
            for letter in word:
                either add the letter to the Trie tree (if it doesn't exist)
                shift the current to the child node.
            at end of for loop, set is_last = True for current node.

        Search and startswith are very similar to insert with very small distinctions.
*/

class TrieNode {
public:
    /**
     * @brief Constructor for the TrieNode Class.
     */
    TrieNode() : is_end_of_word(false), children_map({}){};

    // Unordered map mapping from character to TrieNode object for children.
    std::unordered_map<char, TrieNode*> children_map;

    // Boolean indicating if the node is the end of a word.
    bool is_end_of_word;
};

class Trie {
public:
    /**
     * @brief Constructor for the Trie Class.
     */
    Trie() {
        root = new TrieNode();
    }

    /**
     * @brief Insert word into the Trie.
     * @param word String word to be inserted.
     */
    void insert(std::string word) {
        auto current_node = root;
        for (auto & letter : word) {
            // Search for letter in the children of the current node.
            auto iterator_to_letter = current_node->children_map.find(letter);

            // If not found.
            if (iterator_to_letter == current_node->children_map.end()) {
                current_node->children_map[letter] = new TrieNode();
            }

            current_node = current_node->children_map[letter];
        }  // End of for loop for word insertion.
        current_node->is_end_of_word = true;
    }

    /**
     * @brief Search for word in the Trie.
     * @param String word to search for.
     * @returns Boolean indicating whether the word exists in the Trie.
     */
    bool search(std::string word) {
        auto current_node = root;
        for (auto & letter : word) {
            // Search for letter in the children of the current node.
            auto iterator_to_letter = current_node->children_map.find(letter);

            // If not found.
            if (iterator_to_letter == current_node->children_map.end()) {
                return false;
            }

            current_node = current_node->children_map[letter];
        }  // End of for loop for word search.

        return current_node->is_end_of_word;
    }

    /**
     * @brief Search whether a word starting with the prefix exists in the Trie.
     * @param String prefix to search against.
     * @returns Boolean indicating whether a word starting with the prefix exists.
     */
    bool startsWith(std::string prefix) {
        auto current_node = root;
        for (auto & letter : prefix) {
            // Search for letter in the children of the current node.
            auto iterator_to_letter = current_node->children_map.find(letter);

            // If not found.
            if (iterator_to_letter == current_node->children_map.end()) {
                return false;
            }

            current_node = current_node->children_map[letter];
        }  // End of for loop for word search with prefix.

        return true;
    }

private:
    // Root of the prefix tree.
    TrieNode* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */