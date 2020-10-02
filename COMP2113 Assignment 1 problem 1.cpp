#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main() {
  float x;
  int n;
  cin>>x>>n;
  float temp;
  float sum=0;
 for (int i=0; i<n+1; i++)
{
cin>>temp;
sum += temp * pow(x, n-i);
}
cout<<fixed<<setprecision(6)<<sum;
return 0;
}