#include <iostream>
#include<cstdio>
#include<iomanip>
#include<cmath>
using namespace std;

double Solver(string pin, ){

}

int main(  ) {
   double a,b,c,s,area;  //注意数据类型double 
  cin>>a>>b>>c;
  if(a+b>c&&a+c>b&&b+c>a){
    s=(a+b+c)*1.0/2;
  area=sqrt(s*(s-a)*(s-b)*(s-c));
  cout<<fixed<<setprecision(2)<<area<<endl;
  }
  else{
    cout<<"error input"<<endl;
  }
  return 0;
 }