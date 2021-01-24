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
  int maximumWealth(const vector<vector<int>>& accounts) {
    int ans = 0;
    for (int i = 0; i < accounts.size(); i++) {
      int sum = 0;
      for (auto v : accounts[i]) {
        sum += v;
      }
      ans = max(sum, ans);
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, maximumWealth, 6,
            vector<vector<int>>({{1, 2, 3}, {3, 2, 1}}));
  TEST_SMP1(Solution, maximumWealth, 10,
            vector<vector<int>>({{1, 5}, {7, 3}, {3, 5}}));
  TEST_SMP1(Solution, maximumWealth, 17,
            vector<vector<int>>({{2, 8, 7}, {7, 1, 3}, {1, 9, 5}}));
  return 0;
}
