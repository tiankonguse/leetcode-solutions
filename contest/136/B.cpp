/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun May 12 10:29:17 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    map<int, set<int>> m;
    vector<int> ans;

    void dfs(int i){
        if(ans[i] != -1){
            return;
        }

        set<int> node;
        for(auto it = m[i].begin(); it != m[i].end(); it++){
            if(ans[*it] != -1){
                node.insert(ans[*it]);
            }
        }
        int color = 1;
        while(color < 5){
            if(node.find(color) == node.end()){
                break;
            }
            color++;
        }
        if(color == 5){
            printf("error\n");
            return ;
        }
        ans[i] = color;
        for(auto it = m[i].begin(); it != m[i].end(); it++){
            dfs(*it);
        }
    }

public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        ans.resize(N, -1);
        for(int i=0;i<paths.size();i++){
            int x = paths[i][0]-1;
            int y = paths[i][1]-1;
            m[x].insert(y);
            m[y].insert(x);
        }
        for(int i=0;i<ans.size();i++){
            if(ans[i] == -1){
                dfs(i);
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
    #define FUNCTION gardenNoAdj

    int first;
    vector<vector<int>> second;
    vector<int> expectAns;

    first = 3;
    second = {{1,2},{2,3},{3,1}};
    expectAns = {1,2,3};
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = 4;
    second = {{1,2},{3,4}};
    expectAns = {1,2,1,2};
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);


    first = 4;
    second = {{1,2},{2,3},{3,4},{4,1},{1,3},{2,4}};
    expectAns = {1,2,3,4};
    TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
