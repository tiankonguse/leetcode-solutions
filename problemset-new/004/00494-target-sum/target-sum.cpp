/*************************************************************************
    > File Name: target-sum.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr  4 00:12:50 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    map<pair<int, int>, int> m;
    int n;
    int S;

    int dfs(int pos, int sum, vector<int>& nums){
        if(pos == n){
            return sum == S?1:0;
        }
        auto p = make_pair(pos, sum);
        if(m.find(p) != m.end()){
            return m[p];
        }
        int ans = 0;
        ans += dfs(pos+1, sum + nums[pos], nums);
        ans += dfs(pos+1, sum - nums[pos], nums);
        return m[p] = ans;
    }

public:
    int findTargetSumWays(vector<int>& nums, int S) {
        n = nums.size();
        this->S = S;
        return dfs(0,0, nums);
    }
};
/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    vector<int> first;
    int second;
    int expectAns;

    first = {1, 1, 1, 1, 1};
    second = 3;
    expectAns = 5;
    TEST_SMP2(Solution, findTargetSumWays, expectAns, first, second);


    return 0;
}
