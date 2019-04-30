/*************************************************************************
> File Name: regular-expression-matching.cpp
> Author: tiankonguse(skyyuan)
> Mail: i@tiankonguse.com 
> Created Time: 2015年05月19日 星期二 22时19分48秒
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
    map<pair<int,int>, int>m;
    int isMatch(string&s, string&p,int first, int second){
        pair<int,int>nowPair(first,second);

        if(m.find(nowPair) != m.end()){
            return m[nowPair];
        }
        if(first == s.size() && second == p.size()){
            m[nowPair] = 1;
        }else if(first == s.size() && second < p.size()){
            if(second + 1 < p.size() && p[second + 1] == '*' ){
                if(isMatch(s, p, first, second + 2)){
                    m[nowPair] = 1;
                }else{
                    m[nowPair] = 0;
                }
            }else{
                m[nowPair] = 0;
            }
        }else if(first < s.size() && second == p.size()){
            m[nowPair] = 0;
        }else{
            if(s[first] == p[second] || p[second] == '.'){
                if(second +1 < p.size() && p[second+1] == '*'){
                    if(isMatch(s,p, first+1, second) || isMatch(s,p,first, second+2)){
                        m[nowPair] = 1;
                    }else{
                        m[nowPair] = 0;
                    }
                }else{
                    if(isMatch(s,p, first+1, second+1)){
                        m[nowPair] = 1;
                    }else{
                        m[nowPair] = 0;
                    }
                }
            }else if(second + 1 < p.size() && p[second + 1] == '*'){
                if(isMatch(s,p,first, second+2)){
                    m[nowPair] = 1;
                }else{
                    m[nowPair] = 0;
                }
            }else{
                m[nowPair] = 0;
            }
        }

        return m[nowPair];
    }
public:
    bool isMatch(string s, string p) {
        m.clear();
        int ans = isMatch(s,p,0,0);
        return ans;
    }
    };


void test(char const*s, char const* p){
    int ans = 0;
    Solution work;
    ans = work.isMatch(s,p);
    printf("s=%s, p=%s, ans=%d\n", s,p,ans);
}

int main() {

    test("", "");
    test("aa", "a");
    test("aa", "aa");
    test("aaa", "aa");
    test("aa", "a*");
    test("aa", ".*");
    test("ab", ".*");
    test("aab", "c*a*b");

    return 0;
}
