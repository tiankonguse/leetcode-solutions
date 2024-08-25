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
  bool CheckEx(int i, int j) { return aa[i] == bb[j] && aa[j] == bb[i]; }
  bool Check() {
    if (aa.size() <= 1 || aa.size() >= 5) return false;
    if (aa.size() == 2 || aa.size() == 3) {
      sort(aa.begin(), aa.end());
      sort(bb.begin(), bb.end());
      return aa == bb;
    }
    // == 4
    for (int i = 1; i < 4; i++) {
      swap(aa[1], aa[i]);
      swap(bb[1], bb[i]);
      if (CheckEx(0, 1) && CheckEx(2, 3)) {
        return true;
      }
      swap(aa[1], aa[i]);
      swap(bb[1], bb[i]);
    }
    return false;
  }
  bool Check(int a, int b) {
    if (a == b) return true;

    aa.clear();
    bb.clear();
    while (a > 0 || b > 0) {
      if ((a % 10) != (b % 10)) {
        aa.push_back(a % 10);
        bb.push_back(b % 10);
        if (aa.size() == 4) {
          if (!Check()) {
            return false;
          }
        }
        if (aa.size() == 5) {
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