
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
  vector<int> findSubstring(const string& s, vector<string>& words) {
    int n = s.size();
    int k = words.size();
    vector<int> ans;
    ans.reserve(n);
    Init(s.c_str(), n);

    unordered_map<ll, int> cnt;
    for (const auto& w : words) {
      cnt[Hash(w.c_str(), 0, w.size())]++;
    }

    int len = words[0].size();
    for (int i = 0; i < len; i++) {
      unordered_map<ll, int> cur = cnt;
      for (int j = 0, p = i; p + len - 1 < n; j++, p += len) {
        ll hh = H(p, p + len - 1);
        cur[hh]--;
        if (cur[hh] == 0) {
          cur.erase(hh);
        }
        if (j < k - 1) {
          continue;
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
  vector<int> findSubstring(const string& s, vector<string>& words) {
    int n = s.size();
    int k = words.size();
    vector<int> ans;
    ans.reserve(n);
    Init(s.c_str(), n);

    unordered_map<ll, int> cnt;
    for (const auto& w : words) {
      cnt[Hash(w.c_str(), 0, w.size())]++;
    }

    int len = words[0].size();
    for (int i = 0; i < len; i++) {
      unordered_map<ll, int> cur = cnt;
      for (int j = 0, p = i; p + len - 1 < n; j++, p += len) {
        ll hh = H(p, p + len - 1);
        cur[hh]--;
        if (cur[hh] == 0) {
          cur.erase(hh);
        }
        if (j < k - 1) {
          continue;
        }
        if (cur.empty()) {
          ans.push_back(p - (k - 1) * len);
        }
        ll hh2 = H(p - (k - 1) * len, p - (k - 1) * len + len - 1);
        cur[hh2]++;
        if (cur[hh2] == 0) {
          cur.erase(hh2);
        }
      }
    }
    sort(ans.begin(), ans.end());
    return ans;
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
        }
        if (cur.empty()) {
          ans.push_back(p - (k - 1) * len);
        }
        ll hh2 = H(p - (k - 1) * len, p - (k - 1) * len + len - 1);
        cur[hh2]++;
        if (cur[hh2] == 0) {
          cur.erase(hh2);
        }
      }
    }
    sort(ans.begin(), ans.end());
    return ans;
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