/*************************************************************************
  > File Name: 42853.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 13:50 2017/8/23
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

double f1(int n){
    double sum = 0;
    for(int i=1;i<=n;i++){
        sum += 1.0*n/i;
    }
    return sum;
}

double f2(int n){
    return n*(log(n) + 0.577215664901532860606512090082402431042159335);
}


int main() {
    int t;
    LL N;
    int n;
    double sum;
    scanf("%d", &t);
    
    for(int i=1;i<=t;i++){
        scanf("%d", &n);
        if(n < 5000){
            sum = f1(n);
        }else{
            sum = f2(n);
        }
        sum += 0.999999;
        printf("%d\n", (int)sum);
    }
    
    
    return 0;
}
