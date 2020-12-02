/*************************************************************************
> File Name: regular-expression-matching.cpp
> Author: tiankonguse(skyyuan)
> Mail: i@tiankonguse.com
> Created Time: 2015年05月19日 星期二 22时19分48秒
***********************************************************************/

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
  map<pair<int, int>, int> m;
  int isMatch(string& s, string& p, int first, int second) {
    pair<int, int> nowPair(first, second);

    if (m.find(nowPair) != m.end()) {
      return m[nowPair];
    }

    if (first == s.size() && second == p.size()) {
      m[nowPair] = 1;
    } else if (first == s.size() && second < p.size()) {
      if (second + 1 < p.size() && p[second + 1] == '*') {
        m[nowPair] = isMatch(s, p, first, second + 2);
      } else {
        m[nowPair] = 0;
      }
    } else if (first < s.size() && second == p.size()) {
      m[nowPair] = 0;
    } else {
      if (s[first] == p[second] || p[second] == '.') {
        if (second + 1 < p.size() && p[second + 1] == '*') {
          if (isMatch(s, p, first + 1, second) ||
              isMatch(s, p, first, second + 2)) {
            m[nowPair] = 1;
          } else {
            m[nowPair] = 0;
          }
        } else {
          m[nowPair] = isMatch(s, p, first + 1, second + 1);
        }
      } else if (second + 1 < p.size() && p[second + 1] == '*') {
        m[nowPair] = isMatch(s, p, first, second + 2);
      } else {
        m[nowPair] = 0;
      }
    }

    return m[nowPair];
  }

 public:
  bool isMatch(string s, string p) {
    m.clear();
    int ans = isMatch(s, p, 0, 0);
    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, isMatch, true, std::string(""), std::string(""));
  TEST_SMP2(Solution, isMatch, true, std::string(""), std::string("a*"));
  TEST_SMP2(Solution, isMatch, false, std::string("aa"), std::string("a"));
  TEST_SMP2(Solution, isMatch, true, std::string("aa"), std::string("aa"));
  TEST_SMP2(Solution, isMatch, false, std::string("aaa"), std::string("aa"));
  TEST_SMP2(Solution, isMatch, true, std::string("aa"), std::string("a*"));
  TEST_SMP2(Solution, isMatch, true, std::string("aa"), std::string("a."));
  TEST_SMP2(Solution, isMatch, true, std::string("ab"), std::string(".*"));
  TEST_SMP2(Solution, isMatch, true, std::string("aab"), std::string("c*a*b"));

  return 0;
}
