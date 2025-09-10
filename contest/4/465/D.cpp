
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

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
int tick = 0;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    // c.clear();
    c.resize(n + 100, 0);
    // times.clear();
    times.resize(n + 100, 0);
  }
  void NextTick() { tick++; }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      if (times[x] == tick) {
        s = (s + c[x]) % mod;
      }
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) {
    if (l > r) return 0;
    return (Query(r) - Query(l - 1) + mod) % mod;
  }

  void Add(int x, ll v) {
    while (x <= n) {
      if (times[x] != tick) {
        times[x] = tick;
        c[x] = 0;
      }
      c[x] = (c[x] + v) % mod;
      x += Lowbit(x);
    }
  }

 private:
  inline int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  vector<ll> times;
  int n;
};
TreeArray treeArray;
class Solution {
 public:
  int totalBeauty(vector<int>& nums) {
    int n = nums.size();
    int maxVal = *max_element(nums.begin(), nums.end());
    vector<vector<int>> valLCM(maxVal + 1);
    for (int i = 0; i < n; i++) {
      const int val = nums[i];
      for (int j = 1; j * j <= val; j++) {
        if (val % j == 0) {
          valLCM[j].push_back(val);
          if (j != val / j) {
            valLCM[val / j].push_back(val);
          }
        }
      }
    }

    ll ans = 0;
    vector<ll> dp(maxVal + 1, 0);
    treeArray.Init(maxVal + 1);
    for (int v = maxVal; v > 0; v--) {
      treeArray.NextTick();
      for (auto val : valLCM[v]) {
        const ll cnt = treeArray.Query(1, val - 1) + 1;
        treeArray.Add(val, cnt);
      }
      dp[v] = (dp[v] + treeArray.Query(1, maxVal)) % mod;
      for (int mul = 2 * v; mul <= maxVal; mul += v) {
        dp[v] = (dp[v] - dp[mul] + mod) % mod;
      }
      ans = (ans + dp[v] * v) % mod;
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