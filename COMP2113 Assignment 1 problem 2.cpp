#include <iostream>
using namespace std;
int main() {
  int a, b, divisor1, divisor2;
  cout<<"a: ";
  cin>>a;
  cout<<"b: ";
  cin>>b;
  cout<<"Divisor 1: ";
  cin>>divisor1;
  cout<<"Divisor 2: ";
  cin>>divisor2;

  cout<<"M "<<divisor1<<" "<<divisor2<<endl;
  int divisible1, divisible2;
  for(int i = a; i < b; i++){
    if (i%divisor1 == 0){
      divisible1 = 1; 
    }
    else{
      divisible1 = 0;
    }
    if (i%divisor2 == 0){
      divisible2 = 1; 
    }
    else{
      divisible2 = 0;
    }
    cout<< i << " " << divisible1 << " " << divisible2 <<endl;
  }
}
