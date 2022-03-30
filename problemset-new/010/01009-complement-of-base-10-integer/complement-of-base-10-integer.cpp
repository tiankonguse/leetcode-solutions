/*************************************************************************
    > File Name: complement-of-base-10-integer.cpp
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
    int bitwiseComplement(int N) {
        vector<int> bit;
        if(N == 0){
            return 1;
        }
        while(N>0){
            bit.push_back(N%2);
            N /= 2;
        }
        int sum = 0;
        for(int i=bit.size()-1;i>=0;i--){
            sum *= 2;
            if(!bit[i]){
                sum += 1;
            }
        }
        return sum;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.bitwiseComplement(firstData);

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
    int first;
    int expectAns;


    first = 5;
    expectAns = 2;
    test(expectAns, first);

    first = 7;
    expectAns = 0;
    test(expectAns, first);


    first = 10;
    expectAns = 5;
    test(expectAns, first);
    return 0;
}

