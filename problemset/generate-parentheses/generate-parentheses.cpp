/*************************************************************************
    > File Name: generate-parentheses.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月16日 星期四 23时59分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<time.h>
using namespace std;


class Solution {
    vector<string>ans;
    string str;
    int maxLev;
    void dfs(int lev, int sta, int pos){
        if(lev == maxLev && sta == 0){
            ans.push_back(str);
            return;
        }

        if(lev < maxLev){
            str[pos] = '(';
            dfs(lev+1, sta+1, pos+1);
        }

        if(sta > 0){
            str[pos] = ')';
            dfs(lev, sta-1, pos+1);
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        ans.clear();
        if(n == 0){
            return ans;
        }
        maxLev = n;
        str.resize(n*2, 0);

        dfs(0, 0, 0);

        return ans;
    }
};

void output(vector<string>&ans){
    printf("ans size = %d\n",(int)ans.size());
    for(int i=0;i<ans.size();i++){
        printf("\t%s\n",ans[i].c_str());
    }
    printf("\n");
}

void test(){
    srand(time(NULL));
    Solution work;

    vector<string>ans;
    int n;

    n=0;
    ans = work.generateParenthesis(n);
    printf("n=%d\n", n);
    output(ans);

    n=1;
    ans = work.generateParenthesis(n);
    printf("n=%d\n", n);
    output(ans);

    n=2;
    ans = work.generateParenthesis(n);
    printf("n=%d\n", n);
    output(ans);

    n=3;
    ans = work.generateParenthesis(n);
    printf("n=%d\n", n);
    output(ans);

    n=5;
    ans = work.generateParenthesis(n);
    printf("n=%d\n", n);
    output(ans);

}

int main(){
    test();
    return 0;
}
