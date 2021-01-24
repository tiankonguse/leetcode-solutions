/*************************************************************************
    > File Name: number-of-submatrices-that-sum-to-target.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  2 10:24:26 2019
    > link: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
    > No: 1074. Number of Submatrices That Sum to Target
    > Contest: https://leetcode.com/contest/weekly-contest-139
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        vector<int> sum(matrix[0].size(), 0);

        int ans = 0;
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<sum.size(); j++) sum[j]=0;

            for(int t=i; t<matrix.size(); t++){
                for(int j=0; j<sum.size(); j++) sum[j]+=matrix[t][j];

                map<int, int> preSet;
                int preSum = 0;
                preSet[preSum] = 1;

                for(int j=0;j<sum.size();j++){
                    preSum += sum[j];
                    int tmp = preSum - target;
                    if(preSet.find(tmp) != preSet.end()){
                        ans += preSet[tmp];
                    }
                    preSet[preSum]++;
                }
            }

        }

        return ans;
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
