/*************************************************************************
    > File Name: 01-matrix.cpp
    > Author: tiankongever
    > Mail: i@tiankongever.com
    > Created Time: Tue Apr  9 22:42:47 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    struct Node{
        Node(int _x=0, int _y=0, int _v=0){
            x=_x,y=_y,v=_v;
        }
        int x,y,v;
    };
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0)return matrix;
        int n = matrix.size();
        int m = matrix[0].size();

        queue<Node> que;
        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                matrix[i][j] = -matrix[i][j];
                if(matrix[i][j] == 0){
                    que.push(Node(i,j, 0));
                }
            }
        }

        int sr, sc;
        while(!que.empty()){
            auto p = que.front();
            que.pop();
            for(int i=0; i<4; i++) {
                sr = p.x + dir[i][0];
                sc = p.y + dir[i][1];
                if(sr < 0 || sr >= n || sc < 0 || sc >= m)
                    continue;
                if(matrix[sr][sc] != -1)
                    continue;
                matrix[sr][sc] = p.v+1;
                que.push(Node(sr, sc, p.v+1));
            }
        }
        return matrix;
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
    vector<vector<int>> expectAns;

    first = {{0,0,0},{0,1,0},{0,0,0}};
    expectAns = {{0,0,0},{0,1,0},{0,0,0}};
    TEST_SMP1(Solution, updateMatrix, expectAns, first);

    first = {{0,0,0},{0,1,0},{1,1,1}};
    expectAns = {{0,0,0},{0,1,0},{1,2,1}};
    TEST_SMP1(Solution, updateMatrix, expectAns, first);

    return 0;
}
