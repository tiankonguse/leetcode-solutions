/*************************************************************************
    > File Name: minimum-size-subarray-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Mar 15 00:34:46 2019
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
    vector<int> sum;
    int search(int left, int right, int val){
        int mid = 0;
        int start = left;
        while(left <= right){
            mid = (left + right)/2;
            if(sum[mid] >= val){
                if(left == right){
                    return mid - start + 1;
                }else{
                    right = mid;
                }
            }else{
                left = mid + 1;
            }
        }
        return -1;
    }
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.size() == 0)return 0;

        sum.resize(nums.size()+1, 0);
        sum[0] = 0;
        for(int i=0;i<nums.size();i++){
            sum[i+1] = sum[i] + nums[i];
        }

        int ans = nums.size() + 1;
        for(int i = 0; i<nums.size(); i++) {
            int tmpAns = this->search(i+1, nums.size(), sum[i] + s);
            if(tmpAns > 0){
                ans = min(ans, tmpAns);
            }
        }
        if(ans == nums.size() + 1){
            ans = 0;
        }
        return ans;
    }
};

template <class ansType, class dataType1, class dataType2 = int>
void test(ansType& expectAns, dataType1& firstData, dataType2 secondData = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.minSubArrayLen(firstData, secondData);

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
    vector<int> second;
    int expectAns;


    first = 7;
    second = {2,3,1,2,4,3};
    expectAns = 2;
    test(expectAns, first, second);


    first = 100;
    second = {2,3,1,2,4,3};
    expectAns = 0;
    test(expectAns, first, second);
    return 0;
}

