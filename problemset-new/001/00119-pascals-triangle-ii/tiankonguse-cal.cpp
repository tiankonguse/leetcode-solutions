/*************************************************************************
    > File Name: pascals-triangle-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 25 23:31:49 2019
    > link: https://leetcode.com/problems/pascals-triangle-ii
    > No: 119. Pascal's Triangle II
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

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
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
