/*************************************************************************
    > File Name: reverse-string.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Mar 14 23:03:43 2019
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();

class Solution {
public:
    void reverseString(vector<char>& s) {
        for(int i=0, j = ((int)s.size())-1;i<j;i++,j--){
            swap(s[i], s[j]);
        }
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.reverseString(firstData);

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

template <class ansType, class dataType1, class dataType2 = int>
void testvoid(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    dataType1 ans = firstData;
    work.reverseString(ans);

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
    vector<char> first;
    vector<char> expectAns;


    first = {'h','e','l','l','o'};
    expectAns = {'o','l','l','e','h'};
    testvoid(expectAns, first);

    first = {'H','a','n','n','a','h'};
    expectAns = {'h','a','n','n','a','H'};
    testvoid(expectAns, first);

    return 0;
}

