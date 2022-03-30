/*************************************************************************
    > File Name: contains-duplicate-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Tue Apr 23 23:51:24 2019
    > link: https://leetcode.com/problems/contains-duplicate-ii/
    > No: 219. Contains Duplicate II
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> m;
        for(int i=0; i<nums.size(); i++) {
            if(m.find(nums[i]) != m.end()) {
                if(i - m[nums[i]] <= k) {
                    return true;
                }
            }
            m[nums[i]] = i;
        }
        return false;
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
#define FUNCTION containsNearbyDuplicate

    vector<int> first;
    int second;
    bool expectAns;

    first = {1,2,3,1};
    second = 3;
    expectAns = true;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {1,0,1,1};
    second = 1;
    expectAns = true;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {1,2,3,1,2,3};
    second = 2;
    expectAns = false;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
