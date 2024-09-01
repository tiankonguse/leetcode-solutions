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
  ll abs(ll x) {
    if (x < 0) {
      return -x;
    }
    return x;
  }

 public:
  vector<int> resultsArray(vector<vector<int>>& queries, int k) {
    max_queue<ll> que;
    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      ll x = abs(q[0]);
      ll y = abs(q[1]);
      ll dis = x + y;
      que.push(dis);
      if (que.size() < k) {
        ans.push_back(-1);
        continue;
      }
      if (que.size() > k) {
        que.pop();
      }
      ans.push_back(que.top());
    }
    return ans;
  }
};