/*************************************************************************
    > File Name: uncrossed-lines.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 29 00:06:47 2019
    > link:
    > No: 1035. Uncrossed Lines
    > Contest: https://leetcode.com/contest/weekly-contest-134/problems/uncrossed-lines/
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int dp[555][555];
        memset(dp, -1, sizeof(dp));
        memset(dp[0], 0, sizeof(dp[0]));
        for(int i=1; i<=A.size(); i++) {
            dp[i][0] = 0;
            for(int j=1; j<=B.size(); j++) {
                if(A[i-1] == B[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        return dp[A.size()][B.size()];
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
#define CLASS Solution
#define FUNCTION maxUncrossedLines

    vector<int> first;
    vector<int> second;
    int expectAns;

    first = {1,4,2};
    second = {1,2,4};
    expectAns = 2;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {2,5,1,2,5};
    second = {10,5,2,1,5,2};
    expectAns = 3;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    first = {1,3,7,1,7,5};
    second = {1,9,2,5,1};
    expectAns = 2;
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
