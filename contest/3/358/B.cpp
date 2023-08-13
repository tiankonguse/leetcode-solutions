// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
  ListNode* ReverseList(ListNode* head) {
    ListNode root;
    while (head) {
      ListNode* tmp = head;
      head = head->next;

      tmp->next = root.next;
      root.next = tmp;
    }
    return root.next;
  }

  void DoubleList(ListNode* head) {
    ListNode* pre = nullptr;

    int flag = 0;
    while (head) {
      pre = head;
      int v = head->val * 2 + flag;
      head->val = v % 10;
      flag = v / 10;
      head = head->next;
    }
    if (flag) {
      pre->next = new ListNode(flag);
    }
  }

 public:
  ListNode* doubleIt(ListNode* head) {
    head = ReverseList(head);
    DoubleList(head);
    return ReverseList(head);
  }
};
