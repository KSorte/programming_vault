#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
    Following is a brief description of testing the autonomous behavior.
    A left operator sits behind the wheel, ready to take over.
    A right operator notes down behaviors, events in short notes or even words.
    For example

    pedestrian crossing street
    human xing street
    ped xing road

    All the above 3 sentences are equivalent, even though they are distinct sentences.
    They are equivalent because of the following word associations we have:

    (pedestrian, ped); (ped, human), (crossing, xing), (road, street), (pedestrian, human)

    Write a class that takes in these word associations as input to constructors.
    Write a method that determines whether two sentences are equivalent.

    Algorithm:
    Sort words into groups using the associations. Use UNION FIND for this.
    Iterate through each sentence, and find the groups of all the words within (if the words have a group).
        Add the group label into the set.

    If the two sets are equal, then the sentences are equivalent.

    Union Find Resources:

    Union Find: https://www.youtube.com/watch?v=0jNmHPfA_yE&t=507s
    Path Compression: https://www.youtube.com/watch?v=VHRhJWacxis
    Kruskal's Algorithm: https://www.youtube.com/watch?v=JZBQLXgSGfs
*/

// TODO(KSorte): Use Smart Pointers.
// TODO(KSorte): Use Path Compression in Union Find.
// TODO(KSorte): Create headers and assign separate repository.
class ConnectionNode {
public:
    /**
     * @brief Constructor.
     */
    ConnectionNode(std::string word) : parent_node(nullptr), word(word) {}

    /**
     * @brief Destructor.
     */
    ~ConnectionNode() {
        for (auto child : children_nodes) {
            delete child;
        }
    }

    /**
     * @brief Add child to the ConnectionNode.
     * @param child ConnectionNode* object to be added as child.
     */
    void add_child(ConnectionNode* child) {
        // Assign self as parent.
        child->parent_node = this;
        children_nodes.insert(child);
    }

    /**
     * @brief Find root of the grouping to which the word belongs.
     * @returns Pointer to the root of the group to which the word belongs.
     */
    ConnectionNode* find_root() {
        auto current_word = this;
        while (current_word->parent_node != nullptr) {
            current_word = current_word->parent_node;

        }
        return current_word;
    }

    // String word corresponding to the word.
    std::string word;

    // Parent node to the connection node.
    ConnectionNode* parent_node;

private:
    // hash map to store children connections to this node.
    std::unordered_set<ConnectionNode*> children_nodes;
};

class NoteEquivalence {
public:
    /**
     * @brief Constructor.
     * Sorts the inputted word associations into groups.
     * @param word_associations Vector of pairs representing word associations.
     */
    NoteEquivalence(std::vector<std::pair<std::string, std::string>> word_associations) :
        word_associations(word_associations) {
            group_data();
    }

    /**
     * @brief Determines if the two sentences are equivalent or not based on the word associations
     * and the corresponding map of associations.
     * @param sentence1 Vector of strings first sentence.
     * @param sentence2 Vector of strings second sentence.
     * @returns Boolean indicating whether the two sentences are equivalent.
     */
    bool is_equivalent(std::vector<std::string> sentence1, std::vector<std::string> sentence2) {
        // TODO(KSorte): Take in full sentences and split the sentences using spaces.
        std::unordered_set<std::string> groups_in_sentence_1;
        std::unordered_set<std::string> groups_in_sentence_2;

        for (const auto & word : sentence1) {
            // If Word exists in the existing database.
            if (map_of_existing_words.find(word) != map_of_existing_words.end()) {
                auto group_root = map_of_existing_words[word]->find_root();
                groups_in_sentence_1.insert(group_root->word);
            }
        }

        for (const auto & word : sentence2) {
            // If Word exists in the existing database.
            if (map_of_existing_words.find(word) != map_of_existing_words.end()) {
                auto group_root = map_of_existing_words[word]->find_root();
                groups_in_sentence_2.insert(group_root->word);
            }
        }
        return groups_in_sentence_1 == groups_in_sentence_2;
    }

    // Map to store the word associations.
    // TODO(KSorte): Move to private, brought here for testing.
    std::unordered_map<std::string, ConnectionNode*> map_of_existing_words;
private:
    // Associations of words.
    std::vector<std::pair<std::string, std::string>> word_associations;

