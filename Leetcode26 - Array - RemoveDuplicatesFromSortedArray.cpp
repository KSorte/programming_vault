#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> :: iterator ptr1;
        vector<int> :: iterator ptr2;   
        for (ptr1 = nums.begin(); ptr1 < nums.end(); ptr1++)
        // So ptr1 would go till last element. nums.end() points to element after last element. 
        {   ptr2 = ptr1+1;
            while(ptr2!=nums.end() && *ptr1==*ptr2)
           {

           ptr2 = nums.erase(ptr2);  
           }    
        }
    return nums.size(); 
    }
};
int main()
{
    Solution s;
    vector<int> v = {1,2,2,3,3,3,4};
    int S = s.removeDuplicates(v);
    //cout<<S;
    return 0;
}
