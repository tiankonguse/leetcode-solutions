/*************************************************************************
    > File Name: find-duplicate-subtrees.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 25 01:16:52 2019
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    map<string, TreeNode*> treeMap;
    set<string> ansSet;

    string dfs(TreeNode* root){
        if(root == NULL){
            return "()";
        }

        string str = "(" + dfs(root->left) + to_string(root->val) + dfs(root->right) + ")";
        if(treeMap.find(str) == treeMap.end()){
            treeMap[str] = root;
        }else{
            ansSet.insert(str);
        }
        return str;
    }

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        vector<TreeNode*> ans;
        for(auto s : ansSet){
            ans.push_back(treeMap[s]);
        }
        return ans;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});

    #define CLASS Solution
    #define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;


    first = 1;
    second = 1;
    expectAns = 1;
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);
*/
int main() {
    #define CLASS Solution
    #define FUNCTION findDuplicateSubtrees

    TreeNode* first;
    int second;
    vector<TreeNode*> expectAns;

    first = vecToTree({1,2,3,4,null,2,4,null,null,4});
    second = 1;
    expectAns = {vecToTree({2,4}), vecToTree({4})};
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
