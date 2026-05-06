
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
unordered_map<ll, int> cnt;
set<ll> s;
void Init() {
  if (!cnt.empty()) return;
  const ll maxn = 1000 * 1000 * 1000;
  for (ll i = 1; i <= 1000; i++) {
    for (ll j = i; j <= 1000; j++) {
      ll x = i * i * i + j * j * j;
      if (x > maxn) break;
      cnt[x]++;
      if (cnt[x] > 1 && s.count(x) == 0) {
        s.insert(x);
        MyPrintf("x=%lld cnt=%d\n", x, cnt[x]);
      }
    }
  }
  MyPrintf("s.size=%d\n", s.size());
}

class Solution {
 public:
  vector<int> findGoodIntegers(int n) {
    Init();
    vector<int> ans;
    for (auto x : s) {
      if (x <= n) {
        ans.push_back(x);
      } else {
        break;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const int n, const vector<int>& ans) {
  TEST_SMP1(Solution, findGoodIntegers, ans, n);  //
}

int main() {
  int n = 1000000000;
  vector<int> ans = {1, 2, 3};
  Test(n, ans);
  return 0;
}

#endif