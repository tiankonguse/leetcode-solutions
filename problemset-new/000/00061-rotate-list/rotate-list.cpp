/*************************************************************************
    > File Name: rotate-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 18 01:06:04 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
    int getLen(ListNode* head){
        int len = 0;
        while(head){
            len++;
            head = head->next;
        }
        return len;
    }
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || (!head->next) || k<=0)return head;
        ListNode* mid = NULL;
        ListNode* tail = head;
        int len = getLen(head);
        k %= len;
        if(k == 0)return head;
        k = len - k;
        len = 1;

        while(tail->next){
            if(len == k){
                mid = tail;
            }
            tail = tail->next;
            len++;
        }
        ListNode* newHead = mid->next;
        mid->next = NULL;
        tail->next = head;
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
    ListNode* first;
    int second;
    ListNode* expectAns;

    first = vecToList({1,2,3,4,5});
    second = 2;
    expectAns = vecToList({4,5,1,2,3});
    TEST_SMP2(Solution, rotateRight, expectAns, first, second);

    first = vecToList({0,1,2});
    second = 4;
    expectAns = vecToList({2,0,1});
    TEST_SMP2(Solution, rotateRight, expectAns, first, second);
    return 0;
}
