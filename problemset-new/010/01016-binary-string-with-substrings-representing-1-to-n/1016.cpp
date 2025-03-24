
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
class Solution {
  int MaxBits(int n) {
    int i = 0;
    while (n) {
      n >>= 1;
      ++i;
    }
    return i;
  }
  unordered_set<ll> h;
  bool AllZero(const string& s) {
    for (auto c : s) {
      if (c != '0') {
        return false;
      }
    }
    return true;
  }
  void queryString(const string& s, int N, int k) {
    ll pre = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      pre = pre * 2 + s[i] - '0';
      if (i < k - 1) continue;
      if (s[i - k + 1] == '1' && pre <= N) {
        h.insert(pre);
      }
      ll v = s[i - k + 1] - '0';
      pre -= v << (k - 1);
    }
  }

 public:
  // 只需要判断长度为 k 和长度为 k-1 窗口的子串是否都存在即可
  // 逻辑： [2^k, 2^(k+1)-1] 前面分别追加 1 和 0，就得到了 [2^(k+1), 2^(k+2)-1]。
  // 因此，如果 [2^(k+1), 2^(k+2)-1] 都存在，那么 [2^k, 2^(k+1)-1] 也一定存在。
  bool queryString(const string& s, int n) {
    if (AllZero(s)) return false;
    if (n == 1) return true;

    int k = MaxBits(n);
    queryString(s, n, k);
    if (k == 2) {
      return h.size() == n - 1;
    }
    queryString(s, n, k - 1);
    return h.size() == n - (1 << (k - 2)) + 1;
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