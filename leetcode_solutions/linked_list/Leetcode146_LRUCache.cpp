#include <list>
#include <memory>
#include <unordered_map>

/*
    Leetcode 146 LRU Cache
    https://leetcode.com/problems/lru-cache/description/

    Algorithm:
    An unordered map mapping from key to the value.
    A doubly linked list to access the front (most recently used) and the back (least recently used) elements
    with O(1).

    Use <list> to use C++ doubly linked list. It should be a list of pairs (key, value) because when you do pop_back() on
    this list to remove the LRU element, you also need to remove it from the map, for which key is needed.

    The map stores list iterators as values.
    When putting a new element, or accessing it, put the (key value) pair to the front of the list and then update the iterator
    in the map using list.begin().

    Using an existing implementation in C++ is always better than writing your own. Implememting a custom list was easy, but unneeded
    and is a bad practice.

*/

class LRUCache {
public:
    /**
     * @brief Constructor.
     */
    LRUCache(int capacity) : capacity(capacity){}

    /**
     * @brief Gets the value associated to the key if present.
     * If not return -1.
     * @param key Int key to get value of.
     * @return Int value associated to the key.
     */
    int get(int key) {

        // O(1)
        if (cache_map.find(key) == cache_map.end()) {
            return -1;
        }

        // Move the accessed element to the front. O(1)
        cache_list.splice(cache_list.begin(), cache_list, cache_map[key]);

        return cache_map[key]->second;
    }

    /**
     * @brief Adds the key value pair to the LRU data structure and removes the least recently used if
     * capacity exceeds.
     * @param key Int key to add.
     * @param value Int value to add.
     */
    void put(int key, int value) {
        // If key doesnt exist in the map. O(1)
        if (cache_map.find(key) == cache_map.end()) {
            // Add value to the front of the doubly linked list.
            cache_list.push_front({key, value});

            // Add to map.
            cache_map[key] = cache_list.begin();

            if (cache_list.size() > capacity) {
                // Get LRU element O(1)
                auto back_element = cache_list.back();

                // Erase LRU element from map and list O(1)
                cache_map.erase(back_element.first);
                cache_list.pop_back();
            }
            return;
        }

        // Update value to key in map.
        cache_map[key]->second = value;

        // Move to front.
        cache_list.splice(cache_list.begin(), cache_list, cache_map[key]);

    }

private:
    // Map to store associations between keys and node elements.
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map;

    // Cache list
    std::list<std::pair<int, int>> cache_list;

    // Cache capacity.
    int capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */