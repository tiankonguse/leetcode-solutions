// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int Abs(int a, int b) {
    if (a < b) {
      return b - a;
    }
    return a - b;
  }

 public:
  vector<int> beautifulIndices(const string& s, string a, string b, int k) {
    int sn = s.length();
    int an = a.length();
    int bn = b.length();

    set<int> h;
    for (int bi = 0; bi + bn <= sn; bi++) {
      if (strncmp(b.data(), s.data() + bi, bn) == 0) {
        h.insert(bi);
        // printf("bi=%d\n", bi);
      }
    }

    vector<int> ans;
    ans.reserve(sn);

    if (h.size() == 0) {
      return ans;
    }

    for (int ai = 0; ai + an <= sn; ai++) {
      if (strncmp(a.data(), s.data() + ai, an) != 0) {
        continue;
      }
      // printf("ai=%d\n", ai);
      auto it = h.lower_bound(ai);
      if (it != h.end()) {
        int v = *it;
        if (Abs(ai, v) <= k) {
          ans.push_back(ai);
          continue;
        }
      }

      if (it != h.begin()) {
        it--;
        int v = *it;
        if (Abs(ai, v) <= k) {
          ans.push_back(ai);
          continue;
        }
      }
    }

    return ans;
  }
};