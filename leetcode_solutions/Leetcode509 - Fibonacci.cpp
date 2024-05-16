  #include <iostream>
 #include <vector>
 #include <string>

using namespace std;
  int fib(int n) {
      int f = 0; int s = 1; int sum = 1; //initilizing all three variables
      if (n == 0){return 0;}
      for (int i = 2; i<=n; i++){
          sum = f + s;
          f = s;
          s = sum;
          } 
          return sum;   
    }
    int main()
    {
        int s = fib(9);
        cout<<" This sum is :"<<endl;
        cout<<s; 
    }
