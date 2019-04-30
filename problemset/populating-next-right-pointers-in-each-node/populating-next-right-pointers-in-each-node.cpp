/*************************************************************************
    > File Name: populating-next-right-pointers-in-each-node.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月05日 星期日 12时39分07秒
 ************************************************************************/

#include<stdio.h>

/**
 * Definition for binary tree with next pointer.
 */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(){
        this->val = -1;
        this->left = NULL;
        this->right = NULL;
        this->next = NULL;
    }
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
    void init(int x,TreeLinkNode* left, TreeLinkNode* right){
        this->val = x;
        this->left = left;
        this->right = right;
        this->next = NULL;
    }
};
class Solution {

    void merge(TreeLinkNode* left, TreeLinkNode* right){
        while(left != NULL && right != NULL){
            left->next = right;
            left = left->right;
            right = right->left;
        }
    }

public:
    void connect(TreeLinkNode *root) {
        if(root == NULL){
            return ;
        }
        connect(root->left);
        connect(root->right);
        merge(root->left, root->right);
    }
};


void output(TreeLinkNode* root){
    if(root == NULL){
        return ;
    }
    printf("val=%d %p left=%p right=%p next=%p\n", root->val, root, root->left, root->right, root->next);
    output(root->left);
    output(root->right);
}

void test(){
    TreeLinkNode root[100];
    for(int i=1;i<=7;i++){
        root[i].init(i, root + i*2, root + i*2+1);
    }
    for(int i=4;i<=7;i++){
        root[i].left = NULL;
        root[i].right = NULL;
    }
    output(root + 1);
    printf("\n");
    Solution work;
    work.connect(root+1);
    
    output(root + 1);
}

int main(){
    test();
    return 0;
}
