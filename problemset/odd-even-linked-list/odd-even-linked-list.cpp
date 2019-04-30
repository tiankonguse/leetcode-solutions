/*************************************************************************
    > File Name: odd-even-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月17日 13:01:46
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head == NULL)return head;
        ListNode* slow = head; //Odd
        ListNode* fast = head->next;  //Even
        while(fast && fast->next){
            //remove from fast
            ListNode* tmp = fast->next;
            fast->next = tmp->next;
            //add to slow
            tmp->next = slow->next;
            slow->next = tmp;
            //move next
            fast = fast->next;
            slow = slow->next;
        }
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
    ListNode* expectAns;

    first = vecToList({1,2,3,4,5});
    expectAns = vecToList({1,3,5,2,4});
    TEST_SMP1(Solution, oddEvenList, expectAns, first);

    return 0;
}
