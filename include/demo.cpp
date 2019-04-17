/*************************************************************************
    > File Name: add-binary.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > link: https://leetcode.com/problems/add-binary/
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int smallestRepunitDivByK(int K) {
        int sum = 0;
        set<int> have;
        for(int i=1;;i++){
            sum = (sum * 10 + 1)%K;
            if(sum == 0){
                return i;
            }
            if(have.find(sum) != have.end()){
                return -1;
            }
            have.insert(sum);
        }
        return -1;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});

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
