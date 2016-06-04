/*************************************************************************
    > File Name: same-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年03月31日 星期二 23时45分16秒
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

public:

    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p == NULL && q == NULL){
            return true;
        }else if(p == NULL || q == NULL){
            return false;
        }else{
            return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        

    }

};


int main(){
    return 0;
}
