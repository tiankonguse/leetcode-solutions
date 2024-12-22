
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
const int N = 1e5 + 10;
int dp2[N][2];
// vector<vector<int>> dp2;
class Solution {
  bool Check1(int pre) {
    int num = numOps;
    for (auto c : s) {
      int v = c - '0';
      if (v == pre) {
        num--;
        if (num < 0) return false;
        pre = 1 - pre;
      } else {
        pre = v;
      }
    }
    return true;
  }

  int Dfs2(const int n, const int v) {
    if (n < 0) return 0;
    int& ret = dp2[n][v];
    if (ret != -1) return ret;
    ret = n + 1;

    int dif = 0;
    for (int l = n; l >= 0 && n - l + 1 <= 2; l--) {
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

  bool Check2() {
    memset(dp2, -1, 2 * (n + 1) * sizeof(int));
    for (int v = 0; v <= 1; v++) {
      if (Dfs2(n - 1, v) <= numOps) return true;
    }
    return false;
  }
  vector<int> prePos;  // 当前字符连续出现的最远位置
  void Init() {
    int p[2] = {-1, -1};
    prePos.resize(n);
    for (int i = 0; i < n; i++) {
      int c = s[i] - '0';
      if (p[c] == -1) {
        prePos[i] = i;  // 是自身
        p[c] = i;       // 更新 c 的位置
        p[1 - c] = -1;  // 相反的字符不存在
      } else {
        prePos[i] = p[c];
        p[1 - c] = -1;  // 相反的字符不存在
      }
    }
  }

  int Cal(int n, int k) { return n / (k + 1); }
  bool Check(int k) {
    K = k;  // 任意次 k

    int m = numOps;
    char preVal = s[0];
    int preNum = 0;
    for (int i = 0; i < n; i++) {
      const char c = s[i];
      if (c == preVal) {
        preNum++;
      } else {
        int num = Cal(preNum, k);
        m -= num;
        preVal = c;
        preNum = 1;
      }
    }
    if (preNum > k) {
      int num = Cal(preNum, k);
      m -= num;
    }

    return m >= 0;
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
    if (Check1(0) || Check1(1)) return 1;
    if (Check2()) return 2;
    Init();
    int l = 3, r = n;  //[l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      if (Check(mid)) {
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