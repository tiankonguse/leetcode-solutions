#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  vector<int> next;
  void get_next(const char* pat) {
    for (int i = 1, k; pat[i]; ++i) {
      for (k = next[i - 1]; k >= 0 && pat[i] != pat[k + 1]; k = next[k])
        ;
      if (pat[k + 1] == pat[i]) next[i] = k + 1;
    }
  }
  int kmp(const char* str, const char* pat) {
    next.resize(strlen(pat) + 1, -1);
    get_next(pat);
    int i = 0, j = 0;
    while (str[i] && pat[j]) {
      if (pat[j] == str[i]) {
        ++i;
        if (!pat[++j]) {
          return i - j;
        }
      } else if (j == 0)
        ++i;
      else
        j = next[j - 1] + 1;
    }
    return -1;
  }

 public:
  int strStr(string haystack, string needle) {
    if (needle.length() == 0) return 0;
    return kmp(haystack.c_str(), needle.c_str());
  }
};

int main() {
  TEST_SMP2(Solution, strStr, 2, string("hello"), string("ll"));
  TEST_SMP2(Solution, strStr, -1, string("aaaaa"), string("bba"));
  TEST_SMP2(Solution, strStr, 0, string("aaaaa"), string(""));

  return 0;
}
