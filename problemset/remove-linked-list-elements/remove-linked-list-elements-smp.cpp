/*************************************************************************
    > File Name: remove-linked-list-elements-smp.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月17日 12:58:38
 ************************************************************************/

#include "../../include/base.h"

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while(head && head->val == val){
            head = head->next;
        }
        ListNode* pre = head;
        while(pre && pre->next){
            if(pre->next->val == val){
                pre->next = pre->next->next;
            }else{
                pre = pre->next;
            }
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
    int second;
    ListNode* expectAns;

    first = vecToList({1,2,6,3,4,5,6});
    second = 6;
    expectAns = vecToList({1,2,3,4,5});
    TEST_SMP2(Solution, removeElements, expectAns, first, 6);


    return 0;
}
