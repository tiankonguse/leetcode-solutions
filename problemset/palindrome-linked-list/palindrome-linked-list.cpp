/*************************************************************************
    > File Name: palindrome-linked-list.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2019年04月17日 13:14:25
 ************************************************************************/

#include "../../include/base.h"

class Solution {
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
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next)return true;
        ListNode* slow = head; //Odd
        ListNode* fast = head;  //Even
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        slow = reverseList(slow);
        while(head && slow){
            if(head->val != slow->val){
                return false;
            }
            slow = slow->next;
            head = head->next;
        }
        return true;
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
    bool expectAns;

    first = vecToList({1,2});
    expectAns = false;
    TEST_SMP1(Solution, isPalindrome, expectAns, first);

    first = vecToList({1,2,2,1});
    expectAns = true;
    TEST_SMP1(Solution, isPalindrome, expectAns, first);

    return 0;
}
