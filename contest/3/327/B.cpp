// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  long long maxKelements(vector<int>& nums, int k) {
    max_queue<ll> que;
    for (auto v : nums) {
      que.push(v);
    }

    ll ans = 0;
    while (k--) {
      ll v = que.top();
      que.pop();
      ans += v;
      que.push((v + 2) / 3);
    }
    return ans;
  }
};