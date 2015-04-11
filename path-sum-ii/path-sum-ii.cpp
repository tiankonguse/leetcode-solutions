/*************************************************************************
    > File Name: path-sum-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月09日 星期四 00时47分32秒
 ************************************************************************/

#include<stdio.h>
#include<vector>
using namespace std;

/**
 * Definition for binary tree
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution {
    void dfs(TreeNode* root, int sum, int all){

        now.push_back(root->val);
        sum += root->val;

        if(root->left == NULL && root->right == NULL){
            // leaf
            if(sum == all){
                ans.push_back(now);
            }
        }else if(root->left == NULL && root->right != NULL){
            // right branch
            dfs(root->right, sum, all);
        }else if(root->left != NULL && root->right == NULL){
            // left branch
            dfs(root->left, sum, all);
        }else if(root->left != NULL && root->right != NULL){
            // node
            dfs(root->left, sum, all);
            dfs(root->right, sum, all);
        }
        now.pop_back();
    }
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        now.clear();
        ans.clear();

        if(root != NULL){
            dfs(root, 0, sum);
        }

        return ans;
    }
private:
    vector<int> now;
    vector<vector<int> >ans;
};

void test(){
    Solution work;

}

int main(){
    test();
    return 0;
}
