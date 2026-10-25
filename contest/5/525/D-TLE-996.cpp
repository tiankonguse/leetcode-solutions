
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 996 / 999 个通过的测试用例

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
typedef long long ll;
class Solution {
 public:
  int countStaircase(vector<int>& nums) {
    const int n = nums.size();
    unordered_map<ll, vector<ll>> valPos;
    min_queue<pair<ll, ll>> minHeap;
    for (int i = 0; i < n; i++) {
      valPos[nums[i]].push_back(i);
    }
    for (auto& [val, ps] : valPos) {
      std::reverse(ps.begin(), ps.end());
      minHeap.push({ps.back(), val});
      MyPrintf("val=%lld, pos: ", val);
      for (int i = 0; i < ps.size(); i++) {
        MyPrintf("%lld ", ps[i]);
      }
      MyPrintf("\n");
    }
    ll ans = 0;
    vector<pair<ll, ll>> sta;
    sta.reserve(n);
    for (int i = 0; i < n; i++) {
      const ll v = nums[i];
      MyPrintf("begin i=%d, v=%lld\n", i, v);
      ll L = i, R = i;
      for (ll k = 1;; k++) {
        const ll expLen = (1 + k) * k / 2;
        if (i + expLen > n) {
          MyPrintf("i + expLen=%lld, n=%d, i + expLen > n, break\n", i + expLen, n);
          break;
        }
        if (minHeap.empty()) {
          MyPrintf("minHeap.empty(), break\n");
          break;
        }
        sta.push_back(minHeap.top());
        auto [pos, val] = minHeap.top();
        minHeap.pop();
        ll valCnt = valPos[val].size();
        MyPrintf("next pos=%lld, val=%lld valCnt=%lld\n", pos, val, valCnt);
        if (valCnt < k) {
          MyPrintf("valCnt=%lld < k=%lld, break\n", valCnt, k);
          break;
        }
        ll valLastPos = valPos[val][valCnt - k];
        R = max(R, valLastPos);
        MyPrintf("valLastPos=%lld, R=%lld\n", valLastPos, R);
        MyPrintf("k=%lld expLen=%lld, R-L+1=%lld\n", k, expLen, R - L + 1);
        if (expLen == (R - L + 1)) {
          MyPrintf("ans++\n");
          ans++;
        }
      }
      while (!sta.empty()) {
        minHeap.push(sta.back());
        sta.pop_back();
      }
      MyPrintf("minHeap.pop(), val=%lld pos=%lld\n", minHeap.top().second, minHeap.top().first);
      minHeap.pop();
      valPos[v].pop_back();
      if (!valPos[v].empty()) {
        MyPrintf("minHeap.push(), val=%lld, pos=%lld\n", v, valPos[v].back());
        minHeap.push({valPos[v].back(), v});
      }
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif