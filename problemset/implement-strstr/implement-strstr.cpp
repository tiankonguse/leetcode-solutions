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
public:
    int strStr(string haystack, string needle) {
        size_t found = haystack.find(needle);
        if(found == string::npos){
            return -1;
        }
        return found;
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
