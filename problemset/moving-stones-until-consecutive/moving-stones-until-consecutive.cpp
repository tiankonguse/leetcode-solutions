/*************************************************************************
    > File Name: moving-stones-until-consecutive.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 29 00:06:47 2019
    > link:
    > No: 1033. Moving Stones Until Consecutive
    > Contest: https://leetcode.com/contest/weekly-contest-134/problems/moving-stones-until-consecutive/
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        vector<int> data = {a,b,c};
        sort(data.begin(), data.end());
        a = data[0], b = data[1], c = data[2];

        int minAns = 0;
        if(b - a > 2 && c - b > 2){
            minAns = 2;
        }else if( a + 1 == b && b + 1 == c){
            minAns = 0;
        }else{
            minAns = 1;
        }
        return {minAns, c - a - 2};
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
#define CLASS Solution
#define FUNCTION numMovesStones

    int first;
    int second;
    int third;
    vector<int> expectAns;

    first = 1;
    second = 2;
    third = 5;
    expectAns = {1,2};
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);


    first = 4;
    second = 3;
    third = 2;
    expectAns = {0,0};
    TEST_SMP3(Solution, FUNCTION, expectAns, first, second, third);
    return 0;
}
