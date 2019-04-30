/*************************************************************************
    > File Name: subsets.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 14时49分43秒
 ************************************************************************/

#include<stdio.h>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;

class Solution {

    vector<vector<int> >ans;

    void dfs(int start, int end, vector<int>&now, vector<int>&S){
        if(start == end){
            ans.push_back(now);
            return;
        }
        now.push_back(S[start]);
        dfs(start+1, end, now, S);
        now.pop_back();
        dfs(start+1, end, now, S);
    }

public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<int> now;
        sort(S.begin(), S.end());
        dfs(0,S.size(), now, S);
        return ans;            
    }
};


void test(){
    Solution work;
    vector<int> S;
    S.push_back(1);
    S.push_back(3);
    S.push_back(2);
    vector<vector<int> > ans = work.subsets(S);
    printf("[\n");
    for(int i=0;i<ans.size();i++){
        printf("\t[");
        vector<int>& now = ans[i];
        for(int j=0;j<now.size();j++){
            printf(j?",%d":"%d", now[j]);
        }
        printf("]");
        printf("\n");
        
    }
    printf("]\n");
}

int main(){
    test();
    return 0;
}
