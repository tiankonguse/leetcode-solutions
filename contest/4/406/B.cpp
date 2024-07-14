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
 public:
  ListNode* modifiedList(vector<int>& nums, ListNode* head) {
    ListNode root(0, head);
    ListNode* pre = &root;

    unordered_set<int> h = {nums.begin(), nums.end()};
    while (pre->next) {
      if (h.count(pre->next->val)) {
        pre->next = pre->next->next;
      } else {
        pre = pre->next;
      }
    }
    return root.next;
  }
};