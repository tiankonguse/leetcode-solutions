#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  ListNode* insertionSortList(ListNode* head, ListNode* node) {
    if (head == NULL) {
      node->next = NULL;
      return node;
    }

    if (head->val >= node->val) {
      node->next = head;
      return node;
    }

    ListNode* pre = head;
    while (pre->next && pre->next->val < node->val) {
      pre = pre->next;
    }

    node->next = pre->next;
    pre->next = node;

    return head;
  }

 public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode* root = NULL;

    while (head != NULL) {
      ListNode* tmp = head;
      head = head->next;
      root = insertionSortList(root, tmp);
    }

    return root;
  }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
  TEST_SMP1(Solution, insertionSortList, vecToList({}), vecToList({}));
  TEST_SMP1(Solution, insertionSortList, vecToList({1}), vecToList({1}));
  TEST_SMP1(Solution, insertionSortList, vecToList({1, 2}), vecToList({1, 2}));
  TEST_SMP1(Solution, insertionSortList, vecToList({1, 2}), vecToList({2, 1}));
  TEST_SMP1(Solution, insertionSortList, vecToList({2, 3, 4}),
            vecToList({4, 2, 3}));
  TEST_SMP1(Solution, insertionSortList, vecToList({1, 2, 3, 4}),
            vecToList({4, 2, 1, 3}));
  TEST_SMP1(Solution, insertionSortList, vecToList({-1, 0, 3, 4, 5}),
            vecToList({-1, 5, 3, 4, 0}));

  return 0;
}
