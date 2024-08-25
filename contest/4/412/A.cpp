// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
    min_queue<pair<ll, ll>> que;
    int n = nums.size();
    for (ll i = 0; i < n; i++) {
      ll v = nums[i];
      que.push({v, i});
    }
    while (k--) {
      auto [v, i] = que.top();
      que.pop();
      v = v * multiplier;
      que.push({v, i});
    }
    while (!que.empty()) {
      auto [v, i] = que.top();
      que.pop();
      nums[i] = v;
    }
    return nums;
  }
};