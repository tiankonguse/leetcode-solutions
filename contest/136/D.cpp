/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 12 10:29:17 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"



class Solution {

public:
    string longestDupSubstring(string str) {
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());

    // dir : up, right, down, right
    //int dir[4][2] = {{0,1}},{1,0},{0,-1,{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION longestDupSubstring

    string first;
    string expectAns;

    first = "banana";
    expectAns = "ana";
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
