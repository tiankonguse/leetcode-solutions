/*************************************************************************
  > File Name: binary-tree-right-side-view.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月22日 10:13:41
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


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x = 0) : val(x), left(NULL), right(NULL) {}
};
class Solution {
    vector<int>ans;
    void init(int lev){
        if(ans.size() == lev){
            ans.push_back(0);
        }
    }
    void dfs(TreeNode* root, int lev = 0){
        if(root == NULL){
            return ;
        }
        init(lev);
        ans[lev]=root->val;
        dfs(root->left, lev + 1);
        dfs(root->right, lev + 1);
    }
public:
    vector<int > rightSideView(TreeNode *root) {
        ans.clear();
        dfs(root);
        return ans;
    }
};

void output(vector<int> ans){
    printf("    ans = %d ", ans.size());
    for(int i=0;i<ans.size();i++){
        printf("%d ", ans[i]);
    }
    printf("\n");
}

void test(){
    Solution work;
    TreeNode list[100];
    vector<int>ans;

    list[0].val = 3;    
    list[1].val = 9;    
    list[2].val = 20;    
    list[3].val = 15;    
    list[4].val = 7; 

    list[0].left = list + 1;
    list[0].right = list + 2;
    list[2].left = list + 3;
    list[2].right = list + 4;

    ans = work.rightSideView(list);
    output(ans);



    

}


int main() {
    test();
    return 0;
}
