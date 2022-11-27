#include <bits/stdc++.h>

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
  ListNode* Dfs(ListNode* root) {
    if (root == nullptr) return root;
    root->next = Dfs(root->next);
    if (root->next == nullptr) {
      return root;
    }

    if (root->val < root->next->val) {
      return root->next;
    } else {
      return root;
    }
  }

 public:
  ListNode* removeNodes(ListNode* head) { return Dfs(head); }
};
