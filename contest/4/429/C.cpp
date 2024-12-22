
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
int dp2[1010][2];
class Solution {
  int Dfs2(const int n, const int v) {
    if (n < 0) return 0;
    int& ret = dp2[n][v];
    if (ret != -1) return ret;
    ret = n + 1;

    int dif = 0;
    for (int l = n; l >= 0 && n - l + 1 <= K; l--) {
      const int V = s[l] - '0';
      if (V != v) {
        dif++;
      }
      int tmp = Dfs2(l - 1, 1 - v);
      // 选择 i+1 个 v
      ret = min(ret, dif + tmp);
      // printf("dp2: n=%d v=%d l=%d dif=%d tmp=%d newRet=%d\n", n, v, l, dif,
      // tmp,
      //        ret);
    }
    // printf("dp2: n=%d v=%d ret=%d\n", n, v, ret);

    return ret;
  }

  bool Check2(int mid) {
    memset(dp2, -1, sizeof(dp2));
    K = mid;
    return Dfs2(n - 1, 0) <= numOps || Dfs2(n - 1, 1) <= numOps;
  }
  int K;
  string s;
  int numOps;
  int n;

 public:
  int minLength(string s_, int numOps_) {
    s.swap(s_);
    numOps = numOps_;
    n = s.size();
    int l = 1, r = n;  //[l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check2(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};
#ifdef USACO_LOCAL_JUDGE

void Test(const string s_, int numOps_, const int ans) {
  TEST_SMP2(Solution, minLength, ans, s_, numOps_);
}

int main() {
  Test("000001", 1, 2);
  return 0;
}

#endif