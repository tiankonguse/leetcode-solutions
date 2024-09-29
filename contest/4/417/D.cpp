// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  char kthCharacter(ll k, vector<int>& operations) {
    if (k == 1) return 'a';
    int n = 0;  // 操作次数
    vector<ll> nums;
    nums.push_back(1);
    while (nums.back() < k) {
      nums.push_back(nums.back() * 2);
      n++;
    }
    myprintf("n=%d\n", n);

    int add = 0;
    for (int i = n - 1; i >= 0; i--) {
      int op = operations[i];
      ll N = nums[i + 1];  // 第 i 次操作后的个数
      ll half = N / 2;
      myprintf("i=%d k=%lld N=%lld half=%lld op=%d \n", i, k, N, half, op);
      if (k > half) {  // k 在前一半，什么都不需要操作
        if (op == 1) {
          myprintf("add\n");
          add++;
        }
        k = k - half;
      }
    }
    return 'a' + (add % 26);
  }
};