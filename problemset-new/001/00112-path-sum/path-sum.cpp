/*************************************************************************
  > File Name: path-sum.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年04月17日  9:46:32
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
    void set(int val, TreeNode*left=NULL, TreeNode*right = NULL){
        this->val = val;
        this->left = left;
        this->right = right;
    }
};
class Solution {
    int sum;
    bool dfs(int now, TreeNode* root){
        now += root->val;

        //have left branch and go to leaf can get sum
        if(root->left != NULL && dfs(now, root->left)){
            return true; 
        }

        //have rightbranch and go to leaf can get sum
        if(root->right != NULL && dfs(now, root->right)){
            return true; 
        }
        
        //already go leaf, check sum
        if(root->left == NULL && root->right == NULL){
            return now == sum;
        }

        //return branch node 
        return false;
    }
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if(root == NULL){
            return false;
        }
        this->sum = sum;
        bool ans = dfs(0, root);
        return ans;
    }
};

struct Data{
    int pos;
    int val;
    int pre;
    int dir;//0 left, 1 right
    Data(int pos, int val, int pre, int dir):pos(pos),val(val),pre(pre),dir(dir){

    }
};

void add(TreeNode* list, Data const& data){
    int pos = data.pos;
    int val = data.val;
    int pre = data.pre;
    int dir = data.dir;

    list[pos].val = val;
    if(pre != -1){
        if(dir == 0){
            list[pre].left = list + pos;
        }else if(dir == 1){
            list[pre].right = list + pos;
        }
    }
}

void output(TreeNode* root, int lev=0){
    
    if(root == NULL){
        printf("bode = %p\n", root);
        return;
    }

    printf("node = %d left = %p right=%p\n", root->left, root->right);
    output(root->left, lev-1);
    output(root->right, lev-1);

}

void test(){
    Solution work;
    TreeNode list[100];
//    const Data* dataList = {
//        {0, 5, -1, 0},
//        {1, 4, 0, 0},
//        {2, 8, 0, 1},
//        {3, 11, 1, 0},
//        {4, 13, 2, 0},
//        {5, 4, 2, 1},
//        {6, 7, 3, 0},
//        {7, 2, 3, 1},
//        {8, 1, 4, 1}
//    };
//
//    int size = sizeof(dataList)/sizeof(Data);
//    for(int i=0;i<size;i++){
//       list[dataList[i].pos].set(dataList[i].val); 
//    }
//    for(int i=0;i<size;i++){
//        add(list, dataList[i]);
//    }
    
    printf("test begin\n");    
    TreeNode* root = list + 0;
    output(root);
    int ans = work.hasPathSum(root, 22);
    printf("ans = %d\n", ans);
    
    root = list + 0;
    output(root);
    ans = work.hasPathSum(root, 0);
    printf("ans = %d\n", ans);
    
    root = NULL;
    output(root);
    ans = work.hasPathSum(root, 0);
    printf("ans = %d\n", ans);
    
}

int main() {
    test();
    return 0;
}
