#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
      vector<int> :: iterator ptr;
      ptr = nums.begin();
      while (ptr<nums.end())
      {
         if(*ptr == val) {ptr = nums.erase(ptr);}
         else{ptr++;}
      }
      return nums.size();
    }
};


int main()
{
Solution s;
vector<int> v = {1,3,5,5,8,4,5,1,5};
int val = 5;
cout<<s.removeElement(v,val)<<endl;
for (int i = 0; i<v.size();i++)
{cout<<v[i]<<endl;}
return 0;
}
