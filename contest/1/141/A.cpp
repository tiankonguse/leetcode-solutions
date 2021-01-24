/*************************************************************************
    > File Name: duplicate-zeros.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  16 10:24:26 2019
    > link: https://leetcode.com/problems/duplicate-zeros/
    > No: 1089. Duplicate Zeros
    > Contest: https://leetcode.com/contest/weekly-contest-141
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        vector<int> ans;
        for(auto v : arr) {
            ans.push_back(v);
            if(ans.size() == arr.size()) {
                break;
            }
            if(v == 0) {
                ans.push_back(v);
            }
            if(ans.size() == arr.size()) {
                break;
            }
        }
        arr = ans;
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
