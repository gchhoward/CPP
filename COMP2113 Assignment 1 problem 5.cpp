#include <iostream>
#include<string>
#include <cmath>
#include<limits>

using namespace std;
void RectangleBB(double &xmin, double &xmax, double &ymin, double &ymax);
void CircleBB(double &xmin, double &xmax, double &ymin, double &ymax);
void PointsetBB(double &xmin, double &xmax, double &ymin, double &ymax);
int main() {

char r;
double xmin, xmax, ymin, ymax;
while (r != '#'){
cin>>r;
if (r=='R'){
  RectangleBB(xmin, xmax, ymin, ymax);
}
if (r=='C'){
  CircleBB(xmin, xmax, ymin, ymax);
}
if (r=='P'){
  PointsetBB(xmin, xmax, ymin, ymax);
}

}
double x_result, y_result, height_result, width_result;
x_result = (xmax + xmin)/2;
y_result = (ymax +ymin)/2;
height_result = ymax - ymin;
width_result = xmax - xmin;
cout << x_result << " "<< y_result<<" " << width_result<<" " << height_result<<endl;
return 0;
}

void RectangleBB(double &xmin, double &xmax, double &ymin, double &ymax)
{
  double x,y,width,height;
  cin>>x>>y>>width>>height;
  double temp_x, temp_y;
  
  if (x - width/2 < xmin){
    xmin = x - width/2;
  }
  else if (x + width/2 > xmax){
    xmax = x + width/2;
  }
  if (y - height/2 < ymin){
    ymin = y - height/2;
  }
  else if (y + height/2 > ymax){
    ymax = y + height/2;
  }
}
void CircleBB(double &xmin, double &xmax, double &ymin, double &ymax)
{
double x,y,radius;
cin>>x>>y>>radius;
if (x - radius < xmin){
    xmin = x - radius;
  }
  else if (x + radius > xmax){
    xmax = x + radius;
  }
  if (y - radius < ymin){
    ymin = y - radius;
  }
  else if (y + radius > ymax){
    ymax = y + radius;
  }
}
void PointsetBB(double &xmin, double &xmax, double &ymin, double &ymax){
double n,x,y;
cin>>n;
for(int i=0;i < n;i++){
  cin>>x>>y;
  if (x < xmin){
    xmin = x;
  }
  else if(x > xmax){
    xmax = x;
  }
  if (y < ymin){
    ymin = y;
  }
  else if(y > ymax){
    ymax = y;
  }

}

}

