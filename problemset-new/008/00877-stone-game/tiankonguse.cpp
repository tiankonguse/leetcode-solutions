/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月10日 17:05:56
    > link: https://leetcode.com/problems/stone-game/
    > No: 877. Stone Game
    > Contest: 95
 ************************************************************************/

#include "../../include/base.h"

class Solution {

    int dp[555][555];
    int sum[555];
    //[left, right)
    int dfs(vector<int>& piles, int left, int right){
        if(dp[left][right] != -1){
            return dp[left][right];
        }
        if(left == right){
            return dp[left][right] = 0;
        }
        int nowSum = sum[right] - sum[left];
        int tryLeft = nowSum - dfs(piles, left+1, right);
        int tryRight = nowSum - dfs(piles, left, right-1);
        return dp[left][right] = max(tryLeft, tryRight);
    }

public:
    bool stoneGame(vector<int>& piles) {
        memset(dp, -1, sizeof(dp));
        sum[0] = 0;
        for(int i=0;i<piles.size();i++){
            sum[i+1] = sum[i] + piles[i];
        }
        int maxNum = dfs(piles, 0, piles.size());
        return maxNum > sum[piles.size()] - maxNum;
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
