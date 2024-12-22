
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
int dp[1010][1010][2][2];
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
  // 最后一个字符不修改的情况下，0和1最多出现1次K子串时（K>=3），是否有答案
  int Dfs(const int n, const int m, int* p) {  //
    if (n < 0) return 1;
    // if (m < 0 || p[0] < 0 || p[1] < 0) {
    //   printf("n=%d m=%d p0=%d p1=%d\n", n, m, p[0], p[1]);
    //   assert(0);
    // }

    int& ret = dp[n][m][p[0]][p[1]];
    if (ret != -1) return ret;
    ret = 0;
    const int c = s[n] - '0';
    const int l = prePos[n];
    const int r = n;
    const int len = r - l + 1;
    if (len < K) {  // 当前连续子串满足不大于 K
      return ret = Dfs(l - 1, m, p);
    } else if (len == K) {
      if (p[c] > 0) {  // 不修改，消耗 p
        p[c]--;
        ret += Dfs(l - 1, m, p);
        p[c]++;
        if (ret) {
          return ret;  // 找到答案
        }
      }
      if (m > 0) {  // 修改，消耗 m
        ret += Dfs(l - 1, m - 1, p);
        if (ret) {
          return ret;  // 找到答案
        }
      }
      return ret;
    } else if (len == K + 1) {
      if (m > 0) {  // 修改，消耗 m
        ret += Dfs(l - 1, m - 1, p);
        if (ret) {
          return ret;  // 找到答案
        }
      }
      return ret;
    } else {  // len > K+1
      if (m < 0) return ret = 0;

      if (p[c] > 0) {  // 修改，消耗 p
        p[c]--;
        ret += Dfs(r - K - 1, m - 1, p);
        p[c]++;
        if (ret) {
          return ret;  // 找到答案
        }
      }

      ret += Dfs(r - K, m - 1, p);
      if (ret) {
        return ret;  // 找到答案
      }
      return ret;
    }
    return ret;
  }
  int Cal(int n, int k) {
    if (n <= k) return 0;
    if (n == k + 1) return 1;
    n++, k++;
    return (n + k - 1) / k;
  }
  bool Check(int k) {  // 至多 1 个k
    if (k == 1) return false;
    memset(dp, -1, sizeof(dp));
    int p[2] = {1, 1};
    K = k + 1;  // 最多一次 k + 1, 答案就是 k
    if (Dfs(n - 1, numOps, p)) {
      return true;
    }

    K = k;  // 任意次 k

    int m = numOps;
    char preVal = s[0];
    int preNum = 0;
    for (int i = 0; i < n; i++) {
      char c = s[i];
      if (c == preVal) {
        preNum++;
      } else {
        int num = Cal(preNum, k);
        m -= num;
        preVal = c;
        preNum++;
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
    if (Check1(0) || Check1(1)) {
      return 1;
    }
    Init();
    int l = 2, r = n;  //[l, r)
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