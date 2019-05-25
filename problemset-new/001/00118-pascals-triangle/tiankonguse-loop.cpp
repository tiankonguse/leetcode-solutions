/*************************************************************************
    > File Name: pascals-triangle.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sat May 25 23:19:10 2019
    > link: https://leetcode.com/problems/pascals-triangle/
    > No: 118. Pascal's Triangle
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        if(numRows == 0)
            return ans;

        vector<int> row;
        row.push_back(1);
        ans.push_back(row);
        for(int i=1; i<numRows; i++) {
            vector<int> row;
            row.push_back(1);

            vector<int>& lastRow = ans[ans.size() - 1];
            for(int i=1; i<lastRow.size(); i++) {
                row.push_back(lastRow[i-1] + lastRow[i]);
            }
            row.push_back(1);
            ans.push_back(row);
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
