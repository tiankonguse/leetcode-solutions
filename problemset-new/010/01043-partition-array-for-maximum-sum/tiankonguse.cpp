/*************************************************************************
    > File Name: partition-array-for-maximum-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 12 10:29:17 2019
    > link: https://leetcode.com/problems/partition-array-for-maximum-sum/
    > No: 1043. Partition Array for Maximum Sum
    > Contest: https://leetcode.com/contest/weekly-contest-136
 ************************************************************************/

#include "../../include/base.h"

typedef long long LL;
class Solution {
    vector<LL> dp;
    vector<int> A;
    int K;

    LL dfs(int pos){
        if(pos <0)return 0;
        if(dp[pos] != -1){
            return dp[pos];
        }
        LL maxVal = A[pos];
        LL ans = 0;
        int OldPos = pos;

        for(int i=1;i<=K && pos >= 0;i++){
            maxVal = max(maxVal, (LL)A[pos]);
            ans = max(maxVal*i + dfs(pos-1), ans);
            pos--;
        }
        return dp[OldPos] = ans;
    }

public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        dp.resize(555,-1);
        this->A = A;
        this->K = K;
        return dfs(A.size()-1);
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
    #define FUNCTION maxSumAfterPartitioning

    vector<int> first;
    int second;
    int expectAns;

    first = {1,15,7,9,2,5,10};
    second = 3;
    expectAns = 84;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
