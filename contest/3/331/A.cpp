// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  ll pickGifts(vector<int>& gifts, int k) {
    max_queue<ll> que;
    for (auto v : gifts) {
      que.push(v);
    }
    while (k--) {
      ll v = que.top();
      que.pop();
      que.push(sqrt(v * 1.0));
    }
    ll ans = 0;
    while (!que.empty()) {
      ans += que.top();
      que.pop();
    }
    return ans;
  }
};