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
  pair<ListNode*, ListNode*> Remove(ListNode* list1, int a, int b) {
    ListNode* leftHead = list1;
    ListNode* leftTail = list1;
    int num = 0;
    while (num < a) {
      leftTail = list1;
      list1 = list1->next;
      num++;
    }
    leftTail->next = nullptr;

    while (num <= b) {
      list1 = list1->next;
      num++;
    }
    return {leftHead, list1};
  }
  ListNode* Merge(ListNode* list1, ListNode* list2) {
    ListNode* head = list1;
    while (list1->next != nullptr) {
      list1 = list1->next;
    }

    list1->next = list2;

    return head;
  }

 public:
  ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
    auto [listPre, listSuf] = Remove(list1, a, b);
    return Merge(Merge(listPre, list2), listSuf);
  }
};