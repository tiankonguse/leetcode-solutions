#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T> >;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  map<int, int> Cal(string word) {
    map<char, int> m1;
    for (auto c : word) {
      m1[c]++;
    }

    map<int, int> ans;
    for (auto p : m1) {
      ans[p.second]++;
    }
    return ans;
  }

  set<char> Cal2(string word) {
    set<char> ans;
    for (auto c : word) {
      ans.insert(c);
    }
    return ans;
  }

 public:
  bool closeStrings(string word1, string word2) {
    return Cal(word1) == Cal(word2) && Cal2(word1) == Cal2(word2);
  }
};

int main() {
  TEST_SMP2(Solution, closeStrings, true, string("abc"), string("bca"));
  TEST_SMP2(Solution, closeStrings, false, string("a"), string("aa"));
  TEST_SMP2(Solution, closeStrings, true, string("cabbba"), string("abbccc"));
  TEST_SMP2(Solution, closeStrings, false, string("cabbba"), string("aabbss"));
  TEST_SMP2(Solution, closeStrings, false, string("uau"), string("ssx"));

  return 0;
}