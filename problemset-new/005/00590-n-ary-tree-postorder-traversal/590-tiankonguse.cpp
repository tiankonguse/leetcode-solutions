/*************************************************************************
    > File Name: n-ary-tree-postorder-traversal.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月25日 20:49:52
    > link: https://leetcode.com/problems/n-ary-tree-postorder-traversal/
    > No: 590. N-ary Tree Postorder Traversal
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
    vector<int> postorder(Node* root) {
        vector<int> ans;
        stack<Node*> sta;
        sta.push(root);
        while(!sta.empty()) {
            Node* now = sta.top();
            sta.pop();
            if(!now)
                continue;
            if(now->children.size() == 0) {
                ans.push_back(now->val);
                continue;
            }
            sta.push(now);
            for(int i = now->children.size()-1; i>=0; i--) {
                sta.push(now->children[i]);
            }
            now->children.clear();
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
    //TEST_SMP1(CLASS, FUNCTION, expectAns, first);
    //TEST_SMP2(Solution, FUNCTION, expectAns, first, second);

    return 0;
}
