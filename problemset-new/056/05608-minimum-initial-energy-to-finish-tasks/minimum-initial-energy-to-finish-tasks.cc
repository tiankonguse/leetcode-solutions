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
  int minimumEffort(vector<vector<int>>& tasks) {
    sort(tasks.begin(), tasks.end(),
         [](auto& a, auto& b) { return a[0] - a[1] < b[0] - b[1]; });

    ll p = 0, sum = 0;
    for (auto& task : tasks) {
      int m = max(task[0], task[1]);
      if (sum < m) {
        p += m - sum;
        sum += m - sum;
      }
      sum -= task[0];
    }

    return p;
  }
};

int main() {
  TEST_SMP1(Solution, minimumEffort, 8,
            vector<vector<int>>({{1, 2}, {2, 4}, {4, 8}}));
  TEST_SMP1(Solution, minimumEffort, 32,
            vector<vector<int>>({{1, 3}, {2, 4}, {10, 11}, {10, 12}, {8, 9}}));
  TEST_SMP1(
      Solution, minimumEffort, 27,
      vector<vector<int>>({{1, 7}, {2, 8}, {3, 9}, {4, 10}, {5, 11}, {6, 12}}));

  return 0;
}
