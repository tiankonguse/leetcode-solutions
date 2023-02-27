// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
typedef long long ll;
class Solution {
 public:
  ll minCost(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> h, h1, h2;

    for (auto v : nums1) {
      h[v]++;
      h1[v]++;
    }

    for (auto v : nums2) {
      h[v]++;
      h2[v]++;
    }

    int minVal = INT_MAX;
    for (auto [k, v] : h) {
      minVal = min(k, minVal);
      if (v % 2 != 0) return -1;
    }

    // 除了最小值，删除已经匹配的
    for (auto [k, v] : h) {
      while (h1.count(k) && h2.count(k)) {
        int a = min(h1[k], h2[k]);
        h1[k] -= a;
        h2[k] -= a;
        if (h1[k] == 0) h1.erase(k);
        if (h2[k] == 0) h2.erase(k);
      }
    }

    // 数组相等
    if (h1.empty()) return 0;

    max_queue<ll> que2;
    min_queue<ll> que1;

    if (h2.count(minVal)) {
      swap(h1, h2);
    }

    for (auto [k, v] : h1) {
      while (v) {
        que1.push(k);
        v -= 2;
      }
    }
    for (auto [k, v] : h2) {
      while (v) {
        que2.push(k);
        v -= 2;
      }
    }

    ll ans = 0;
    if (minVal == que1.top()) {
      ans += minVal;
      que1.pop();
      que2.pop();
    }

    while (!que1.empty()) {
      ll val = min(que1.top(), que2.top());
      que1.pop();
      que2.pop();

      if (minVal * 2 < val) {
        ans += minVal * 2;
      } else {
        ans += val;
      }
    }

    return ans;
  }
};