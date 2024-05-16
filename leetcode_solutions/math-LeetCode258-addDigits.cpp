#include <iostream>
using namespace std;
class Solution {
public:
    int Sum(int num){
        int sum = 0;
        while (true)
        {
            sum += num%10;
            num = (num - num%10)/10;  // Cutting last digit
            if (num == 0){break;}
        }
        return sum;
    }
    int addDigits(int num) {
      
        while(num>=10)
        {
            num = Sum(num);
        }
        return num;
    }
};

int main()
{
    Solution s;
    cout<<s.addDigits(474829)<<endl;
    return 0;
}
