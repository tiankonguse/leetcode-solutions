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
  vector<int> aa, bb;
  void Fix(vector<int>& nums) {
    if (nums[0] > nums[1]) {
      swap(nums[0], nums[1]);
    }
  }
  bool Check() {
    if (aa.size() != 2) return false;
    Fix(aa);
    Fix(bb);
    return aa == bb;
  }
  bool Check(int a, int b) {
    if (a == b) return true;

    aa.clear();
    bb.clear();
    while (a > 0 || b > 0) {
      if ((a % 10) != (b % 10)) {
        aa.push_back(a % 10);
        bb.push_back(b % 10);
        if (aa.size() == 2) {
          if (!Check()) {
            return false;
          }
        }
        if (aa.size() == 3) {
          return false;
        }
      }
      a = a / 10;
      b = b / 10;
    }

    return Check();
  }

 public:
  int countPairs(vector<int>& nums) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (Check(nums[i], nums[j])) {
          ans++;
          continue;
        }
      }
    }

    return ans;
  }
};