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
  int minOperations(vector<int>& nums, int k) {
    min_queue<ll> que;
    for (auto v : nums) {
      que.push(v);
    }
    int ans = 0;
    while (que.top() < k) {
      ll x = que.top();
      que.pop();
      ll y = que.top();
      que.pop();
      que.push(min(x, y) * 2 + max(x, y));
      ans++;
    }
    return ans;
  }
};