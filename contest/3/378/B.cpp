// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<unordered_map<ll, ll>> stat;
  void Init(const string& s) {
    stat.resize(26);
    int preVal = -1;
    ll preNum = 0;
    for (auto c : s) {
      int val = c - 'a';
      if (val != preVal) {
        if (preNum > 0) {
          stat[preVal][preNum]++;
        }
        preVal = val;
        preNum = 0;
      }
      preNum++;
    }
    if (preNum > 0) {
      stat[preVal][preNum]++;
    }
  }

  bool Check(int mid) {
    if (mid == 0) return true;
    for (auto& m : stat) {
      ll num = 0;
      for (auto [k, v] : m) {
        if (k < mid) continue;
        num += (k - mid + 1) * v;
        if (num >= 3) return true;
      }
    }
    return false;
  }

 public:
  int maximumLength(const string& s) {
    Init(s);
    ll l = 0, r = s.length();  // [l ,r)
    while (l < r) {
      ll mid = (l + r) / 2;
      if (Check(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    r--;
    if (r == 0) {
      r = -1;
    }
    return r;
  }
};