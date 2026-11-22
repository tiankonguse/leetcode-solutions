
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 超出时间限制 881 / 884 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 100010, max6 = 2000010;

const ll BASE = 29, BASE1 = 100003, BASE2 = 100019;

class StringHash {
  ll h[max5];
  ll qpowCache[max5];
  const ll BASE;
  const ll MOD;

 public:
  StringHash(ll base, ll mod) : BASE(base), MOD(mod) {}
  ll H(int l, int r) {  // [l,r], 0 base
    if (l == 0) return h[r];
    ll pre = h[l - 1] * qpowCache[r - l + 1] % MOD;
    return (h[r] - pre + MOD) % MOD;
  }

  void Init(const vector<int>& str, int n) {
    qpowCache[0] = 1;
    for (int i = 1; i <= n; i++) {
      qpowCache[i] = (qpowCache[i - 1] * BASE) % MOD;
    }

    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre = (pre * BASE + str[i]) % MOD;
      h[i] = pre;
    }
  }
};
StringHash H1(BASE1, mod1e7);
StringHash H2(BASE1, mod1e7);

class Solution {
  unordered_map<int, int> mp;
  ll cnt = 0;
  void Add(int v) {  //
    if (mp[v] == 0) {
      cnt++;
    }
    mp[v]++;
    if (mp[v] == 0) {
      cnt--;
    }
  }
  void Remove(int v) {
    if (mp[v] == 0) {
      cnt++;
    }
    mp[v]--;
    if (mp[v] == 0) {
      cnt--;
    }
  }
  bool Empty() {
    return cnt == 0;  //
  }

 public:
  vector<int> countSuffix(vector<int>& nums, vector<int>& target) {
    int n = nums.size();
    int m = target.size();
    for (auto v : nums) {
      Remove(v);
    }
    vector<int> ans;
    ans.reserve(m - n + 1);
    if (n == 1) {
      for (auto v : target) {
        if (v == nums[0]) {
          ans.push_back(1);
        } else {
          ans.push_back(0);
        }
      }
      return ans;
    }
    H1.Init(nums, n);
    H2.Init(target, m);

    vector<int> preOrder(m, 0);
    for (int i = 1; i < m; i++) {
      if (target[i] <= target[i - 1]) {
        preOrder[i] = preOrder[i - 1];
      } else {
        preOrder[i] = i;
      }
    }

    auto Check = [&](const int l, const int r) -> bool {
      int len = r - l + 1;
      return H1.H(0, len - 1) == H2.H(l, r);
    };
    auto Solver = [&](const int l, const int r) -> int {
      int L = l, R = r + 1;  // [L, R)
      while (L < R) {
        int mid = (L + R) / 2;
        if (Check(l, mid)) {
          L = mid + 1;
        } else {
          R = mid;
        }
      }
      MyPrintf("l=%d r=%d L=%d, R=%d preOrder=%d\n", l, r, L, R, preOrder[r]);
      // [L, R) 相等
      if (preOrder[r] > R) {
        return 0;
      }
      int newL = max(l, preOrder[r]);
      if (R > r) {  // 全部相等
        return R - newL;
      } else {
        return R - newL + 1;
      }
    };

    Add(target[0]);
    int l = 0;
    for (int r = 1; r < m; r++) {  // [l, r]
      Add(target[r]);
      if (r < n - 1) continue;
      int tmpAns = 0;
      if (Empty()) {
        tmpAns = Solver(l, r);
      }
      ans.push_back(tmpAns);
      l++;
      Remove(target[l - 1]);  // 删除最左边的元素
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