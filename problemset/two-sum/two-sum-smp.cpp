/*************************************************************************
    > File Name: two-sum-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 19:16:38 2019
    > Link: https://leetcode.com/problems/two-sum/
    > No: 1
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> m;
        for(int i=0;i<nums.size();i++){
            int tmp = target - nums[i];
            if(m.find(tmp) != m.end()){
                return {m[tmp], i};
            }
            m[nums[i]] = i;
        }
        return {};
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<int> first;
    int second;
    vector<int> expectAns;

    first = {2, 7, 11, 15};
    second = 9;
    expectAns = {0, 1};
    TEST_SMP2(Solution, twoSum, expectAns, first, second);

    return 0;
}
