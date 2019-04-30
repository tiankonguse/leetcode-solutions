/*************************************************************************
    > File Name: maximum-depth-of-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年03月31日 星期二 23时39分22秒
 ************************************************************************/

#include<iostream>
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
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {

    int max(int a, int b){
        return a> b ? a: b;
    }

public:

    int maxDepth(TreeNode *root) {
        if(root == NULL){
            return 0;
        }else{
            return 1 + max(maxDepth(root->left), maxDepth(root->right));
        }
    }

};

int main(){
    return 0;
}

