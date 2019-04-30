/*************************************************************************
  > File Name: longest-substring-without-repeating-characters.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年05月18日 20:58:35
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
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        vector<int> vec(256,-1);
        int left = 0;
        int now = 0;
        int size = s.length();
        int c = 0;
        for(int i=0;i<size;i++){
            c = s[i] ;
            if(vec[c] != -1 && vec[c] >= left){
                left = vec[c] + 1;
            }
            
            vec[c] = i;
            now = i - left + 1;
            if(now > ans){
                ans = now;
            }
        }

        return ans;        
    }
};


void test(char const* _in, int ans){
    Solution work;
    int now;
    string in = _in;
    now = work.lengthOfLongestSubstring(_in);
    printf("in=%s out=%d ans = %d %s\n", in.c_str(), now, ans, now==ans?"YES":"NO");
            
}


int main() {
    test("abcabcbb", 3);
    test("bbbbb", 1);
    return 0;
}
