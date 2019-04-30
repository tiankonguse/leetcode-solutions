/*************************************************************************
  > File Name: number-of-islands.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com
  > Created Time: 2015年04月22日 20:35:25
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

class Solution {
    int x,y;
    int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    void dfs(int i, int j, vector<vector<char> >&grid){
        if(i<0 || j<0 || i >= x || j >= y){
            return;
        }
        if(grid[i][j] != '1'){
            return;
        }
        grid[i][j] = '0';
        for(int k=0;k<4;k++){
            dfs(i+dir[k][0], j+dir[k][1], grid);
        }
    }
public:
    int numIslands(vector<vector<char>> &grid) {
        if(grid.size() == 0 || grid[0].size() == 0){
            return 0;
        }
        x = grid.size();
        y = grid[0].size();
        int ans = 0;
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(grid[i][j] == '1'){
                    dfs(i,j, grid);
                    ans = ans + 1;
                }
            }
        }
        return ans;
    }
};

void bornData(vector<string>&data, vector<vector<char> >&grid){
    grid.clear();
    for(int i=0;i<data.size();i++){
        string& s = data[i];
        vector<char>vec(s.begin(), s.end());
        grid.push_back(vec);
    }
}

void output(vector<vector<char> >&grid){
    for(int i=0;i<grid.size();i++){
        vector<char>& vec = grid[i];
        for(int j=0;j<vec.size();j++){
            printf("%c", vec[j]);
        }
        printf("\n");
    }
}

void test(){
    Solution work;
    vector<vector<char>> grid;
    int ans;
    vector<string> data;

    data = {
        "11110",
        "11010",
        "11000",
        "00000"
    };
    bornData(data, grid);
    output(grid);
    ans = work.numIslands(grid);
    printf("ans=%d\n",ans);

    data = {
        "11000",
        "11000",
        "00100",
        "00011"
    };
    bornData(data, grid);
    output(grid);
    ans = work.numIslands(grid);
    printf("ans=%d\n",ans);

}

int main() {

    test();

    return 0;
}
