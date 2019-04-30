/*************************************************************************
    > File Name: intersection-of-two-linked-lists.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 15 00:55:24 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    ListNode * getLast(ListNode *head, int& len) {
        ListNode * tmp = head;
        len = 1;
        while(tmp->next != NULL) {
            tmp = tmp->next;
            len++;
        }
        return tmp;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL)
            return NULL;

        int lenA = 1;
        ListNode *tmpA = getLast(headA, lenA);
        int lenB = 1;
        ListNode *tmpB = getLast(headB, lenB);

        if(tmpB != tmpB) {
            return NULL;
        }

        while(lenA != lenB) {
            if(lenA > lenB) {
                lenA--;
                headA = headA->next;
            } else {
                lenB--;
                headB = headB->next;
            }
        }
        while(headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        return headB;
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
    ListNode root[100];
    ListNode * first;
    ListNode * expectAns;

    first = vecToList({3,2,0,-4}, root);
    root[3].next = root+2;
    expectAns = root+2;
    TEST_SMP1(Solution, detectCycle, expectAns, first);

    first = vecToList({1,2}, root);
    root[1].next = root+0;
    expectAns = root+0;
    TEST_SMP1(Solution, detectCycle, expectAns, first);


    first = vecToList({1}, root);
    expectAns = NULL;
    TEST_SMP1(Solution, detectCycle, expectAns, first);


    first = vecToList({3,2,0,-4,-5}, root);
    root[4].next = root+2;
    expectAns = root+2;
    TEST_SMP1(Solution, detectCycle, expectAns, first);


    first = vecToList({3,2,0,-4,-5,-6}, root);
    root[5].next = root+2;
    expectAns = root+2;
    TEST_SMP1(Solution, detectCycle, expectAns, first);

    return 0;
}
