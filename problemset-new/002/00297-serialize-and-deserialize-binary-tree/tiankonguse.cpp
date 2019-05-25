/*************************************************************************
    > File Name: serialize-and-deserialize-binary-tree.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月25日 17:29:23
    > link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
    > No: 297. Serialize and Deserialize Binary Tree
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    void split(vector<string>& vec, string& data) {
        int prePos = 1;
        for(int i=1; i<data.size(); i++) {
            if(data[i] == ',') {
                vec.push_back(data.substr(prePos, i-prePos));
                prePos = i+1;
            }
        }
        vec.push_back(data.substr(prePos, data.size()-prePos-1));
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> que;
        if(root)
            que.push(root);
        vector<string> vec;
        while(!que.empty()) {
            root = que.front();
            que.pop();
            if(root == NULL) {
                vec.push_back("null");
            } else {
                vec.push_back(to_string(root->val));
                que.push(root->left);
                que.push(root->right);
            }
        }

        int iEnd = vec.size() - 1;
        while(iEnd > 0 && vec[iEnd] == "null") {
            iEnd--;
        }

        string ans = "[";
        for(int i=0; i<=iEnd; i++) {
            if(i)
                ans.push_back(',');
            ans.append(vec[i]);
        }
        ans.push_back(']');
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.length() == 2)
            return NULL;
        vector<string> vec;
        split(vec, data);
        //for(int i=0;i<vec.size();i++){
        //    printf("%s\n", vec[i].c_str());
        //}


        TreeNode* root = new TreeNode(atoi(vec[0].c_str()));
        queue<TreeNode*> que;
        que.push(root);

        for(int i=1; i<vec.size();) {
            TreeNode* pre = que.front();
            que.pop();
            if(!pre)
                continue;
            if(i<vec.size()) {
                if(vec[i] != "null") {
                    pre->left = new TreeNode(atoi(vec[i].c_str()));
                    que.push(pre->left);
                }
                i++;
            }
            if(i < vec.size()) {
                if(vec[i] != "null") {
                    pre->right = new TreeNode(atoi(vec[i].c_str()));
                    que.push(pre->right);
                }
                i++;
            }
        }

        //printf("data[%s] %s\n",data.c_str(), serialize(root).c_str());

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
#define CLASS Solution
#define FUNCTION smallestRepunitDivByK

    int first;
    int second;
    int expectAns;

    first = 113;
    second = 1;
    expectAns = -1;
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
