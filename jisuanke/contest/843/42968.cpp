/*************************************************************************
  > File Name: 42968.cpp
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




int main() {
    int n,r,R, ans;
    while(~scanf("%d%d%d",&n,&R,&r)){
        ans = 0;
        if(2*r > R){
            //只能放一个盘子
            ans = 1;
        }else if(2*r == R){
            //只能放两个盘子
            ans = 2;
        }else if(3*r == R){
            //可以放6个
            ans = 6;
        }else{
            ans = (int)((atan(1.0) * 4)/(asin(1.0*r/(R-r))));
        }
        printf("%s\n", ans>=n?"yes":"no" );
    }
    
    return 0;
}
