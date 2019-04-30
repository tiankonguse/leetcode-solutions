/*************************************************************************
    > File Name: find-minimum-in-rotated-sorted-array-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 11:56:31 2019
    > link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
    > No: 153. Find Minimum in Rotated Sorted Array
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1, mid;
        // k, k+1, ..., Max - 1, Max, 1, 2, ..., k-2, k-1
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid] > nums[right]){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        return nums[left];
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
*/
int main() {
    #define CLASS Solution
    #define FUNCTION findMin

    vector<int> first;
    int expectAns;

    first = {3,4,5,1,2};
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {4,5,6,7,0,1,2};
    expectAns = 0;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
