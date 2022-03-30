/*************************************************************************
    > File Name: find-pivot-index.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Mar 12 00:03:35 2019
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
    int pivotIndex(vector<int>& nums) {
        const int n = nums.size();
        if(n == 0){
            return -1;
        }

        vector<int> frontSum(nums.size(), 0);
        vector<int> backSum(nums.size(), 0);
        frontSum[0] = nums[0];
        for(int i = 1;i<n;i++){
            frontSum[i] = frontSum[i-1] + nums[i];
        }
        backSum[n - 1] = nums[n - 1];
        for(int i = n - 2;i>=0;i--){
            backSum[i] = backSum[i+1] +  nums[i];
        }
        for(int i=0;i<n;i++){
            if(frontSum[i] == backSum[i]){
                return i;
            }
        }
        return -1;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& data, dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.pivotIndex(data);

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


    data = {1, 7, 3, 6, 5, 6};
    expectAns = 3;
    test(expectAns, data);


    data = {1, 2, 3};
    expectAns = -1;
    test(expectAns, data);

    return 0;
}
