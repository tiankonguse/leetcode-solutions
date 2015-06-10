/*************************************************************************
  > File Name: implement-strstr.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月11日 星期四 00时30分24秒
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
class Solution {
public:
    int strStr(string haystack, string needle) {
        size_t found = haystack.find(needle);
        if(found == string::npos){
            return -1;
        }
        return found;
    }
};
int main() {

    return 0;
}
