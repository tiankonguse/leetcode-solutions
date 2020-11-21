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
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
  ListNode* merge(ListNode* left, ListNode* right) {
    ListNode root(0);
    ListNode* head = &root;

    while (left && right) {
      if (left->val < right->val) {
        head->next = left;
        head = left;
        left = left->next;
      } else {
        head->next = right;
        head = right;
        right = right->next;
      }
    }

    if (left != NULL) {
      head->next = left;
    } else if (right != NULL) {
      head->next = right;
    } else {
      head->next = NULL;
    }

    return root.next;
  }

  ListNode* Next(ListNode* head, int step) {
    while (head && step) {
      head = head->next;
      step--;
    }
    return head;
  }
  ListNode* Last(ListNode* head) {
    while (head->next) {
      head = head->next;
    }
    return head;
  }

 public:
  ListNode* sortList(ListNode* head) {
    if (head == NULL || head->next == NULL) {
      return head;
    }
    ListNode root(0, head);

    for (int step = 1;; step <<= 1) {
      ListNode* preEnd = &root;
      if (Next(preEnd, step) == NULL) {
        break;
      }

      while (preEnd) {
        ListNode* left = preEnd->next;
        ListNode* leftEnd = Next(preEnd, step);
        if (leftEnd == NULL || leftEnd->next == NULL) break;  //只有一条链

        ListNode* right = leftEnd->next;
        ListNode* rightEnd = Next(leftEnd, step);

        leftEnd->next = NULL;       //左半部
        ListNode* nextHead = NULL;  //下一个
        if (rightEnd != NULL) {
          nextHead = rightEnd->next;
          rightEnd->next = NULL;  //右半部
        }

        preEnd->next = merge(left, right);

        rightEnd = Last(preEnd->next);
        rightEnd->next = nextHead;
        preEnd = rightEnd;
      }
    }
    return root.next;
  }
};

/*
    //ListNode* root = vecToList({1,2,3,4});
    // vecToTree({});
    // std::reverse(a.begin(),a.end());
    //int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
*/
int main() {
  TEST_SMP1(Solution, sortList, vecToList({}), vecToList({}));
  TEST_SMP1(Solution, sortList, vecToList({1, 2}), vecToList({1, 2}));
  TEST_SMP1(Solution, sortList, vecToList({1, 2}), vecToList({2, 1}));
  TEST_SMP1(Solution, sortList, vecToList({1, 2, 3, 4}),
            vecToList({4, 2, 1, 3}));
  TEST_SMP1(Solution, sortList, vecToList({-1, 0, 3, 4, 5}),
            vecToList({-1, 5, 3, 4, 0}));

  return 0;
}
