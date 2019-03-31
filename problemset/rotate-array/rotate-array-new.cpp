/*************************************************************************
    > File Name: rotate-array-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年03月31日 19:41:55
 ************************************************************************/

#include "../../include/base.h"

class Solution {
     void swap(vector<int>&list, int n, int k){

     }
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n <= 1 || k%n == 0){
            return ;
        }
        k = k % n;
        swap(nums, n,n - k);
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
    int first;
    int expectAns;

    first = 113;
    expectAns = 112;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 2;
    expectAns = -1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    return 0;
}
