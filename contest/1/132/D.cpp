/*************************************************************************
    > File Name: A.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 14 10:19:00 2019
 ************************************************************************/

#include "../../include/base.h"

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
    int readNum(int& i, string& S) {
        int ans = 0;
        while(S[i] >= '0' && S[i] <= '9') {
            ans = ans * 10 + S[i] - '0';
            i++;
        }
        return ans;
    }
    int readDash(int& i, string& S) {
        int ans = 0;
        while(S[i] == '-') {
            ans++,i++;
        }
        return ans;
    }
public:
    TreeNode* recoverFromPreorder(string S) {
        stack<pair<TreeNode*, int>> sta;
        int pos = 0;
        int depth = 0;
        int val;

        val = readNum(pos, S);

        TreeNode* root = new TreeNode(val);
        sta.push(make_pair(root, 0));

        while(pos < S.length()) {
            depth = readDash(pos, S);
            val = readNum(pos, S);
            TreeNode* nowNode = new TreeNode(val);

            //get pre
            while(!sta.empty()) {
                auto p = sta.top();
                TreeNode* preNode = p.first;
                //not pre
                if(depth != p.second + 1) {
                    sta.pop();
                    continue;
                }
                if(preNode->left == nullptr) {
                    preNode->left = nowNode;
                } else {
                    preNode->right = nowNode;
                }
                sta.push(make_pair(nowNode, depth));
                break;
            }
        }

        return root;

    }
};

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    string first;
    TreeNode* expectAns;

    first = "1-2--3--4-5--6--7";
    expectAns = vecToTree({1,2,5,3,4,6,8});
    TEST_SMP1(Solution, recoverFromPreorder, expectAns, first);


    first = "1-2--3---4-5--6---7";
    expectAns = vecToTree({1,2,5,3,null,6,null,4,null,8});
    TEST_SMP1(Solution, recoverFromPreorder, expectAns, first);

    first = "1-401--349---90--88";
    expectAns = vecToTree({1,401,null,349,88,90});
    TEST_SMP1(Solution, recoverFromPreorder, expectAns, first);

    return 0;
}
