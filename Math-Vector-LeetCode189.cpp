//Given an array, rotate the array to the right by k steps, where k is non-negative.

// Intially, I just copied one element from vector end, added to beginning using .begin(). However, the .begin is O(n). So I got TLE error. Then, I made a list. There, they have a push_front method. However, the 'next' or 'advance' methods for accessing elements of the list is O(n).
#include<iostream>
#include<vector>
#include<list>
#include <algorithm>
using namespace std;
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        reverse(nums.begin(), nums.end());   // Reversing the string. So // rotation direction also reverses.
        int len = nums.size();

       for (int i=1; i<=k; i++)
       {
           nums.push_back(nums[i-1]);  // Adding i-1 th element to end of the reversed vector.  
       } 

          reverse(nums.begin(), nums.end());   // Reversing the vector pop_back
          nums.resize(len);
    }
};

int main()
{
    Solution s;
     vector<int> vect;
    vect.push_back(10);
    vect.push_back(20);
    vect.push_back(30);
    vect.push_back(40);
    vect.push_back(50);
    int k = 2;
    s.rotate(vect, k);
    for (int i = 1; i<=vect.size(); i++)
    {
        cout<<vect[i-1]<<endl;
    }
}
/* Method 1 : 
IN A FOR LOOP - k times
Get last element - using .back()
Insert last element at the beginning using .insert() - O(n)
delete last element using pop_back O(1)
*/
// Time complexity exceeds permissible limits(O 10^9) for METHOD 1. 
/*
Stored all elements to a list.
IN A FOR LOOP 
 for (int i=1; i<=k; i++)
       {
          // auto it1 = next(list1.begin(),len-1);    // TIME COMPLEXITY - O(N) !!!!!!!!!! This is not good. 
           //list1.push_front(*it1);   
           //list1.pop_back(); // Deleting the last element
       }
        // filling nums vector with changed list
      // for(int i = 1; i<=len; i++) {
        //   auto it1 = next(list1.begin(),i-1);
          // nums[i-1] = *it1;}  

          For loop of the order of k*n for both METHODS. Would exceed 10^9 for k = n = 10^5. 
Accessing elements for the list itself is very expensive. 
*/
