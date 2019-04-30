/*************************************************************************
    > File Name: contains-duplicate.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 18:18:11 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> s;
        for(int i=0;i<nums.size();i++){
            if(s.find(nums[i]) != s.end()){
                return true;
            }
            s.insert(nums[i]);
        }
        return false;
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
    bool expectAns;

    first = {1,2,3,1};
    expectAns = true;
    TEST_SMP1(Solution, containsDuplicate, expectAns, first);

    first = {1,2,3,4};
    expectAns = false;
    TEST_SMP1(Solution, containsDuplicate, expectAns, first);

    first = {1,1,1,3,3,4,3,2,4,2};
    expectAns = true;
    TEST_SMP1(Solution, containsDuplicate, expectAns, first);

    return 0;
}
