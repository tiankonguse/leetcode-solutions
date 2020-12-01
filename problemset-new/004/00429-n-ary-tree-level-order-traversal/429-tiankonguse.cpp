/*************************************************************************
    > File Name: n-ary-tree-level-order-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月25日 20:52:15
    > link: https://leetcode.com/problems/n-ary-tree-level-order-traversal/
    > No: 429. N-ary Tree Level Order Traversal
    > Contest:
 ************************************************************************/

#include "../../../include/base.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if(!root)return ans;
        queue<Node*> que;
        que.push(root);

        while(!que.empty()){
            int levelLen = que.size();
            vector<int> levelAns;

            while(levelLen--){
                Node* now = que.front();que.pop();
                levelAns.push_back(now->val);

                for(int i = 0; i < now->children.size(); i++){
                    que.push(now->children[i]);
                }
            }
            ans.push_back(levelAns);
        }
        return ans;
    }
};

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
    TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
