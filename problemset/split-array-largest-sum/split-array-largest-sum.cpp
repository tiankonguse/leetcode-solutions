/*************************************************************************
    > File Name: split-array-largest-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 9日 21:51:44
    > link: https://leetcode.com/problems/split-array-largest-sum/
    > No: 410. Split Array Largest Sum
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int check(vector<int>& nums, long long mid) {
        int ans = 1;
        long long tmpSum = nums[0];
        for(int i=1; i<nums.size(); i++) {
            if(tmpSum + nums[i] > mid) {
                ans++;
                tmpSum = nums[i];
            } else {
                tmpSum += nums[i];
            }
        }
        return ans;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        long long left = nums[0];
        long long right = 1;
        for(int i=0; i<nums.size(); i++) {
            right += nums[i];
            left = max(left, (long long)nums[i]);
        }
        while(left < right) {
            long long mid = (left + right)/2;
            if(check(nums, mid) > m) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;

    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION splitArray

    vector<int> first;
    int second;
    int expectAns;

    first = {7,2,5,10,8};
    second = 2;
    expectAns = 18;
    TEST_SMP2(CLASS, FUNCTION, expectAns, first, second);

    return 0;
}
