/*************************************************************************
    > File Name: D.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Mar 13 22:45:30 2019
    > contest: https://leetcode.com/contest/weekly-contest-130
 ************************************************************************/

#include "../../include/base.h"

int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
class Solution {
        int n ;
        int m;

    void dfs(vector<vector<int>>& A, int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= m){
            return ;
        }
        if(A[x][y] != 1){
            return;
        }

        A[x][y] = 2;
        for(int i=0;i<4;i++){
            dfs(A, x+dir[i][0], y+dir[i][1]);
        }
    }

public:
    int numEnclaves(vector<vector<int>>& A) {
         n = A.size();
         m = A[0].size();

        for(int i=0;i<n;i++){
            dfs(A, i, 0);
            dfs(A, i, m-1);
        }
        for(int i=0;i<m;i++){
            dfs(A, 0, i);
            dfs(A, n-1, i);
        }

        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(A[i][j] ==  1){
                    ans++;
                }
            }
        }
        return ans;
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
    vector<vector<int>> first;
    int expectAns;

    first =  {{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}};
    expectAns = 3;
    TEST_SMP1(Solution, numEnclaves, expectAns, first);

    first = {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}};
    expectAns = 0;
    TEST_SMP1(Solution, numEnclaves, expectAns, first);

    return 0;
}
