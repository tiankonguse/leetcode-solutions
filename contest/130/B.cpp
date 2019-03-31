/*************************************************************************
    > File Name: B.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > contest: https://leetcode.com/contest/weekly-contest-130
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    string baseNeg2(int N) {
        if(N == 0){
            return "0";
        }
        string ans;
        int pre = 0;
        int bit = 0;

        while(N>0 || pre >0){
            int sum = N%2 + pre;
            if(sum == 0){
                ans.push_back('0');
            }else if(sum == 1){
                pre = bit%2;
                ans.push_back('1');
            }else if(sum == 2){
                pre = 1;
                ans.push_back('0');
            }
            bit++;
            N = N/2;
        }

        std::reverse(ans.begin(), ans.end());
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
    int first;
    string expectAns;

    first = 0;
    expectAns = "0";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);


    first = 1;
    expectAns = "1";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);

    first = 2;
    expectAns = "110";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);

    first = 3;
    expectAns = "111";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);


    first = 4;
    expectAns = "100";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);


    first = 5;
    expectAns = "101";
    TEST_SMP1(Solution, baseNeg2, expectAns, first);

    return 0;
}
