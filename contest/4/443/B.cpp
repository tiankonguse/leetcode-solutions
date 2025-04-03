
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

const ll mod1e7 = 1000000007, mod1e9 = 1000000009;
const ll mod1e79 = mod1e7 * mod1e9;
const ll mod = mod1e9;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max3];
ll qpowCache[max3];

ll HH(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod;
  return (h[r] - pre + mod) % mod;
}

ll Hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod;
  }
  return pre;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod;
    h[i] = pre;
  }
}

unordered_set<ll> H[max3];
int dp[max3];
string S;
string T;
class Solution {
  // 中心在 t 上，在 s 上尝试匹配
  // s[a...b] t[c...c] t[b...a]]
  int Solver(string& s, const string& t) {  //
    int n = s.size();
    int m = t.size();
    int nm = max(n, m) + 1;
    // MyPrintf("s=%s\nt=%s\n", s.c_str(), t.c_str());

    for (int i = 0; i <= nm; i++) {
      H[i].clear();
    }
    // std::reverse(s.begin(), s.end());
    for (int i = 0; i < n; i++) {
      ll pre = 0;
      for (int j = i; j < n; j++) {
        pre = (pre * BASE + (s[j] - 'a' + 1)) % mod;
        H[j - i + 1].insert(pre);
      }
    }
    // std::reverse(s.begin(), s.end());  // 还原

    // 预处理出 t 每个位置的可以回文匹配的最长子串
    Init(t.c_str(), m);
    fill_n(dp, m + 1, 0);
    for (int i = 0; i < m; i++) {
      int l = i, r = m;  // [l, r)
      while (l < r) {
        int mid = (l + r) / 2;
        if (mid - i + 1 <= n && H[mid - i + 1].count(HH(i, mid))) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      dp[i] = l - i;
    }

    // 枚举中心位置
    int ans = 0;
    for (int i = 0; i < m; i++) {  // 枚举中心位置
      int l = i;
      int r = i;
      while (l >= 0 && r < m && t[l] == t[r]) {
        int tmp = r - l + 1 + 2 * dp[r + 1];
        ans = max(ans, tmp);
        l--;
        r++;
      }
    }

    return ans;
  }
  void Fix(const string& s, string& ret) {
    ret.clear();
    ret.reserve(s.size() * 2 + 2);
    ret.push_back('z' + 1);
    for (auto c : s) {
      ret.push_back(c);
      ret.push_back('z' + 1);
    }
  }
  int Self(const string& t) {
    int m = t.size();
    // 枚举中心位置
    int ans = 0;
    for (int i = 0; i < m; i++) {  // 枚举中心位置
      int l = i;
      int r = i;
      while (l >= 0 && r < m && t[l] == t[r]) {
        int tmp = r - l + 1;
        if (tmp > ans) {
          // MyPrintf("tmp=%d t[%d:%d]=%s dp[r+1]=%d \n", tmp, l, r, t.substr(l, r - l + 1).c_str(), dp[r + 1]);
          // MyPrintf("t[%d:%d]=%s\n", r + 1, r + dp[r + 1], t.substr(r + 1, dp[r + 1]).c_str());
          ans = max(ans, tmp);  // 后缀回文匹配
        }
        l--;
        r++;
      }
    }

    return ans;
  }

 public:
  int longestPalindrome(const string& s, const string& t) {
    Fix(s, S);
    Fix(t, T);
    // MyPrintf("S=%s\n", S.c_str());
    // MyPrintf("T=%s\n", T.c_str());
    std::reverse(S.begin(), S.end());
    int ans1 = Solver(S, T);
    // int ans2 = Self(S);
    // std::reverse(T.begin(), T.end());
    int ans2 = Solver(T, S);
    int ans = max(ans1, ans2);
    // MyPrintf("ans1=%d ans2=%d\n", ans1, ans2);
    return ans / 2;
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