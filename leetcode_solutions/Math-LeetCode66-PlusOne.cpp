/*You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.*/

    vector<int> plusOne(vector<int>& digits) {

    int flag = 0;
    int len = digits.size();
    for (int i = len-1; i>=0; i-- )
    {
        if (digits[i] == 9) {digits[i] = 0; continue;  /*skip later steps in the iteration*/ }
        else {digits[i]+=1; flag =1; break;}
    }   // for loop ends

    if (flag == 0){digits.insert(digits.begin(),1); }
    return digits;
    }


