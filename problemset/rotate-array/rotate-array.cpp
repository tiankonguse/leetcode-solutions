/*************************************************************************
    > File Name: rotate-array-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月31日 19:41:55
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    void rotate(vector<int>&nums){
        int n = nums.size();
        int lastVal = nums[n-1];
        for(int i=n-1;i>0;i--){
            nums[i] = nums[i-1];
        }
        nums[0] = lastVal;
    }

public:
    vector<int> rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        while(k>0){
            rotate(nums);
            k--;
        }
        return nums;
    }
};

/*
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


    first = {1,2,3,4,5,6,7};
    second = 1;
    expectAns = {7,1,2,3,4,5,6};
    TEST_SMP2(Solution, rotate, expectAns, first, second);


    first = {1,2,3,4,5,6,7};
    second = 2;
    expectAns = {6,7,1,2,3,4,5};
    TEST_SMP2(Solution, rotate, expectAns, first, second);


    first = {1,2,3,4,5,6,7};
    second = 3;
    expectAns = {5,6,7,1,2,3,4};
    TEST_SMP2(Solution, rotate, expectAns, first, second);


    first = {-1,-100,3,99};
    second = 2;
    expectAns = {3,99,-1,-100};
    TEST_SMP2(Solution, rotate, expectAns, first, second);


    return 0;
}
