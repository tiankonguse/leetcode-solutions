/*************************************************************************
    > File Name: search-in-rotated-sorted-array-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat Apr 27 10:34:29 2019
    > link: https://leetcode.com/problems/search-in-rotated-sorted-array/
    > No: 33. Search in Rotated Sorted Array
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0) {
            return -1;
        }
        int left = 0, right = nums.size()-1;
        //nums value like: k, k+1, ... , MAX,  1, 2, ..., k-1
        while(left <= right) {
            int mid = (left + right)/2;
            if(nums[mid] == target) {
                return mid;
            }
            if(target > nums[right] && nums[mid] <= nums[right]) {
                // target in left part, but mid in right part
                right = mid - 1;
            } else if(target <= nums[right] && nums[mid] > nums[right]) {
                // target in right part, but id in left part
                left = mid + 1;
            } else {
                //target and mid in same part
                if(nums[mid] > target) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }

        return -1;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
*/
int main() {
#define CLASS Solution
#define FUNCTION search

    vector<int> first;
    int second;
    int expectAns;

    first = {4,5,6,7,0,1,2};
    second = 0;
    expectAns = 4;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {4,5,6,7,0,1,2};
    second = 3;
    expectAns = -1;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
