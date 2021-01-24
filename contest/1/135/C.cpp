/*************************************************************************
    > File Name: minimum-score-triangulation-of-polygon.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月 7日  9:50:42
    > No: 1039. Minimum Score Triangulation of Polygon
    > Contest: 135
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int dp[55][55];
    int dfs(vector<int>& A, int from, int to) {
        if(from + 2 > to) {
            return 0;
        }
        if(dp[from][to]) {
            return dp[from][to];
        }
        for(int i= from + 1; i < to ; i++) {
            int tmp = A[from] * A[i] * A[to];
            tmp += dfs(A, from, i);
            tmp += dfs(A, i, to);
            if(dp[from][to]  == 0) {
                dp[from][to]  = tmp;
            } else {
                dp[from][to] = min(tmp, dp[from][to]);
            }
        }
        return dp[from][to];
    }
public:
    int minScoreTriangulation(vector<int>& A) {
        memset(dp, 0, sizeof(dp));
        return dfs(A, 0, A.size()-1);
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
#define FUNCTION minScoreTriangulation

    vector<int> first;
    int expectAns;

    first = {1,2,3};
    expectAns = 6;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {3,7,4,5};
    expectAns = 144;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);

    first = {1,3,1,4,1,5};
    expectAns = 13;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);


    return 0;
}
