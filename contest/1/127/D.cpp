/*************************************************************************
    > File Name: construct-binary-search-tree-from-preorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Mar 10 09:58:54 2019
    > desc: 1008. Construct Binary Search Tree from Preorder Traversal
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<time.h>
#include "../../include/base.h"
using namespace std;


#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int debug = 0;
typedef unsigned uint;
typedef unsigned char uchar;
auto __ =[]() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}
();


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
    TreeNode* dfs(vector<int>& preorder, int left, int right) {
        if(left > right){
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[left]);
        int mid;
        for(mid=left;mid<=right;mid++){
            if(preorder[mid] > preorder[left]){
                break;
            }
        }
        root->left = dfs(preorder, left + 1, mid - 1);
        root->right = dfs(preorder, mid, right);

        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return dfs(preorder, 0, preorder.size()-1);
    }
};
template <class ansType, class dataType1 = int, class dataType2 = int>
void test(ansType& expectAns, dataType1& A = dataType1(), dataType2 K = dataType2()) {
    Solution work;
    ansType ans;
    ans = work.bstFromPreorder(A);

    output("ans", ans);
    return ;
    static int index = 0;
    index++;
    bool check = eq(ans, expectAns);
    printf("\n");
    if(!check) {
        printf("index %d: NO\n", index);
        output("A", A);
        output("K", K);
        output("ans", ans);
        output("expectAns", expectAns);
    } else {
        printf("index %d: YES\n", index);
    }
    printf("\n");

}

int main() {
    vector<int> data;
    TreeNode* expectAns;


    data = {8,5,1,7,10,12};
    //expectAns = 5;
    test(expectAns, data);

    return 0;
}
