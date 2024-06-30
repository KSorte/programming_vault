#include <string>
#include <unordered_map>
#include <utility> // for std::pair
#include <vector>

/*

Leetcode 981 Time Based Key-Value Store.
Create a hashmap that has a string key and value is a vector of pairs.
Each pair is tuple of timestamp and value.
This hashmap should exist in private.

Set function appends the pair to the vector of the key.
Timestamps are assured to be strictly ascending.

Get function queries the vector using binary search over timestamps which are always chronological in the vectors.
If the exact time stamp is not available, the search pointers would overshoot (right pointer to the left of left pointer).
We would return the right pointer - which is the most recent timestamp smaller than the requested.
*/

class TimeMap {
public:
    /**
     * @brief Constructor.
     */
    TimeMap() {

    }

    /**
     * @brief Stores the key key with the value value at the given time timestamp.
     * @param key String key for which value is stored.
     * @param value String value to be stored at key at a timestamp.
     * @param timestamp Integer timestamp for value.
     */
    void set(std::string key, std::string value, int timestamp) {
        // Add the timestamp-value pair to the vector mapped by the key.
        time_based_key_value_map[key].emplace_back(std::pair<int, std::string>(
            timestamp, value));
    }

    /**
     * @brief Returns the string value mapped by key at a timestamp using binary search.
     * @param key String key for which value is queried.
     * @param timestamp Integer timestamp at which value is queried.
     * @returns value String value stored at the key at the timestamp (closest previous if not exact).
     */
    std::string get(std::string key, int timestamp) {
        // Get size of the vector at key to search.
        int num_stamps = time_based_key_value_map[key].size();

        // Initialize pointers for binary search.
        int left = 0, right = num_stamps - 1;

        // O(logn) search
        while(left <= right) {
            // If left exceed right, break out of the loop.
            if (left > right) {
                break;
            }

            // Calculate middle position.
            int middle = (left + right)/2;

            // If middle is timestamp, return it.
            if (timestamp == time_based_key_value_map[key][middle].first) {
                return time_based_key_value_map[key][middle].second;
            }

            // If timestamp greater than middle, go right.
            if (timestamp > time_based_key_value_map[key][middle].first) {
                left = middle + 1;
                continue;
            }

            // If timestamp smaller than middle, go left.
            if (timestamp < time_based_key_value_map[key][middle].first) {
                right = middle - 1;
                continue;
            }
        }  // while loop ends, binary search over.

        // Return the value pointed by the right pointer.
        if (right < 0) {
            // If the requested timestamp is smaller than the smallest available.
            return "";
        }
        return time_based_key_value_map[key][right].second;
    }

private:
    // Time Based Key Value Hashmap.
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> time_based_key_value_map;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */