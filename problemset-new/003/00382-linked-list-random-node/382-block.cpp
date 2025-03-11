
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

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
  int n = 0;
  int B = 0;
  vector<ListNode*> nums;

 public:
  Solution(ListNode* head) {
    for (ListNode* p = head; p; p = p->next) {
      n++;
    }
    B = sqrt(n);
    nums.reserve(n);
    int i = 0;
    for (ListNode* p = head; p; p = p->next, i++) {
      if (i % B == 0) {
        nums.push_back(p);
      }
    }
  }

  int getRandom() {
    const int r = rand() % n;
    int a = r / B, b = r % B;
    ListNode* p = nums[a];
    while (b && p) {
      p = p->next;
      b--;
    }
    return p->val;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif