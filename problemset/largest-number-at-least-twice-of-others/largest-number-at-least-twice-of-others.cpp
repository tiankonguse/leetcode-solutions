/*************************************************************************
    > File Name: largest-number-at-least-twice-of-others.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Mar 12 00:19:10 2019
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
    int dominantIndex(vector<int>& nums) {
        int maxNum = nums[0];
        int maxIndex = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] > maxNum){
                maxNum = nums[i];
                maxIndex = i;
            }
        }
        for(int i=0;i<nums.size();i++){
            if(i == maxIndex){
                continue;
            }
            if(nums[i] * 2 > maxNum){
                return -1;
            }
        }
        return maxIndex;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.dominantIndex(data);

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
    int expectAns;


    data = {3, 6, 1, 0};
    expectAns = 1;
    test(expectAns, data);


    data = {1, 2, 3, 4};
    expectAns = -1;
    test(expectAns, data);

    data = {0,0,0,1};
    expectAns = 3;
    test(expectAns, data);

    return 0;
}
