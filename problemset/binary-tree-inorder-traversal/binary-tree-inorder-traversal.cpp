/*************************************************************************
    > File Name: binary-tree-inorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月19日 星期日 22时25分31秒
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
    TreeNode(int x=0) : val(x), left(NULL), right(NULL) {}
};
class Solution {
    vector<int>ans;

    void dfs(TreeNode* root){
        if(root == NULL){
            return ;
        }
        
        ans.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

public:
    vector<int> inorderTraversal(TreeNode *root) {
        ans.clear();
        dfs(root);
        return ans;
    }
};

void output(TreeNode* root, int lev = 1){
    if(root == NULL){
        printf("%p\n", root);
        return;
    }

    printf("%p %d\n", root, root->val);
    output(root->left, lev + 1);
    output(root->right, lev + 1);
}

void output(vector<int>&ans){
    printf("ans=");
    for(int i=0;i<ans.size();i++){
        printf("%d ",ans[i]);
    }
    printf("\n");
}

void test(){
    srand(time(NULL));
    Solution work;

    TreeNode list[100];    
    vector<int>ans;

    list[0].val = 1;
    list[1].val = 2;
    list[2].val = 3;

    list[0].right = list + 1;
    list[1].left = list + 2;

    output(list);
    ans = work.inorderTraversal(list);
    output(ans);

}

int main(){
    test();
    return 0;
}
