/*************************************************************************
    > File Name: last-stone-weight.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 19 10:27:35 2019
    > link: https://leetcode.com/problems/last-stone-weight/
    > No: 1046. Last Stone Weight
    > Contest: https://leetcode.com/contest/weekly-contest-137
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> que(stones.begin(), stones.end());
        while(que.size() >= 2) {
            int y = que.top();
            que.pop();
            int x = que.top();
            que.pop();
            if(y != x) {
                que.push(y-x);
            }
        }
        if(que.size() == 0) {
            return 0;
        }
        return que.top();
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
#define FUNCTION lastStoneWeight

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
