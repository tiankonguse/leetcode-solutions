
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  ll maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
    // 枚举子数组左端点，看看有多少个合法的右端点
    vector<vector<ll>> groups(n + 1);
    for (auto& v : conflictingPairs) {
      int a = v[0];
      int b = v[1];
      if (a > b) {
        swap(a, b);
      }
      groups[a].push_back(b);
    }
    for (auto& v : groups) {
      sort(v.begin(), v.end());
    }

    ll sum = 0;  // 不删除可以得到的最大子数组个数
    min_queue<ll> minQue;
    vector<ll> secondMinNum(n + 2, 0);
    minQue.push(n + 1);  // 至少存在一个边界
    minQue.push(n + 1);  // 至少存在一个边界
    for (int l = n; l >= 1; l--) {
      for (auto v : groups[l]) {
        minQue.push(v);
      }
      ll r0 = minQue.top();  // [l, r)
      sum += r0 - l;

      minQue.pop();
      ll r1 = minQue.top();
      minQue.push(r0);

      secondMinNum[r0] += r1 - r0;
    }
    ll maxAdd = 0;
    for (auto v : secondMinNum) {
      maxAdd = max(maxAdd, v);
    }
    return sum + maxAdd;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif