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
  int dis(int a, int b) {
    if (a > b) {
      return a - b;
    } else {
      return b - a;
    }
  }

 public:
  int minimumDeviation(vector<int>& nums) {
    set<int> s;
    for (auto v : nums) {
      if (v % 2 == 0) {
        s.insert(v);
      } else {
        s.insert(v * 2);
      }
    }
    int ans = *s.rbegin() - *s.begin();

    while (*s.rbegin() % 2 == 0) {
      int v = *s.rbegin();
      s.erase(v);
      s.insert(v / 2);
      ans = min(ans, *s.rbegin() - *s.begin());
    }

    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, minimumDeviation, 1, vector<int>({1, 2, 3, 4}));
  TEST_SMP1(Solution, minimumDeviation, 3, vector<int>({4, 1, 5, 20, 3}));
  TEST_SMP1(Solution, minimumDeviation, 3, vector<int>({2, 10, 8}));
  TEST_SMP1(Solution, minimumDeviation, 7, vector<int>({9, 4, 3, 6, 2}));
  return 0;
}
