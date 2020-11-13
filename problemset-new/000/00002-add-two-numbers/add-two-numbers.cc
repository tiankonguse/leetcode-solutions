/*************************************************************************
    > File Name: add-two-numbers-new.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Thu Apr 18 00:07:03 2019
 ************************************************************************/

#include "base.h"

class Solution {
  ListNode* head;
  ListNode* tail;
  int pre;
  void add(int val) {
    pre += val;
    ListNode* node = new ListNode(pre % 10);
    pre /= 10;
    if (head == NULL) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }

 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    head = tail = NULL;
    pre = 0;
    while (l1 && l2) {
      add(l1->val + l2->val);
      l1 = l1->next;
      l2 = l2->next;
    }
    ListNode* l3 = l1 ? l1 : l2;
    while (l3) {
      add(l3->val);
      l3 = l3->next;
    }
    if (pre) {
      add(0);
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
  TEST_SMP2(Solution, addTwoNumbers, vecToList({7, 0, 8}), vecToList({2, 4, 3}),
            vecToList({5, 6, 4}));

  return 0;
}
