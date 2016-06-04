/*************************************************************************
  > File Name: valid-parentheses.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月11日 星期四 00时00分56秒
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
    bool isValid(string s) {
        stack<char>sta;
        int l = s.length();

        for(int i=0;i<l;i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                sta.push(s[i]);
            }else{
                if(sta.empty()){
                    return false;
                }
                if(s[i] == ')' && sta.top() == '('){
                    sta.pop();
                }else if(s[i] == ']' && sta.top() == '['){
                    sta.pop();
                }else if(s[i] == '}' && sta.top() == '{'){
                    sta.pop();
                }else{
                    return false;
                }
            }
        }
        return sta.empty();
    }
};
int main() {

    return 0;
}
