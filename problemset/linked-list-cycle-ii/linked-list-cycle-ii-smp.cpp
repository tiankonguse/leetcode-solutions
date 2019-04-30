/*************************************************************************
    > File Name: linked-list-cycle-ii-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr 15 00:51:53 2019
 ************************************************************************/

#include "../../include/base.h"

class Solution {

public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (slow && fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }
        if(!(slow && fast && fast->next)){
            return NULL;
        }

        // now have cycle
        slow = head;
        while(slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
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
