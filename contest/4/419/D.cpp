// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  unordered_map<ll, ll> H1;
  set<pair<ll, ll>> H2;

  ll sum = 0;
  pair<ll, ll> minPos;  // [minPos, end())

  void Add(const ll v) {
    const pair<ll, ll> oldP = {H1[v], v};  // 如果不存在，H1[v] 按0计算
    const pair<ll, ll> newP = {oldP.first + 1, oldP.second};
    myprintf("in: add v[%lld] count[%lld], minPos[%lld, %lld] sum[%lld]\n", v,
             oldP.first, minPos.first, minPos.second, sum);

    H1[v]++;
    H2.erase(oldP);
    H2.insert(newP);

    if (oldP >= minPos) {  // 在前 X 个元素中，更新答案
      sum += v;
      // 可能是 minPos 更新
      auto it = H2.lower_bound(minPos);
      minPos = *it;
    } else {  // 不再前 X 个元素中， 需要判断加1后，是否会移动到前 X 中
      if (newP >= minPos) {  // 加1后，比第X个更大了，需要删除第X个，加入 p
        sum -= minPos.first * minPos.second;
        sum += newP.first * newP.second;

        // minPos 前面插入一个元素，所以边界更新为下一个
        auto it = H2.upper_bound(minPos);
        minPos = *it;
      }
    }
    myprintf("out: add v[%lld], minPos[%lld, %lld] sum[%lld]\n", v,
             minPos.first, minPos.second, sum);
  }
  void Remove(ll v) {
    pair<ll, ll> oldP = {H1[v], v};
    const pair<ll, ll> newP = {oldP.first - 1, oldP.second};
    myprintf("in: remove v[%lld] count[%lld], minPos[%lld, %lld] sum[%lld]\n",
             v, oldP.first, minPos.first, minPos.second, sum);

    H1[v]--;
    H2.erase(oldP);
    H2.insert(newP);

    if (oldP >= minPos) {    // 删除的是前 X 个元素, 删除后会后移
      if (newP >= minPos) {  // 减一之后，依旧在前 X 个
        sum -= v;
      } else {  // 减一之后，不满足前 X 个了
        sum -= oldP.first * oldP.second;
        myprintf("remove oldP: [%lld,%lld] sum[%lld]\n", oldP.first,
                 oldP.second, sum);
        auto it = H2.lower_bound(minPos);
        it--;
        minPos = *it;
        sum += minPos.first * minPos.second;
        myprintf("add minPos: [%lld,%lld] sum[%lld]\n", minPos.first,
                 minPos.second, sum);
      }
    }
    myprintf("remove v[%lld], minPos[%lld, %lld] sum[%lld]\n", v, minPos.first,
             minPos.second, sum);
  }
  ll Query() { return sum; }

 public:
  vector<ll> findXSum(vector<int>& nums, const int k, const int x) {
    int n = nums.size();
    vector<ll> ans;
    ans.reserve(n - k + 1);

    for (ll v : nums) {
      H2.insert({0, v});
      H1[v] = 0;
    }
    while (H2.size() <= x) {
      H2.insert({0, ll(-H2.size())});
    }
    ll count = 0;
    for (auto& p : H2) {
      if (count + x == H2.size()) {
        minPos = p;
        break;
      }
      count++;
    }
    sum = 0;

    ll l = 0, r = 0;  //[l, r)
    for (r = 0; r < k; r++) {
      Add(nums[r]);
    }
    ans.push_back(Query());
    for (; r < n; r++, l++) {
      Remove(nums[l]);
      Add(nums[r]);
      ans.push_back(Query());
    }
    return ans;
  }
};