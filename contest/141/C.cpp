/*************************************************************************
    > File Name: shortest-path-in-binary-matrix.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Jun  16 10:24:26 2019
    > link: https://leetcode.com/problems/shortest-path-in-binary-matrix/
    > No: 1091. Shortest Path in Binary Matrix
    > Contest: https://leetcode.com/contest/weekly-contest-141
 ************************************************************************/

#include "../../../include/base.h"

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1) {
            return -1;
        }
        if(n == 1) {
            return 1;
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                grid[i][j] = -grid[i][j];
            }
        }

        queue<pair<int,int>> que;
        int x = 0;
        int y = 0;
        que.push(make_pair(x, y));
        grid[x][y] = 1;

        int dir[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
        while(!que.empty()) {
            auto p = que.front();
            que.pop();

            for(int i=0; i<8; i++) {
                x = p.first + dir[i][0];
                y = p.second + dir[i][1];
                if(x <0 || x >= n || y < 0 || y >= n) {
                    continue;
                }
                if(grid[x][y] != 0) {
                    continue;
                }

                grid[x][y] = grid[p.first][p.second] + 1;

                que.push(make_pair(x, y));
                if(x == n-1 && y == n-1) {
                    return grid[x][y];
                }
            }
        }
        return -1;
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
