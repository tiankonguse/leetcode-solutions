/*************************************************************************
    > File Name: jump-game-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月18日 19:19:42
    > link: https://leetcode.com/problems/jump-game-ii/
    > No: 45. Jump Game II
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
    vector<int> f;
    int maxPos;
    void next(vector<int>& nums, int nowPos) {
        while(nowPos + nums[nowPos] >= maxPos && maxPos  < f.size()) {
            f[maxPos] = f[nowPos] + 1;
            maxPos++;
        }
    }
public:
    int jump(vector<int>& nums) {
        f.resize(nums.size(), -1);
        maxPos = 1;
        f[0] = 0;
        for(int i=0; i<nums.size(); i++) {
            next(nums, i);
        }
        return f[nums.size()-1];
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
#define FUNCTION jump

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
