/*************************************************************************
    > File Name: find-peak-element.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 11:23:44 2019
    > link: https://leetcode.com/problems/find-peak-element/
    > No: 162. Find Peak Element
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size()-1, mid;
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid] > nums[mid+1]){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
*/
int main() {
    #define CLASS Solution
    #define FUNCTION findPeakElement

    vector<int> first;
    int expectAns;

    first = {1,2,3,1};
    expectAns = 2;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {1,2,1,3,5,6,4};
    expectAns = 5;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
