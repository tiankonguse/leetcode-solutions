/*************************************************************************
    > File Name: max-consecutive-ones.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Mar 15 00:25:29 2019
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
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int left =-1, right = -1;
        int ans = 0;
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] == 0) {
                left = right = -1;
            } else {
                if(left == -1) {
                    left = i;
                }
                right = i;
                ans = max(ans, right - left + 1);
            }
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.findMaxConsecutiveOnes(firstData);

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


    first = {1,1,0,1,1,1};
    expectAns = 3;
    test(expectAns, first);


    first = {1,1,0};
    expectAns = 2;
    test(expectAns, first);


    first = {0, 1,1};
    expectAns = 2;
    test(expectAns, first);


    first = {0, 1,1, 0};
    expectAns = 2;
    test(expectAns, first);



    first = {1,1};
    expectAns = 2;
    test(expectAns, first);



    first = {0,0,0};
    expectAns = 0;
    test(expectAns, first);
    return 0;
}

