/*************************************************************************
    > File Name: copy-list-with-random-pointer.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 18 00:50:09 2019
 ************************************************************************/

#include "../../include/base.h"

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

class Solution {
    map<Node*, Node*> m;
    Node* get(Node* head) {
        if(m.find(head) == m.end()) {
            m[head] = new Node(head->val, NULL, NULL);
        }
        return m[head];
    }
public:
    Node* copyRandomList(Node* head) {
        m[NULL]=NULL;
        Node* newHead = get(head);
        Node* tail = newHead;
        while(head) {
            tail->next = get(head->next);
            tail->random = get(head->random);
            tail=tail->next;
            head=head->next;
        }
        return newHead;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4});

    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    int first;
    int expectAns;

//    first = 113;
//    expectAns = 112;
//    TEST_SMP1(Solution, copyRandomList, expectAns, first);
//

    return 0;
}
