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
  string getSmallestString(int n, int k) {
    string ans;
    ans.resize(n, 'a');
    // x + 1 + y = n
    // x * 1 + z * 1 + 26 * y = k

    int y = (k - n) / 25;
    int z = (k - n) % 25 + 1;

    int i;
    for (i = n - 1; i >= 0 && y > 0; i--, y--) {
      ans[i] = 'z';
    }
    if (i >= 0) {
      ans[i] = 'a' + z - 1;
    }

    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, getSmallestString, string("aay"), 3, 27);
  TEST_SMP2(Solution, getSmallestString, string("aaszz"), 5, 73);
  TEST_SMP2(Solution, getSmallestString, string("a"), 1, 1);
  TEST_SMP2(Solution, getSmallestString, string("z"), 1, 26);
  TEST_SMP2(Solution, getSmallestString, string("aa"), 2, 2);
  TEST_SMP2(Solution, getSmallestString, string("zz"), 2, 56);
  TEST_SMP2(Solution, getSmallestString, string("ab"), 2, 3);
  TEST_SMP2(Solution, getSmallestString, string("aaa"), 3, 3);
  TEST_SMP2(Solution, getSmallestString, string("aab"), 3, 4);
  TEST_SMP2(Solution, getSmallestString, string("aaz"), 3, 28);
  TEST_SMP2(Solution, getSmallestString, string("abz"), 3, 29);

  return 0;
}
