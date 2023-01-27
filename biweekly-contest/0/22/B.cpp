// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int val[3];
  int leftVal = 0;
  int midVal = 0;
  int rightVal = 0;
  void Init() {
    for (int i = 0; i < 4; i++) {
      val[0] |= 1 << (i + 2);
      val[1] |= 1 << (i + 4);
      val[2] |= 1 << (i + 6);
    }
  }
  int Cal(int v) {
    int ans = 0;
    for (auto bit : val) {
      if ((v & bit) == 0) {
        ans++;
        v |= bit;
      }
    }
    return ans;
  }

 public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    Init();

    unordered_map<int, int> m;
    for (auto& v : reservedSeats) {
      int x = v[0], y = v[1];
      m[x] |= (1 << y);
    }

    int ans = (n - m.size()) * 2;
    for (auto [k, v] : m) {
      ans += Cal(v);
    }

    return ans;
  }
};