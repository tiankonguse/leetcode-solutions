/*************************************************************************
    > File Name: 1051-height-checker.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 26 10:08:23 2019
    > link: https://leetcode.com/problems/height-checker
    > No: 1051. Height Checker
    > Contest: https://leetcode.com/contest/weekly-contest-138/problems/height-checker/
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> newheights = heights;
        sort(newheights.begin(),newheights.end());
        int ans = 0;
        for(int i=0; i<newheights.size(); i++) {
            if(newheights[i] != heights[i])
                ans++;
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
