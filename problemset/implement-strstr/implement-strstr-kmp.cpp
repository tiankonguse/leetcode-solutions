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
#include "../../include/base.h"
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
class Solution {
    vector<int> next;
    void get_next(const char *pat) {
        for(int i=1,k; pat[i]; ++i) {
            for(k=next[i-1]; k>=0 && pat[i]!=pat[k+1]; k=next[k]);
            if(pat[k+1] == pat[i])
                next[i]=k+1;
        }
    }
    int kmp(const char* str, const char* pat) {
        next.resize(strlen(pat)+1, -1);
        get_next(pat);
        int i=0, j=0;
        while( str[i] && pat[j] ) {
            if( pat[j] == str[i] ) {
                ++i;
                if(!pat[++j]){
                    return i-j;
                }
            } else if(j == 0)
                ++i;
            else
                j = next[j-1]+1;
        }
        return -1;
    }
public:
    int strStr(string haystack, string needle) {
        if(needle.length() == 0)return 0;
        return kmp(haystack.c_str(), needle.c_str());
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.strStr(firstData, secondData);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("firstData", firstData);
        output("secondData", secondData);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    string first;
    string second;
    int expectAns;


    first = "hello";
    second = "ll";
    expectAns = 2;
    test(expectAns, first, second);


    first = "aaaaa";
    second = "bba";
    expectAns = -1;
    test(expectAns, first, second);



    first = "aaa";
    second = "a";
    expectAns = 0;
    test(expectAns, first, second);



    first = "aaa";
    second = "";
    expectAns = 0;
    test(expectAns, first, second);

    return 0;
}
