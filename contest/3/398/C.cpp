// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll sumDigitDifferences1(vector<int>& nums) {
    ll n = nums.size();
    vector<vector<ll>> bits(12, vector<ll>(10, 0));
    for (auto v : nums) {
      for (int i = 0; i < 12; i++) {
        int unit = v % 10;
        v = v / 10;
        bits[i][unit]++;
      }
    }

    ll ans = 0;
    for (auto& bit : bits) {
      for (ll v : bit) {
        if (v == 0) continue;
        ans += v * (n - v);
      }
    }
    return ans / 2;
  }
  ll sumDigitDifferences(vector<int>& nums) {
    ll n = nums.size();
    vector<vector<ll>> bits(12, vector<ll>(10, 0));
    for (auto v : nums) {
      for (int i = 0; i < 12; i++) {
        int unit = v % 10;
        v = v / 10;
        bits[i][unit]++;
      }
    }

    ll ans = 0;
    for (auto& bit : bits) {
      for (ll v : bit) {
        if (v == 0) continue;
        ans += v * (n - v);
      }
    }
    return ans / 2;
  }
};