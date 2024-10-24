#include <iostream>
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
    This implementation assumes the following:
        1. Sentences are in the same format and with same number of words.
        For example pedestrian crossing street; human xing street
        Each word is of the same "nature". (Human, Crossing, Street).

        What this means that ith word in both sentences is of the same type and if it is not, return false.
        2. If the there is transitivity, eg (pedestrian, ped), (ped, human) and there is no direct connection b/w
        "pedestrian" and "human", then this algorithm doesn't consider those two words equivalent.
*/

class NoteEquivalenceBasic {
public:
    // Constructor.
    NoteEquivalenceBasic(std::vector<std::pair<std::string, std::string>> word_associations) :
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
        bool is_equivalent_if_word1_key, is_equivalent_if_word2_key;

        // Assuming that sentences are in the same format and with same number of words,
        // iterate through the sentences.
        for (size_t i = 0; i < sentence1.size(); i++) {
            is_equivalent_if_word1_key = false, is_equivalent_if_word2_key = false;

            if (sentence1[i] == sentence2[i]) {
                // Words equal.
                continue;
            }

            if (word_groupings_map.find(sentence1[i]) != word_groupings_map.end()) {
                // Word1 found in the keys, search if word2 in its set.
                if (word_groupings_map[sentence1[i]].find(sentence2[i]) != word_groupings_map[sentence1[i]].end()) {
                    // Words match.
                    is_equivalent_if_word1_key = true;
                }
            }

            if (word_groupings_map.find(sentence2[i]) != word_groupings_map.end()) {
                // Word2 found in the keys, search if word1 in its set.
                if (word_groupings_map[sentence2[i]].find(sentence1[i]) != word_groupings_map[sentence2[i]].end()) {
                    // Words match.
                    is_equivalent_if_word2_key = true;
                }
            }

            if (!(is_equivalent_if_word1_key || is_equivalent_if_word2_key)) {
                // If both combinations yield failure, then the two words are not equivalent,
                // and hence the sentences are not equivalent.
                return false;
            }
        }
        return true;
    }

private:
    // Associations of words.
    std::vector<std::pair<std::string, std::string>> word_associations;

    // Map to store the word associations.
    std::unordered_map<std::string, std::unordered_set<std::string>> word_groupings_map;

    /**
     * @brief Groups the words using the vector of word associations.
     */
    void group_data() {
        // Iterate through the word associations taken as input
        for (auto & [first_word, second_word] : word_associations) {
            // Add second word in pair to the set mapped by the first.
            word_groupings_map[first_word].insert(second_word);
        }
    }
};

int main() {
    std::vector<std::pair<std::string, std::string>> word_associations;
    word_associations.emplace_back("pedestrian", "ped");
    word_associations.emplace_back("ped", "human");
    word_associations.emplace_back("crossing", "xing");
    word_associations.emplace_back("road", "street");
    word_associations.emplace_back("pedestrian", "human");

    NoteEquivalenceBasic note_equivalence_object(word_associations);

    std::vector<std::string> sentence1 = {"human", "crossing", "street"};
    std::vector<std::string> sentence2 = {"pedestrian", "xing", "road"};
    std::vector<std::string> sentence3 = {"pedestrian", "street", "xing"}; // Not equivalent to sentence 1 or 2.
    std::vector<std::string> sentence4 = {"pedestrian", "crossing", "street"};

    auto result = note_equivalence_object.is_equivalent(sentence1, sentence4);

    if (result) {
        std::cout<<"Equivalent"<<"\n";
    } else {
        std::cout<<"Not Equivalent"<<"\n";
    }
}
