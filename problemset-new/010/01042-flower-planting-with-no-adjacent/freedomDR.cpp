#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<vector<int>> edge(N, vector<int>());
        for(int i = 0; i < paths.size(); i++) {
            int x = paths[i][0]-1, y = paths[i][1]-1;
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        vector<int> ans(N, 0);
        for(int i = 0; i < N; i++){
            bool used[5] = {};
            for(int v : edge[i]) used[ans[v]] = true;
            for(int t = 1; t < 5; t++) {
                if(used[t] == false) ans[i] = t;
            }
        }
        return ans;
    }
};

int main()
{
    return 0;
}
