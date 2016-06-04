/*************************************************************************
  > File Name: binary-tree-preorder-traversal.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月21日 20:43:46
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


    struct Node{
        TreeNode* root;
        int lev;//0 root, 1 left, 2 right
        Node(TreeNode* root = NULL, int lev = 0):root(root),lev(lev){
        }
    };

    void loop(TreeNode* root){
        stack<Node> sta;
        sta.push(Node(root, 0));
        Node now;

        while(!sta.empty()){
            now = sta.top();
            sta.pop();

            if(now.root == NULL){
                // null node
                continue;
            }

            if(now.lev == 0){
                //node in left
                ans.push_back(now.root->val);
                now.lev = 1;
                sta.push(now);
                sta.push(Node(now.root->left, 0));
            }else if(now.lev == 1){
                // node in right
                now.lev = 2;
                sta.push(now);
                sta.push(Node(now.root->right, 0));
            }else if(now.lev == 2){
                //node out root
            }
        }
    }
    

public:
    vector<int> preorderTraversal(TreeNode *root) {
        ans.clear();
        //dfs(root);
        loop(root);
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
    ans = work.preorderTraversal(list);
    output(ans);

}

int main() {
    test();
    return 0;
}
