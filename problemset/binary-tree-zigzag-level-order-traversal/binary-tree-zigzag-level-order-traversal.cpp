/*************************************************************************
  > File Name: binary-tree-zigzag-level-order-traversal.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月22日 10:23:36
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
    vector<vector<int> >ans;
    void init(int lev){
        if(ans.size() == lev){
            vector<int> line;
            ans.push_back(line);
        }
    }
    void dfs(int lev, TreeNode* root){
        if(root == NULL){
            return ;
        }

        init(lev);
        ans[lev].push_back(root->val);

        dfs(lev + 1, root->left);
        dfs(lev + 1, root->right);
    }
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        ans.clear();
        dfs(0, root);
        int size = ans.size();
        for(int i=1;i<size;i+=2){
            reverse(ans[i].begin(), ans[i].end());
        }
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

void output(vector<vector<int> >ans){
    printf("ans = %d\n", ans.size());
    for(int i=0;i<ans.size();i++){
        output(ans[i]);
    }
}

void test(){
    Solution work;
    TreeNode list[100];
    vector<vector<int> >ans;

    list[0].val = 3;    
    list[1].val = 9;    
    list[2].val = 20;    
    list[3].val = 15;    
    list[4].val = 7; 

    list[0].left = list + 1;
    list[0].right = list + 2;
    list[2].left = list + 3;
    list[2].right = list + 4;

    ans = work.zigzagLevelOrder(list);
    output(ans);


    list[0].val = 1;    
    list[1].val = 2;    
    list[2].val = 3;    
    list[3].val = 4;    
    list[4].val = 5;

    

}

int main() {
    test();
    return 0;
}
