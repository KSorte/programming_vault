#include<iostream>
#include<unordered_set>
#include<vector>

/**
 * @brief Given an integer array nums, return true if any value appears at least twice in the array,
 * and return false if every element is distinct.
 *
 * This function iterates through the given integer array and uses an unordered set
 * to track elements that have been seen. If an element is found in the set, it means
 * the element is a duplicate and the function returns true. Otherwise, it inserts
 * the element into the set and continues. If no duplicates are found after checking
 * all elements, the function returns false.
 *
 * @param nums The vector of integers to check for duplicates.
 * @return True if any value appears at least twice in the array, otherwise false.
 */

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
    // An unordered set to store iterated from nums.
    std::unordered_set<int> numset;
    for(int i=0; i<nums.size(); i++)
    {
      // .find returns an iterator if the element is found, else returns an iterator to the end of the set.
      // if element at ith place already exists in the set, return true.
      if(numset.find(nums[i])!=numset.end()) return true;
      // If element at ith place not already in set, insert it.
      numset.insert(nums[i]);
    }
    return false;
    }
};

int main()
{
    Solution solution;

    std::vector<int> nums1 = {1, 2, 3, 4, 5};
    std::vector<int> nums2 = {1, 2, 3, 4, 1};

    std::cout << "Test 1 - Expected: false, Actual: " << std::boolalpha << solution.containsDuplicate(nums1) << std::endl;
    std::cout << "Test 2 - Expected: true, Actual: " << std::boolalpha << solution.containsDuplicate(nums2) << std::endl;

    return 0;
}
