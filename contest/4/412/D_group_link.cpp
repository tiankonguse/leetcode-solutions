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
  inline bool CheckEx(int i, int j) { return aa[i] == bb[j] && aa[j] == bb[i]; }
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

  vector<int> bits;
  int Hash(int v) {
    bits.clear();
    bits.resize(10, 0);
    while (v) {
      bits[v % 10]++;
      v /= 10;
    }
    int h = 0;
    for (int i = 1; i <= 9; i++) {
      int v = bits[i];
      while (v--) {
        h = h * 10 + i;
      }
    }
    return h;
  }

 public:
  int countPairs(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    vector<int> preIndex(n, -1);
    unordered_map<int, int> valToHash;
    unordered_map<int, int> hashIndex;
    for (int i = 0; i < n; i++) {
      int v = nums[i];
      if (!valToHash.count(v)) {
        valToHash[v] = Hash(v);
      }
      int h = Hash(v);

      if (hashIndex.count(h)) {
        preIndex[i] = hashIndex[h];
      }
      hashIndex[h] = i;
    }
    vector<int> tmpNums;
    tmpNums.reserve(n);
    for (auto [h, i] : hashIndex) {
      tmpNums.clear();
      tmpNums.push_back(nums[i]);
      while (preIndex[i] != -1) {
        i = preIndex[i];
        tmpNums.push_back(nums[i]);
      }

      int m = tmpNums.size();
      for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
          if (Check(tmpNums[i], tmpNums[j])) {
            ans++;
            continue;
          }
        }
      }
    }

    return ans;
  }
};