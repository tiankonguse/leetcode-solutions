/*************************************************************************
    > File Name: balanced-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: 2015年04月22日 星期三 00时17分32秒
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
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x=0) : val(x), left(NULL), right(NULL) {}
};
class Solution {
    bool checkHeightBalanced(TreeNode* root, int& height){
        if(root == NULL){
            height = 0;
            return true;
        }

        int l = 0,r = 0;
        if(!checkHeightBalanced(root->left, l)){
            return false;
        }

        if(!checkHeightBalanced(root->right, r)){
            return false;
        }

        if(abs(l - r) <= 1){
            height = max(l, r) + 1;
            return true;
        }

        return false;
    }

    int abs(int a){
        if(a<0){
            return -a;
        }else{
            return a;
        }
    }

    int max(int a, int b){
        if(a < b){
            return b;
        }else{
            return a;
        }
    }

public:
    bool isBalanced(TreeNode *root) {
        int ans;
        int h;
        ans = checkHeightBalanced(root, h);
        return ans;
    }
};

struct Node{
    int index;
    int val;
    int pre;
    int type; // 0 left, 1 right , -1 root
    Node(int index=-1, int val = -1, int pre = -1, int type = -1):index(index), val(val), pre(pre), type(type){

    }
};

void born(vector<Node>&data, TreeNode* root){
    for(vector<Node>::iterator it = data.begin(); it != data.end(); it++){
        int index = it->index;
        int val = it->val;
        int pre = it->pre;
        int type = it->type;

        root[index].val = val;
        if(pre != -1){
            if(type == 0){
                root[pre].left = root + index;
            }else if(type == 1){
                root[pre].right = root + index;
            }else{
                printf("WARNING: data error. type = %d\n", type);
            }
        }
    }
}

void output(TreeNode* root, int lev=0, int pre = -1){
    printf("lev = %d pre = %d addr = %p\n", lev, pre, root);
    if(root != NULL){
        output(root->left, lev+1, root->val);
        output(root->right, lev+1, root->val);
    }
}

void test(){
    srand(time(NULL));
    Solution work;

    TreeNode list[100];
    int ans;

    vector<Node> data;

    data = {
        {0, 0, -1, -1},
        {1, 1, 0, 0},
        {2, 2, 0, 1},
    };
    memset(list, 0, sizeof(list));
    born(data, list);
    output(list);
    ans = work.isBalanced(list);
    printf("ans=%d\n", ans);

    data = {
        {0, 0, -1, -1},
        {1, 1, 0, 0},
        {2, 2, 0, 1},
        {3, 3, 2, 0},
    };
    memset(list, 0, sizeof(list));
    born(data, list);
    output(list);
    ans = work.isBalanced(list);
    printf("ans=%d\n", ans);
    
    data = {
        {0, 0, -1, -1},
        {1, 1, 0, 0},
        {2, 2, 0, 1},
        {3, 3, 2, 0},
        {4, 4, 3, 1},
    };
    memset(list, 0, sizeof(list));
    born(data, list);
    output(list);
    ans = work.isBalanced(list);
    printf("ans=%d\n", ans);
}

int main(){
    test();
    return 0;
}
