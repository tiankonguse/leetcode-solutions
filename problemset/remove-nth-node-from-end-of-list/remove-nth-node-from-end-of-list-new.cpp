/*************************************************************************
    > File Name: remove-nth-node-from-end-of-list-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 15 01:08:28 2019
 ************************************************************************/

#include "../../include/base.h"
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head->next == NULL)
            return NULL;

        ListNode* first = head;
        ListNode* second = head;
        ListNode* pre = head;

        n--;
        while(n-->0 && second->next != NULL) {
            second = second->next;
        }

        //del head
        if(second->next == NULL) {
            return head->next;
        }

        while(second->next != NULL) {
            if(pre != first) {
                pre = pre->next;
            }
            first = first->next;
            second = second->next;
        }

        pre->next = first->next;

        return head;
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
    int second;
    ListNode * expectAns;

    first = vecToList({1,2,3,4,5}, root);
    second = 2;
    expectAns = vecToList({1,2,3,5}, root+10);
    TEST_SMP2(Solution, removeNthFromEnd, expectAns, first, second);
    return 0;
}
