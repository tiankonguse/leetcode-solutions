
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

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

ll Hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}
class Solution {
 public:
  int longestValidSubstring(const string& word, vector<string>& forbidden) {
    int n = word.size();
    Init(word.c_str(), n);
    unordered_set<ll> h;
    unordered_set<int> lens;
    for (const auto& s : forbidden) {
      int m = s.size();
      ll hash = Hash(s.c_str(), 0, m);
      h.insert(hash);
      lens.insert(m);
    }
    int l = 0, r = 0;
    int ans = 0;
    auto updateAdd = [&](auto& v) {};
    auto updateDel = [&](auto& v) {};
    auto shouldMove = [&](auto& lv, auto& rv) -> bool {
      for (auto k : lens) {
        int R = r - 1;
        int L = R - k + 1;
        if (L < l) continue;
        if (h.count(H(L, R))) {
          return true;
        }
      }
      return false;
    };
    while (r < n) {
      auto& rv = word[r];
      r++;
      updateAdd(rv);  // 第一步：移动右指针

      while (l < r && shouldMove(word[l], rv)) {  // 第二步：移动左指针
        auto& lv = word[l];
        l++;
        updateDel(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
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