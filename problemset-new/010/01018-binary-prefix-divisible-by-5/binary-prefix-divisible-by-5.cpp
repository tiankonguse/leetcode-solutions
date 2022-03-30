/*************************************************************************
    > File Name: binary-prefix-divisible-by-5.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > contest: https://leetcode.com/contest/weekly-contest-130
    > link: https://leetcode.com/problems/binary-prefix-divisible-by-5/
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        vector<bool> ans;
        int now = 0;

        for(int i=0; i<A.size(); i++) {
            now = (now * 2 + A[i])%5;
            if(now ==0) {
                ans.push_back(1);
            } else {
                ans.push_back(0);
            }

        }
        return ans;
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
    vector<bool> expectAns;

    first = {0,1,1};
    expectAns = {true,false,false};
    TEST_SMP1(Solution, prefixesDivBy5, expectAns, first);

    first = {0,1,1,1,1,1};
    expectAns = {true,false,false,false,true,false};
    TEST_SMP1(Solution, prefixesDivBy5, expectAns, first);

    return 0;
}
