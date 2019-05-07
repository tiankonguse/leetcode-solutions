/*************************************************************************
    > File Name: valid-boomerang.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 7日  9:50:42
    > No: 1037. Valid Boomerang
    > Contest: 135
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& p) {
        return ( (p[1][0] - p[0][0]) * (p[2][1] - p[0][1]) ) != ( (p[2][0] - p[0][0]) * (p[1][1] - p[0][1]) );
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
    #define FUNCTION isBoomerang

    vector<vector<int>> first;
    bool expectAns;

    first = {{1,1},{2,3},{3,2}};
    expectAns = true;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {{1,1},{2,2},{3,3}};
    expectAns = false;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
