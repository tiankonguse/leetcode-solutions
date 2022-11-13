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
 public:
  int countConsistentStrings(string allowed, vector<string>& words) {
    unordered_set<char> s;
    for (auto c : allowed) {
      s.insert(c);
    }

    int ans = 0;
    for (auto& str : words) {
      bool have = true;
      for (auto c : str) {
        if (s.count(c) == 0) {
          have = false;
          break;
        }
      }
      if (have) {
        ans++;
      }
    }
    return ans;
  }
};
int main() {
  TEST_SMP2(Solution, countConsistentStrings, 2, std::string("ab"),
            vector<string>({"ad", "bd", "aaab", "baa", "badab"}));
  TEST_SMP2(Solution, countConsistentStrings, 7, std::string("abc"),
            vector<string>({"a", "b", "c", "ab", "ac", "bc", "abc"}));
  TEST_SMP2(Solution, countConsistentStrings, 4, std::string("cad"),
            vector<string>({"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"}));

  return 0;
}
