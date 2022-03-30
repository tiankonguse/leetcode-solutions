/*************************************************************************
    > File Name: linked-list-cycle-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Sun Apr 14 23:56:05 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    bool hasCycle(ListNode *head){
        ListNode* slow = head;
        ListNode* fast = head;
        while (slow && fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
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
    bool expectAns;

    first = vecToList({3,2,0,-4}, root);
    root[3].next = root+2;
    expectAns = true;
    TEST_SMP1(Solution, hasCycle, expectAns, first);

    first = vecToList({1,2}, root);
    root[1].next = root+0;
    expectAns = true;
    TEST_SMP1(Solution, hasCycle, expectAns, first);


    first = vecToList({1}, root);
    expectAns = false;
    TEST_SMP1(Solution, hasCycle, expectAns, first);


    first = vecToList({3,2,0,-4,-5}, root);
    root[4].next = root+2;
    expectAns = true;
    TEST_SMP1(Solution, hasCycle, expectAns, first);


    first = vecToList({3,2,0,-4,-5,-6}, root);
    root[5].next = root+2;
    expectAns = true;
    TEST_SMP1(Solution, hasCycle, expectAns, first);

    return 0;
}
