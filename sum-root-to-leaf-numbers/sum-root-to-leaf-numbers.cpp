/*************************************************************************
    > File Name: sum-root-to-leaf-numbers.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月06日 星期一 19时38分35秒
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for binary tree
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(){
        left = NULL;
        right = NULL;
    }
};

class Solution {

    int sum;
    void dfs(TreeNode*root, int now){
        if(root == NULL){
            // empty tree
            return;
        }
        if(root->left == NULL && root->right == NULL){
            // leaf
            sum += now*10 + root->val;
        }else{
            // now leaf
            dfs(root->left, now*10+root->val);
            dfs(root->right, now*10+root->val);
        }
    }
public:
    int sumNumbers(TreeNode *root) {
        sum = 0;
        dfs(root, 0);
        return sum;
    }
};

void test(){
    
    TreeNode list[10];
    Solution work;
    int ans;

    for(int i=0;i<10;i++){
        list[i].val = i;
    }

    ans = work.sumNumbers(NULL);
    printf("%d\n", ans);
    printf("\n");

    
    ans = work.sumNumbers(list + 1);
    printf("%d\n", ans);
    printf("\n");



    for(int i=1;i<=1;i++){
        list[i].left = list + i * 2; 
        list[i].right = list + i * 2 + 1;
    }
    ans = work.sumNumbers(list+1);
    printf("%d\n",ans);


    

}

int main(){
    test();
    return 0;
}
