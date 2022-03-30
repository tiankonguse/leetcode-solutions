/*************************************************************************
    > File Name: binary-search.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Fri Apr 26 22:16:21 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size(), mid;
        while(left < right){
            mid = (left + right)/2;
            if(nums[mid] < target){
                left = mid + 1;
            }else if(nums[mid] == target){
                return mid;
            }else{
                right = mid;
            }
        }
        return -1;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION search

    vector<int> first;
    int second;
    int expectAns;

    first = {-1,0,3,5,9,12};
    second = 9;
    expectAns = 4;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = {-1,0,3,5,9,12};
    second = 2;
    expectAns = -1;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
