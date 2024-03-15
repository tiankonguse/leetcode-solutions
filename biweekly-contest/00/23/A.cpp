// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int H(int v) {
    int ans = 0;

    while (v) {
      ans += v % 10;
      v /= 10;
    }

    return ans;
  }

 public:
  int countLargestGroup(int n) {
    unordered_map<int, int> m;
    while (n) {
      m[H(n)]++;
      n--;
    }
    int ans = 0;
    int groupSize = 0;
    for (auto [k, v] : m) {
      if (groupSize == v) {
        ans++;
      } else if (groupSize < v) {
        ans = 1;
        groupSize = v;
      }
    }
    return ans;
  }
};
