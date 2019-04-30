/*************************************************************************
    > File Name: flatten-a-multilevel-doubly-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 18 00:22:11 2019
 ************************************************************************/

#include "../../include/base.h"

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};

class Solution {
    Node* get(Node* root){
        Node* it = root;
        Node* ansTail = root;
        while(it){
            ansTail = it;
            if(it->child){
                Node* head = it->child;
                Node*  tail = get(head);
                head->prev = it;
                tail->next = it->next;
                it->next = head;
                if(tail->next){
                    tail->next->prev = tail;
                    ansTail = tail->next;
                }else{
                    ansTail = tail;
                }
                it->child = NULL;

                it = tail->next;
            }else{
                it = it->next;
            }
        }
        return ansTail;
    }
public:
    Node* flatten(Node* head) {
        get(head);
        return head;
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
//    TEST_SMP1(Solution, flatten, expectAns, first);
//

    return 0;
}
