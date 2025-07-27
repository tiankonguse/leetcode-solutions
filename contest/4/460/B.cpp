
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
class Solution {
  enum { LCT = 0, LC = 1, L = 2, CT = 1, T = 2 };

 public:
  long long numOfSubsequences(const string& s) {
    int n = s.size();
    vector<vector<ll>> pre(n + 2, vector<ll>(3, 0));
    for (int i = 1; i <= n; i++) {
      const char c = s[i - 1];
      pre[i] = pre[i - 1];
      if (c == 'L') {
        pre[i][L]++;
      } else if (c == 'C') {
        pre[i][LC] += pre[i - 1][L];
      } else if (c == 'T') {
        pre[i][LCT] += pre[i - 1][LC];
      } else {
        // do nothing
      }
    }
    vector<vector<ll>> suf(n + 2, vector<ll>(3, 0));
    for (int i = n; i >= 1; i--) {
      const char c = s[i - 1];
      suf[i] = suf[i + 1];
      if (c == 'L') {
        suf[i][LCT] += suf[i + 1][CT];
      } else if (c == 'C') {
        suf[i][CT] += suf[i + 1][T];
      } else if (c == 'T') {
        suf[i][T]++;
      } else {
        // do nothing
      }
    }
    const ll base = pre[n][LCT];  // 不含插入字符 LCT 的个数
    ll ans = base;
    for (int i = 1; i <= n + 1; i++) {                   // 在 i 之前插入 LCT 其中一个字符
      ans = max(ans, base + suf[i][CT]);                 // 插入 L
      ans = max(ans, base + pre[i - 1][L] * suf[i][T]);  // 插入 C
      ans = max(ans, base + pre[i - 1][LC]);             // 插入 T
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