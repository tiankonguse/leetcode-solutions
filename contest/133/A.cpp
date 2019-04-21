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
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<int>> ans;

        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        int m[101][101];
        memset(m, -1, sizeof(m));
        queue<pair<int, int>> que;

        ans.push_back({r0, c0});
        m[r0][c0] = 0;
        que.push(make_pair(r0, c0));

        while(!que.empty()) {
            auto p = que.front();
            que.pop();

            for(int i=0; i<4; i++) {
                r0 = p.first + dir[i][0];
                c0 = p.second + dir[i][1];
                if(r0 <0 || r0 >= R || c0 <0 || c0 >= C)
                    continue;
                if(m[r0][c0] != -1)
                    continue;

                ans.push_back({r0, c0});
                m[r0][c0] = m[p.first][p.second] + 1;
                que.push(make_pair(r0, c0));
            }
        }
        return ans;
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
    int param1;
    int param2;
    int param3;
    int param4;
    vector<vector<int>> expectAns;

    param1 = 1;
    param2 = 2;
    param3 = 0;
    param4 = 0;
    expectAns = {{0,0},{0,1}};
    TEST_SMP4(Solution, allCellsDistOrder, expectAns, param1,param2,param3,param4);


    param1 = 2;
    param2 = 2;
    param3 = 0;
    param4 = 1;
    expectAns = {{0,1},{0,0},{1,1},{1,0}};
    TEST_SMP4(Solution, allCellsDistOrder, expectAns, param1,param2,param3,param4);

    param1 = 2;
    param2 = 3;
    param3 = 1;
    param4 = 2;
    expectAns = {{1,2},{0,2},{1,1},{0,1},{1,0},{0,0}};
    TEST_SMP4(Solution, allCellsDistOrder, expectAns, param1,param2,param3,param4);

    return 0;
}
