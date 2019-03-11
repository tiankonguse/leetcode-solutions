/*************************************************************************
    > File Name: plus-one.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Mar 12 00:26:06 2019
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
    vector<int> plusOne(vector<int> digits) {
        int sum = 1;
        for(int i=digits.size()-1;i>=0;i--){
            digits[i] += sum;
            sum = digits[i]/10;
            digits[i] %= 10;
        }
        if(sum){
            digits.insert(digits.begin(), sum);
        }
        return digits;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.plusOne(data);

    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("data", data);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> data;
    vector<int> expectAns;


    data = {1,2,3};
    expectAns = {1,2,4};
    test(expectAns, data);

    data = {4,3,2,1};
    expectAns = {4,3,2,2};
    test(expectAns, data);

    data = {0};
    expectAns = {1};
    test(expectAns, data);

    data = {9,0,9};
    expectAns = {9,1,0};
    test(expectAns, data);

    data = {9,9,9};
    expectAns = {1, 0, 0, 0};
    test(expectAns, data);

    return 0;
}
