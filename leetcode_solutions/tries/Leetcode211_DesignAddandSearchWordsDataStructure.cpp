#include <memory>
#include <string>
#include <unordered_map>

/*
    Leetcode 211 Design, Add And Search Words Data Structure.
    Design a data structure that supports adding new words and finding
    if a string matches any previously added string.

    Implement the WordDictionary class:

    WordDictionary() Initializes the object.
    void addWord(word) Adds word to the data structure, it can be matched later.
    bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise.
    word may contain dots '.' where dots can be matched with any letter.

    Implementation:
    Implementation can be similar to the Leetcode 208 problem - Trie needs to be implemented.
    - A DictionaryNode class equivalent to Trie Node class.
    - Insert method from Leetcode 208 can be transferred for addWord method.
    - StartsWith method from Leetcode 208 can be adapted with improvements for search method.

    Searching a pattern ('.ad' for example) is not a trivial problem.
    A DFS algo is needed to search the entire Trie.
*/

class DictionaryNode {
public:
    /**
     * @brief Constructor for the DictionaryNode Class.
     */
    DictionaryNode() : is_end_of_word(false) {};

    // Unordered map mapping from character to TrieNode object for children.
    std::unordered_map<char, std::unique_ptr<DictionaryNode>> children_map;

    // Boolean indicating if the node is the end of a word.
    bool is_end_of_word;
};

class WordDictionary {
public:
    /**
     * @brief Constructor for the Trie Class.
     * Initializes root of the Dictionary Trie.
     */
    WordDictionary() {
        root = std::make_unique<DictionaryNode>();
    }

    /**
     * @brief Add word into the Dictionary Trie.
     * @param word String word to be addedd.
     */
    void addWord(std::string word) {
        auto current_node = root.get();
        for (const auto & letter : word) {
            auto letter_in_children_map = current_node->children_map.find(letter);

            // If non existent, create new.
            if (letter_in_children_map == current_node->children_map.end()) {
                current_node->children_map[letter] = std::make_unique<DictionaryNode>();
            }
            // Update current node.
            current_node = current_node->children_map[letter].get();
        }  // End of for loop.
        current_node->is_end_of_word = true;
    }

    /**
     * @brief Search for string in the Dictionary.
     * Uses depth first search.
     * @param word String to search for.
     * @returns Boolean indicating whether the word exists in the Dictionary.
     */
    bool search(std::string word) {
        return depth_first_search(0, word, root.get());
    }

private:
    // Root of the prefix tree.
    std::unique_ptr<DictionaryNode> root;

    /**
     * @brief Search for word starting from word_index in the Trie subtree given by root.
     * @param word_index Integer word index that slices the string to search for.
     * @param word String to search for.
     * @param root DictionaryNode* pointer to the root of a subtree in Trie to search for.
     * @returns Boolean indicating whether the word exists in the Subtree.
     */
    bool depth_first_search(int word_index,
        std::string & word,
        DictionaryNode* root) {
        auto current_node = root;

        for (int i = word_index; i < word.size(); i++) {
            if(word[i] == '.') {
                // Search through all the children of current node.
                for (auto & [letter, node] : current_node->children_map) {
                    if (depth_first_search(i + 1, word, node.get())) {
                        return true;
                    }
                }  // End of recursive for loop.
                return false;
            } else {
                // Character is a letter.
                auto iterator_to_child =
                    current_node->children_map.find(word[i]);
                if (iterator_to_child == current_node->children_map.end()) {
                    // Not found.
                    return false;
                }
                current_node = current_node->children_map[word[i]].get();
            }
        }
        // NOTE: Replace this return with a true. You will see some important test cases fail.
        return current_node->is_end_of_word;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */