
template <class T>
inline bool ckmin(T &x, const T &y) {
  return x > y ? x = y, 1 : 0;
}
template <class T>
inline bool ckmax(T &x, const T &y) {
  return x < y ? x = y, 1 : 0;
}

#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
// int init = []() { return cin.tie(nullptr)->sync_with_stdio(false), 0; }();
#else

#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const ll kMaxK = 1000001;
ll C(int n, int m) {
  m = min(m, n - m);
  ll res = 1;
  for (int i = 1; i <= m; ++i) {
    res = res * (n - m + i) / i;
    if (res >= kMaxK) return kMaxK;
  }
  return res;
}

ll C2(int n, int m) {
  m = min(m, n - m);
  ll res = 1;
  for (int i = 1; i <= m; ++i) {
    res = res * (n - i + 1) / i;
    if (res >= kMaxK) return kMaxK;
  }
  return res;
}

class Solution {
  map<char, int> freq;
  ll CC(int n) {
    ll res = 1;
    for (auto [k, v] : freq) {
      res *= C(n, v);
      if (res >= kMaxK) return kMaxK;
      n -= v;
    }
    return res;
  }
  string halfAns = "";
  void kthPermutation(int n, long long k) {  // 输入保证非空
    MyPrintf("n = %d, k = %lld\n", n, k);
    for (auto [ch, count] : freq) {
      MyPrintf("ch = %c, count = %d\n", ch, count);
    };

    halfAns.clear();
    halfAns.reserve(n);
    // 逆序计算总排列数
    ll total = CC(n);  // 之前已经计算的排列数
    if (total < k) {
      return;  // 不足 k 个
    }
    const int nn = n;
    for (int i = 0; i < nn; i++) {
      for (auto &[ch, count] : freq) {
        if (count == 0) continue;
        count--;
        n--;
        ll permutations = CC(n);  // 剩余字符的排列数;
        if (k <= permutations) {
          halfAns.push_back(ch);
          break;
        } else {
          count++;
          n++;
          k -= permutations;
        }
      }
    }

    MyPrintf("res = %s\n", halfAns.c_str());
    for (auto [ch, count] : freq) {
      MyPrintf("ch = %c, count = %d\n", ch, count);
    }
    return;
  }

 public:
  string smallestPalindrome(const string &s, int k) {
    const int n = s.length();
    if (n == 1) {
      if (k == 1) {
        return s;
      } else {
        return "";
      }
    }

    freq.clear();
    for (char c : s) {
      freq[c]++;
    }
    char oddVal = 'a';
    for (auto &[c, count] : freq) {
      if (count % 2 == 1) {
        oddVal = c;
        count--;
      }
      count /= 2;
    }

    kthPermutation(n / 2, k);
    if (halfAns.empty()) {
      return "";  // 不足 k 个
    }
    string ans = halfAns;
    ans.reserve(n);
    if (n % 2 == 1) {
      ans.push_back(oddVal);
    }
    reverse(halfAns.begin(), halfAns.end());
    ans.append(halfAns);
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif