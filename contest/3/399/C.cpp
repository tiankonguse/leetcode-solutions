// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

typedef long long ll;
class Solution {
  vector<ll> flag;
  void Add(int N) {
    for (int i = 1; i * i <= N; i++) {
      if (N % i == 0) {
        int j = N / i;
        flag[i]++;
        if (i != j) {
          flag[j]++;
        }
      }
    }
  }

 public:
  long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    int maxVal = 100;
    for (auto v : nums1) {
      maxVal = max(maxVal, v + 1);
    }

    flag.resize(maxVal, 0);
    for (auto v : nums1) {
      if (v % k == 0) {
        Add(v / k);
      }
    }
    ll ans = 0;
    for (auto v : nums2) {
      if (v < maxVal) {
        ans += flag[v];
      }
    }
    return ans;
  }
};