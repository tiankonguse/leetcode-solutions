/*************************************************************************
    > File Name: find-k-th-smallest-pair-distance.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > link: https://leetcode.com/problems/find-k-th-smallest-pair-distance/
    > No: 719. Find K-th Smallest Pair Distance
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {

    //return the num  <= k   from start
    int littleFind(vector<int>& nums, int start, int k) {
        if(start == nums.size()) {
            return 0;
        }
        int left = start;
        int right = nums.size();
        while(left < right) {
            int mid = (left + right)/2;
            if(nums[mid] <= k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left - start;
    }
    //return the num of pair that <= k
    int pairFind(vector<int>& nums, int k) {
        int ans = 0;
        for(int i=0; i <nums.size(); i++) {
            int first = nums[i] + k;
            ans += littleFind(nums, i+1, first);
        }
        return ans;
    }
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int left = 0;
        int right = nums[n-1] - nums[0] + 1;
        while(left < right) {
            int mid = (left + right)/2;
            int littleNum = pairFind(nums, mid);
            if(littleNum < k) {
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
#define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
//    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
