// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
  struct T {
    int flag = 1;
    max_queue<ll> que;
  };

 public:
  long long findMaximumElegance(vector<vector<int>>& items, int k) {
    unordered_map<int, T> m;
    for (auto& v : items) {
      ll V = v[0];
      int c = v[1];
      auto& t = m[c];
      t.flag = 1;
      t.que.push(V);
    }

    max_queue<tuple<ll, int, int>> que;  // <V, flag, c>
    for (auto& [c, t] : m) {
      que.push({t.que.top(), t.flag, c});
    }

    ll ans = 0;
    ll sum = 0;
    ll diffCategory = 0;

    min_queue<ll> double_que;  // 可以被替换的元素

    // 先从大到小选择 k 个
    for (int i = 0; i < k; i++) {
      auto [V, flag, c] = que.top();
      que.pop();
      auto& t = m[c];
      t.que.pop();

      sum += V;
      if (flag) {
        diffCategory++;
        t.flag = 0;
      } else {
        double_que.push(V);
      }

      if (t.que.size() > 0) {
        que.push({t.que.top(), t.flag, c});
      }
    }
    ans = sum + diffCategory * diffCategory;

    // 已选择的元素里面，重复的品类里，选择出最小的值
    while (!que.empty() && !double_que.empty()) {
      auto [V, flag, c] = que.top();
      que.pop();
      if (flag == 0) continue;  // 已选择，忽略

      int oldV = double_que.top();
      double_que.pop();

      sum = sum - oldV + V;
      diffCategory++;

      ans = max(ans, sum + diffCategory * diffCategory);
    }

    return ans;
  }
};
