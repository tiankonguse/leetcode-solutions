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
    string base;
    int len;
    struct Point{
        int x,y,pos,dir;
        Point(){
            x=y=pos=dir=0;
        }
    };
    // 0 => up
    // 1 => right
    // 2 => down
    // 3 => left
    // L => turn left
    // G => turn right
    void next(Point& now){
        int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        //skip turn
        while(base[now.pos] != 'G'){
            if(base[now.pos] == 'L'){
                now.dir = (now.dir + 3)%4;
            }else{
                now.dir = (now.dir + 1)%4;
            }
            now.pos = (now.pos + 1)%len;
        }
        now.pos = (now.pos + 1)%len;
        //begin move
        now.x += dir[now.dir][0];
        now.y += dir[now.dir][1];
    }
public:
    bool isRobotBounded(string str) {
        base = str;
        len = str.length();

        bool haveMove = false;
        for(int i=0;i<len;i++){
            if(str[i] == 'G'){
                haveMove = true;
                break;
            }
        }
        if(!haveMove){
            return true;
        }

        Point fast,slow;
        int step = 0;
        while(step < len*10){
            next(slow);
            next(fast);
            next(fast);
            step++;
            //printf("slow: x=%d y=%d dir=%d pos=%d\n", slow.x, slow.y, slow.dir, slow.pos);
            //printf("fast: x=%d y=%d dir=%d pos=%d\n", fast.x, fast.y, fast.dir, fast.pos);
            if(fast.x == slow.x && fast.y == slow.y){
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
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
    #define CLASS Solution
    #define FUNCTION isRobotBounded

    string first;
    bool expectAns;

    first = "GGLLGG";
    expectAns = true;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    return 0;
}
