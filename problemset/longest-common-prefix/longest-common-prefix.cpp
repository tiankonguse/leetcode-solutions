/*************************************************************************
  > File Name: longest-common-prefix.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
  > Created Time: 2015年04月16日 12:51:15
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
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0){
            return "";
        }

        const string& first = strs[0];
        int ansLen = first.length();
        for(int i=1; i< strs.size(); i++){
            const string& str = strs[i];
            ansLen = min(ansLen, (int)str.length());
            for(int j=0;j<ansLen;j++){
                if(str[j] != first[j]){
                    ansLen = j;
                    break;
                }
            }
            if(ansLen == 0){
                return "";
            }
        }
        return first.substr(0,ansLen);
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.longestCommonPrefix(firstData);

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
    vector<string> first;
    string expectAns;

    first = {"flower","flower","flower"};
    expectAns = "flower";
    test(expectAns, first);

    first = {"flower","flow","flight"};
    expectAns = "fl";
    test(expectAns, first);


    first = {"dog","racecar","car"};
    expectAns = "";
    test(expectAns, first);

    first = {};
    expectAns = "";
    test(expectAns, first);

    return 0;
}


