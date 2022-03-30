/*************************************************************************
    > File Name: profitable-schemes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月10日 17:05:56
    > link: https://leetcode.com/problems/profitable-schemes/
    > No: 879. Profitable Schemes
    > Contest: 95
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int dp[111][111][111];
    vector<int> group;
    vector<int> profit;
    long long mod = 1000000007;

    // g => people
    // p => min profit
    // n => profit[0, n)
    long long dfs(int g, int p, int n){
        if(dp[g][p][n] != -1){
            return dp[g][p][n];
        }
        if(g == 0){
            return dp[g][p][n] = 0;
        }
        if(n == 0){
            return dp[g][p][n] = 0;
        }
        long long ans = 0;

        //not choise last profit
        ans += dfs(g, p, n-1);

        //choise last profit
        if(group[n-1] <= g){
            int newP = max(0, p - profit[n-1]);
            if(newP == 0){
                ans++;
            }
            ans += dfs(g - group[n-1], newP, n-1);
        }

        return dp[g][p][n] = ans % mod;
    }
public:
    int profitableSchemes(int g, int p, vector<int>& group, vector<int>& profit) {
        memset(dp, -1, sizeof(dp));
        this->group = group;
        this->profit = profit;
        return dfs(g, p, profit.size());
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
