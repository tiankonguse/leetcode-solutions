/*************************************************************************
  > File Name: isomorphic-strings.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月07日 星期日 14时16分08秒
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
    bool isIsomorphic(string s, string t) {
        int m_s_t[257];
        int m_t_s[257];
        memset(m_s_t, -1, sizeof(m_s_t));
        memset(m_t_s, -1, sizeof(m_t_s));
        int l = s.length();

        for(int i=0;i<l;i++){
            if(m_s_t[s[i]] == -1 && m_t_s[t[i]] == -1){
                m_s_t[s[i]] = t[i];
                m_t_s[t[i]] = s[i];
            }else if(m_s_t[s[i]] == t[i] && m_t_s[t[i]] == s[i]) {
                continue;
            }else{
                return false;
            }
        }

        return true;
    }
};

void test(string s, string t){
    Solution work;
    int ans;
    ans = work.isIsomorphic(s,t);
    printf("<%s, %s> = %d\n", s.c_str(), t.c_str(), ans);
}



int main() {
   

    test("egg", "add");
    test("foo", "bar");
    test("paper", "title");
    test("ab","aa");
    return 0;
}
