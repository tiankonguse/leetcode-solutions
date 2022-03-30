/*************************************************************************
    > File Name: reverse-linked-list-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月17日 12:51:59
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* mid = head;
        while(head && mid->next){
            ListNode* tmp = mid->next;
            mid->next = mid->next->next;
            tmp->next = head;
            head = tmp;
        }
        return head;
    }
};

/*
    //ListNode* root = vecToList({1,2,3,4,5});

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
    ListNode* expectAns;

    first = vecToList({1,2,3,4,5});
    expectAns = vecToList({5,4,3,2,1});
    TEST_SMP1(Solution, reverseList, expectAns, first);


    return 0;
}
