/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月19日 16:45:45
 ************************************************************************/


#include "../../include/base.h"

class Solution {
    void getLeaf(TreeNode* root,vector<int>& leaf) {
        if(!root)
            return;
        if(!root->left && !root->right) {
            leaf.push_back(root->val);
            return ;
        }
        getLeaf(root->left, leaf);
        getLeaf(root->right, leaf);
    }
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaf1;
        vector<int> leaf2;
        getLeaf(root1, leaf1);
        getLeaf(root2, leaf2);
        if(leaf1.size() != leaf2.size()) {
            return false;
        }
        for(int i=0; i<leaf1.size(); i++) {
            if(leaf1[i] != leaf2[i]) {
                return false;
            }
        }
        return true;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    vecToTree();

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    TreeNode* first;
    TreeNode* second;
    bool expectAns;

    first = vecToTree({3,5,1,6,2,9,8,null,null,7,4});
    expectAns = vecToTree({3,5,1,6,7,4,2,null,null,null,null,null,null,9,8});
    TEST_SMP2(Solution, leafSimilar, expectAns, first, second);


    return 0;
}
