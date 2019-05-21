/*************************************************************************
    > File Name: tiankonguse.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月21日 21:22:24
    > link:
    > No:
    > Contest:
 ************************************************************************/

#include "../../include/base.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
    void connect(Node* left, Node* right) {
        while(left && right) {
            left->next = right;
            left = left->right;
            right = right->left;
        }
    }
public:
    Node* connect(Node* root) {
        if(!root)
            return root;
        connect(root->left, root->right);
        connect(root->left);
        connect(root->right);
        return root;
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
