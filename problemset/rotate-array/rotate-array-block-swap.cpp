/*************************************************************************
    > File Name: rotate-array-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月31日 19:41:55
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    void swap(vector<int>&nums, int firstStart, int firstEnd, int secondStart, int secondEnd){
        while(firstStart<=firstEnd){
            std::swap(nums[firstStart], nums[secondStart]);
            firstStart++,secondStart++;
        }
    }

    void rotate(vector<int>&nums, int start, int n, int k) {
        if(n <= 1 || k%n == 0) {
            return ;
        }
        k = k % n;

        int right = k;
        int left = n - k;
        if(left >= right) {
            int secondEnd = start + n-1;
            int secondStart = secondEnd - k + 1;
            int firstEnd = secondStart - 1;
            int firstStart =firstEnd - k + 1;
            swap(nums, firstStart, firstEnd, secondStart, secondEnd);
            rotate(nums, start, left, k);
        } else {
            int firstStart = start;
            int firstEnd = firstStart + left - 1;
            int secondStart = firstEnd + 1;
            int secondEnd = secondStart + left - 1;
            swap(nums, firstStart, firstEnd, secondStart, secondEnd);
            rotate(nums, start+left, right, right-left);
        }
    }
public:
    vector<int> rotate(vector<int>& nums, int k) {
        rotate(nums, 0, nums.size(), k);
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
