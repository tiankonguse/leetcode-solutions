/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 21 10:12:57 2019
    > Contest:
    > Title:
    > Link:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int m[111][111];
    int N, K;

    int dp0(int n, int k, vector<vector<int>>& costs) {
        if(n== -1 || k == -1)
            return 0;
        if(m[n][k] != -1) {
            return m[n][k];
        }
        if(k == 0) {
            return m[n][k] = costs[n][1] + dp0(n-1, k, costs);
        }
        if(n + 1 == k) {
            return m[n][k] = costs[n][0] + dp0(n-1, k-1, costs);
        }
        return m[n][k] = min(costs[n][0] + dp0(n-1, k-1, costs),  costs[n][1] + dp0(n-1, k, costs));

    }

public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        memset(m, -1, sizeof(m));
        N = costs.size();
        K = N/2;
        return dp0(N-1, K, costs);
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<vector<int>> first;
    int expectAns;

    first = {{10,20},{30,200},{400,50},{30,20}};
    expectAns = 110;
    TEST_SMP1(Solution, twoCitySchedCost, expectAns, first);

    return 0;
}
