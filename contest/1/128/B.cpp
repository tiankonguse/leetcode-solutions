/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 17 10:29:18 2019
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
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> smallTime(60, 0);
        for(int i=0;i<time.size();i++){
            smallTime[time[i]%60]++;
        }
        int ans = 0;
        if(smallTime[0] > 0){
            ans += smallTime[0] * (smallTime[0] - 1)/2;
        }
        if(smallTime[30] > 0){
            ans += smallTime[30] * (smallTime[30] - 1)/2;
        }

        for(int i=1;i<30;i++){
            ans += smallTime[i] * smallTime[60-i];
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.numPairsDivisibleBy60(firstData);

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
    vector<int> first;
    int expectAns;


    first = {30,20,150,100,40};
    expectAns =3;
    test(expectAns, first);


    first = {60,60,60};
    expectAns =3;
    test(expectAns, first);

    return 0;
}

