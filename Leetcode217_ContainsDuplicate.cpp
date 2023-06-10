//Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> numset;
    int i;
    for(i=0;i<nums.size();i++)
    {
      if (numset.find(nums[i])!=numset.end()) return true;
      // .find returns an iterator if the element is found, else returns an iterator to the end of the set. 
      numset.insert(nums[i]);
      
    }
    return false;   
    }
};
