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
    string base;
    int len;
    struct Point {
        int x,y,pos,dir;
        Point() {
            x=y=pos=dir=0;
        }
    };
    void next(Point& now) {
        int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        //skip turn
        while(base[now.pos] != 'G') {
            if(base[now.pos] == 'L') {
                now.dir = (now.dir + 3)%4;
            } else {
                now.dir = (now.dir + 1)%4;
            }
            now.pos = (now.pos + 1)%len;
        }
        //begin move
        now.x += dir[now.dir][0];
        now.y += dir[now.dir][1];
        now.pos = (now.pos + 1)%len;
    }
public:
    bool isRobotBounded(string str) {
        base = str;
        len = str.length();

        bool haveMove = false;
        for(int i=0; i<len; i++) {
            if(str[i] == 'G') {
                haveMove = true;
                break;
            }
        }
        if(!haveMove) {
            return true;
        }

        Point fast,slow;
        int step = 0;
        while(step < len*10) {
            next(slow),next(fast), next(fast);
            step++;
            if(fast.x == slow.x && fast.y == slow.y) {
                break;
            }
        }
        return fast.x == slow.x && fast.y == slow.y;
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
