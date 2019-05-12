/*************************************************************************
    > File Name: robot-bounded-in-circle.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 12 10:29:17 2019
    > link: https://leetcode.com/problems/robot-bounded-in-circle/
    > No: 1041. Robot Bounded In Circle
    > Contest: https://leetcode.com/contest/weekly-contest-136
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool isRobotBounded(string str) {
        int DIR[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        int x = 0, y = 0, dir = 0;
        for(int i=0; i<str.length(); i++) {
            if(str[i] == 'G') {
                x += DIR[dir][0];
                y += DIR[dir][1];
            } else if(str[i] == 'L') {
                dir = (dir + 3)%4;
            } else {
                dir = (dir + 1)%4;
            }
        }
        if(x == 0 && y == 0) {
            return true;
        }
        return dir != 0;
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
