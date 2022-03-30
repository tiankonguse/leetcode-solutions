/*************************************************************************
    > File Name: find-first-and-last-position-of-element-in-sorted-array.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月27日 18:22:06
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int lowBound(const vector<int>& nums, int target){
        int left = 0, right = nums.size(), mid;
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid]>=target){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        if(left < nums.size() && nums[left] == target){
            return left;
        }else{
            return -1;
        }
    }
    int upBound(const vector<int>& nums, int target){
        int left = 0, right = nums.size(), mid;
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid]>target){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        if(left > 0 && nums[left - 1] == target){
            return left-1;
        }else{
            return -1;
        }
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {lowBound(nums, target), upBound(nums, target)};
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
*/
int main() {
    #define CLASS Solution
    #define FUNCTION searchRange

    vector<int> first;
    int second;
    vector<int> expectAns;

    first = {5,7,7,8,8,10};
    second = 8;
    expectAns ={3,4};
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {5,7,7,8,8,10};
    second = 6;
    expectAns ={-1, -1};
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    return 0;
}
