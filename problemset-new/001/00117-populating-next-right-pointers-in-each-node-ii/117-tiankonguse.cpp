/*************************************************************************
    > File Name: populating-next-right-pointers-in-each-node-ii.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年05月21日 21:26:45
    > link: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
    > No: 117. Populating Next Right Pointers in Each Node II
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
public:
    Node* connect(Node* root) {
        if(!root)
            return root;

        Node* preHead = root;
        Node* nowHead = NULL;
        Node* nowPoint = NULL;

        while(preHead) {
            nowPoint = nowHead = NULL;
            while(preHead) {
                if(preHead->left) {
                    if(nowPoint) {
                        nowPoint->next = preHead->left;
                    }
                    nowPoint = preHead->left;
                }
                if(nowPoint && !nowHead)
                    nowHead = nowPoint;

                if(preHead->right) {
                    if(nowPoint) {
                        nowPoint->next = preHead->right;
                    }
                    nowPoint = preHead->right;
                }
                if(nowPoint && !nowHead)
                    nowHead = nowPoint;

                preHead = preHead->next;
            }
            preHead = nowHead;
        }
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
