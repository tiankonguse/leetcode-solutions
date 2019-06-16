/*************************************************************************
    > File Name: merge-two-sorted-lists-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Wed Apr 17 23:49:54 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        head = tail = NULL;
        while(l1 && l2){
            l1->val <= l2->val?add(l1):add(l2);
        }
        while(l1)add(l1);
        while(l2)add(l2);
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
    ListNode* first;
    ListNode* second;
    ListNode* expectAns;

    first = vecToList({1,2,4});
    second = vecToList({1,3,4});
    expectAns = vecToList({1,1,2,3,4,4});
    TEST_SMP2(Solution, mergeTwoLists, expectAns, first, second);

    return 0;
}