    /**
     * @brief Groups the words using the vector of word associations using the Union Find algorithm.
     */
    void group_data() {
        // Iterate through the word associations taken as input
        for (auto & [first_word, second_word] : word_associations) {
            // Check if the words exist in set.
            auto first_exists = map_of_existing_words.find(first_word);
            auto second_exists = map_of_existing_words.find(second_word);

            // If both do not exist in the set.
            if (first_exists == map_of_existing_words.end() &&
            second_exists == map_of_existing_words.end()) {
                ConnectionNode* first = new ConnectionNode(first_word);
                ConnectionNode* second = new ConnectionNode(second_word);
                first->add_child(second);

                // Add words to map.
                map_of_existing_words[first_word] = first;
                map_of_existing_words[second_word] = second;
                continue;
            }

            // If both exist in the set.
            if (first_exists != map_of_existing_words.end() &&
            second_exists != map_of_existing_words.end()) {

                // Pointers.
                auto first = map_of_existing_words[first_word];
                auto second = map_of_existing_words[second_word];

                auto root_first_word = first->find_root();
                auto root_second_word = second->find_root();

                if (root_first_word == root_second_word) {
                    // Both already in same group.
                    continue;
                }

                // Assign the root of second as the child of root of first.
                // TODO(KSorte): What if the root of the second child is made the child of the ROOT of the first child
                // and not to the first child? This would make the paths smaller.
                first->add_child(root_second_word);
                continue;
            }

            // One exists, the other doesn't.
            if (first_exists == map_of_existing_words.end()) {
                // If first doesnt exist and second does.
                auto first = new ConnectionNode(first_word);
                // Get pointer of second.
                auto second = map_of_existing_words[second_word];
                second->add_child(first);
                map_of_existing_words[first_word] = first;
            } else if (second_exists == map_of_existing_words.end()) {
                // If first exists, but second doesn't.
                auto second = new ConnectionNode(second_word);
                // Get pointer to first.
                auto first = map_of_existing_words[first_word];
                first->add_child(second);
                map_of_existing_words[second_word] = second;
            }

        }
    }
};


int main() {
    std::vector<std::pair<std::string, std::string>> word_associations;
    word_associations.emplace_back("pedestrian", "ped");
    word_associations.emplace_back("ped", "human");
    word_associations.emplace_back("crossing", "xing");
    // word_associations.emplace_back("ped", "xing");
    word_associations.emplace_back("road", "street");
    word_associations.emplace_back("pedestrian", "human");
    word_associations.emplace_back("fast", "speedy");
    word_associations.emplace_back("rapid", "fast");

    NoteEquivalence note_equivalence_finder(word_associations);

    for (auto & [word, connection_node] : note_equivalence_finder.map_of_existing_words) {
        std::cout<<"Word: "<<word<<'\n';
        auto root = connection_node->find_root();
        std::cout<<"Root of this word: "<<root->word<<'\n';
    }


    std::vector<std::string> sentence1 = {"human", "is", "crossing", "street", "with", "a", "dog"};
    std::vector<std::string> sentence2 = {"pedestrian", "xing", "road"};
    std::vector<std::string> sentence3 = {"pedestrian", "street", "is", "xing"};
    std::vector<std::string> sentence4 = {"pedestrian", "bear", "street"};

    std::vector<std::string> sentence5 = {"pedestrian", "fast", "street"};
    std::vector<std::string> sentence6 = {"pedestrian", "rapid", "street"};


    auto result = note_equivalence_finder.is_equivalent(sentence5, sentence6);

    if (result) {
        std::cout<<"Sentence are 5 and 6 Equivalent"<<"\n\n";
    } else {
        std::cout<<"Sentences 5 and 6 are not Equivalent"<<"\n\n";
    }

    // Create nodes for testing find.
    ConnectionNode* nodeA = new ConnectionNode("A");
    ConnectionNode* nodeB = new ConnectionNode("B");
    ConnectionNode* nodeC = new ConnectionNode("C");
    ConnectionNode* nodeD = new ConnectionNode("D");

    // Establish parent-child relationships
    nodeA->add_child(nodeB); // A -> B
    nodeB->add_child(nodeC); // B -> C
    nodeC->add_child(nodeD); // B -> C

    // Find the root node from nodeC
    ConnectionNode* root = nodeD->find_root();

    // // Output the result
    std::cout << "The root node of nodeD is: "<<root->word<<'\n';

    return 0;
}
