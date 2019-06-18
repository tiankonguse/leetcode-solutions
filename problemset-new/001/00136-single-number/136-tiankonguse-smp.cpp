/*************************************************************************
    > File Name: single-number-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 18:24:49 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(int i=0;i<nums.size();i++){
            ans ^= nums[i];
        }
        return ans;
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
    int expectAns;

    first = {2,2,1};
    expectAns = 1;
    TEST_SMP1(Solution, singleNumber, expectAns, first);

    first = {4,1,2,1,2};
    expectAns = 4;
    TEST_SMP1(Solution, singleNumber, expectAns, first);

    return 0;
}
