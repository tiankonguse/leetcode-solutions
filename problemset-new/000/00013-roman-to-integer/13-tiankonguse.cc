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

/*
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
class Solution {
  int X(char c) {
    switch (c) {
      case 'I':
        return 1;
      case 'V':
        return 5;
      case 'X':
        return 10;
      case 'L':
        return 50;
      case 'C':
        return 100;
      case 'D':
        return 500;
      case 'M':
        return 1000;
      default:
        return 0;
    }
  }

 public:
  int romanToInt(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      if (i + 1 < n && X(s[i]) < X(s[i + 1])) {
        ans -= X(s[i]);
      } else {
        ans += X(s[i]);
      }
    }

    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, romanToInt, 3, string("III"));
  TEST_SMP1(Solution, romanToInt, 4, string("IV"));
  TEST_SMP1(Solution, romanToInt, 9, string("IX"));
  TEST_SMP1(Solution, romanToInt, 58, string("LVIII"));
  TEST_SMP1(Solution, romanToInt, 1994, string("MCMXCIV"));
  TEST_SMP1(Solution, romanToInt, 49, string("XLIX"));
  TEST_SMP1(Solution, romanToInt, 999, string("CMXCIX "));

  return 0;
}
