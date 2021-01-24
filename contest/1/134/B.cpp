/*************************************************************************
    > File Name: coloring-a-border.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 29 00:06:47 2019
    > link:
    > No: 1034. Coloring A Border
    > Contest: https://leetcode.com/contest/weekly-contest-134/problems/coloring-a-border/
 ************************************************************************/

#include "../../include/base.h"


int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
class Solution {
    int n, m, oldColor;
    bool isBorder(vector<vector<int>>& grid, int x, int y) {
        int x0, y0;
        for(int i=0; i<4; i++) {
            x0 = x + dir[i][0];
            y0 = y + dir[i][1];
            if(x0 < 0 || x0 >= n || y0 < 0 || y0 >= m) {
                return true;
            }
            if(grid[x0][y0] > 0 && grid[x0][y0] != oldColor) {
                return true;
            }
        }
        return false;
    }
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int x, int y, int newColor) {
        n = grid.size(), m = grid[0].size();
        queue<pair<int, int>> que;
        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        oldColor = grid[x][y];
        grid[x][y] = isBorder(grid, x, y)?-1:-2;
        que.push({x, y});

        while(!que.empty()) {
            auto p = que.front();
            que.pop();
            x = p.first, y = p.second;
            for(int i=0; i<4; i++) {
                int x0 = x + dir[i][0];
                int y0 = y + dir[i][1];
                if(x0 < 0 || x0 >= n || y0 < 0 || y0 >= m) {
                    continue;
                }
                if(grid[x0][y0] != oldColor) {
                    continue;
                }
                grid[x0][y0] = isBorder(grid, x0, y0)?-1:-2;
                que.push({x0, y0});
            }
        }

        for(int x=0; x<n; x++) {
            for(int y=0; y<m; y++) {
                if(grid[x][y] > 0) {
                    continue;
                }
                grid[x][y] = grid[x][y]== -1?newColor:oldColor;
            }
        }
        return grid;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
*/
int main() {
#define CLASS Solution
#define FUNCTION colorBorder

    vector<vector<int>> first;
    int second;
    int third;
    int four;
    vector<vector<int>> expectAns;

    first = {{{1,1},{1,2}}};
    second = 0;
    third = 0;
    four = 3;
    expectAns = {{3, 3}, {3, 2}};
    TEST_SMP4(Solution, FUNCTION, expectAns, first, second, third, four);


    first = {{1,2,2},{2,3,2}};
    second = 0;
    third = 1;
    four = 3;
    expectAns = {{1, 3, 3}, {2, 3, 3}};
    TEST_SMP4(Solution, FUNCTION, expectAns, first, second, third, four);

    first = {{1,1,1},{1,1,1},{1,1,1}};
    second = 1;
    third = 1;
    four = 2;
    expectAns = {{2, 2, 2}, {2, 1, 2}, {2, 2, 2}};
    TEST_SMP4(Solution, FUNCTION, expectAns, first, second, third, four);
    return 0;
}
