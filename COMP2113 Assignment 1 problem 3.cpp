#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int fac(int p);
int main() {
int n;
double x;
cin>>x>>n;
double sum;
double save=x;

sum=save;

for (int i=0; i<n+1;i++)
{
	save*=x/(i*2)*x/(i*2+1);
sum += pow(-1, i)*save;
}
cout<<fixed<<setprecision(15)<<"sin(x) by cmath: "<<sum<<endl;
cout<<fixed<<setprecision(15)<<"Taylor series approximation:"<<endl;

save=x;sum=save;
cout<<"0 "<<sum<<endl;

for (int i=0; i<n+1;i++)
{
	save*=x/(i*2)*x/(i*2+1);
sum += pow(-1, i)*save;
cout<<fixed<<setprecision(15)<<i<<" "<<sum<<endl;
}

return 0;
}

