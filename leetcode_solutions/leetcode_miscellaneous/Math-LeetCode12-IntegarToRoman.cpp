// Online C++ compiler to run C++ program online
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;
string addletter(string roman,int n,string letter){
        for(int i=1; i<=n; i++){roman.insert(0,letter);}
        return roman;}
    string intToRoman(int num) {
        
        vector<int> vect;
        int flag = 0;
        int digit;
        string roman;
        while(true)
        {
           digit = num%10;
           num = floor(num/10);
           vect.insert(vect.begin(),digit);
           if (num == 0){break;} 
        }
        int len = vect.size(); 
        for (int i=len-1; i>=0; i--)
        {   
            digit = vect[i];
             if (digit == 5)
            {
             if(len-i==1) { roman.insert(0,"V");}
             if(len-i==2){ roman.insert(0,"L");}
             if(len-i==3){ roman.insert(0,"D");}
            } 
            
            if (digit == 4)
            {
             if(len-i==1){roman.insert(0,"IV");}
             if(len-i==2){ roman.insert(0,"XL");}
             if(len-i==3){ roman.insert(0,"CD");}
            } 
             if (digit == 9)
            {
             if(len-i==1) { roman.insert(0,"IX");}
             if(len-i==2){ roman.insert(0,"XC");}
             if(len-i==3){ roman.insert(0,"CM");}
            } 
            if (digit <=3)
            {
                if(len-i==1){roman = addletter(roman,digit,"I");}
                if(len-i==2){roman = addletter(roman,digit,"X");}
                if(len-i==3){roman = addletter(roman,digit,"C");}
                if(len-i==4){roman = addletter(roman,digit,"M");}
            }
             if (digit>=6 && digit<=8)
            {
                if(len-i==1){roman =  addletter(roman,digit-5,"I"); roman.insert(0,"V");}
                if(len-i==2){roman = addletter(roman,digit-5,"X"); roman.insert(0,"L");}
                if(len-i==3){roman = addletter(roman,digit-5,"C"); roman.insert(0,"D");}
            }
        }
        return roman;
    };

int main()
{
    int n = 2567;
    cout<<intToRoman(n)<<endl;
    return 0;
}

// Output : MMDLXVII

// OR A BETTER WAY
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
class Solution {
public:
    string intToRoman(int num) {
        int n[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        string r[] = {"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};

        string ans;
        int i = 12;
        int div;
        while(num>0)
        {
            div = num/n[i];
            num = num % n[i];
            while(div--) ans += r[i];
            i--;
        }

        return ans;
    }
};

int main()
{ Solution s;
 int number = 27;
 string roman;
 roman = s.intToRoman(number);
 cout<<roman<<endl;
 return 0;
}
