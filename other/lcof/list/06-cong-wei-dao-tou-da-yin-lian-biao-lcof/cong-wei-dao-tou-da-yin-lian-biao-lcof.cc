#include "base.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  vector<int> reversePrint(ListNode* head) {
    stack<int> sta;
    while (head) {
      sta.push(head->val);
      head = head->next;
    }

    vector<int> ans;
    while (!sta.empty()) {
      ans.push_back(sta.top());
      sta.pop();
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, reversePrint, vector<int>({2, 3, 1}),
            vecToList({1, 3, 2}));

  return 0;
}