#include<string>
#include<iostream>
#include<map> 

int romanToInt(string s) {
        map<char,int> map1;
        map1['I']=1;
        map1['V']=5;
        map1['X']=10;
        map1['L'] = 50;
        map1['C']=100;
        map1['D']=500;
        map1['M']=1000;

        int len = s.size();
        int sum = 0;
        int flag = 0;  // when a subtraction happens, this flag become 1. 
        for(int i = len-1; i>=0; i--)
        {
         if (flag == 1){flag = 0; continue;}   //skipping the iteration when subtraction happens.
          sum+=map1[s[i]];
          if (i == 0) {continue;}     // Not making the subtraction check if we have reached the beginning of string
          else if(map1[s[i-1]]<map1[s[i]]) {sum-=map1[s[i-1]]; flag = 1;}  // Subtracting if a smaller value comes before bigger value
        }
        return sum;
    };


void main()
{
string s1 = "IV";
cout<<romanToInt(s1);
}
