/*************************************************************************
    > File Name: pascals-triangle-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 01:12:07 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans;
        ans.resize(rowIndex+1, 1);
        for(int i=1; i<rowIndex; i++) {
            ans[i] = ans[i-1] * (rowIndex - i + 1LL) / i;
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
    int first;
     vector<int>  expectAns;

    first = 1;
    expectAns = {1,1};
    TEST_SMP1(Solution, getRow, expectAns, first);


    first = 2;
    expectAns = {1,2,1};
    TEST_SMP1(Solution, getRow, expectAns, first);

    first = 3;
    expectAns = {1,3,3,1};
    TEST_SMP1(Solution, getRow, expectAns, first);



    first = 4;
    expectAns = {1,4,6,4,1};
    TEST_SMP1(Solution, getRow, expectAns, first);


    first = 5;
    expectAns = {1,5,10,10,5,1};
    TEST_SMP1(Solution, getRow, expectAns, first);

    return 0;
}
