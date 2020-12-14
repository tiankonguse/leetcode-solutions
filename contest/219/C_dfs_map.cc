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
  vector<int> sum;
  int dfs(int l, int r) {
    pair<int, int> p = {l, r};
    if (m.count(p)) {
      return m[p];
    }

    if (l == r) {
      return m[p] = 0;
    }

    int left_val = sum[r] - sum[l] - dfs(l + 1, r);
    int right_val = sum[r - 1] - sum[l - 1] - dfs(l, r - 1);
    return m[p] = max(left_val, right_val);
  }

 public:
  int stoneGameVII(vector<int>& str) {
    int n = str.size();

    sum.resize(n + 1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + str[i - 1];
    }

    return dfs(1, n);
  }
};

int main() {
  TEST_SMP1(Solution, stoneGameVII, 6, vector<int>({5, 3, 1, 4, 2}));
  TEST_SMP1(Solution, stoneGameVII, 122,
            vector<int>({7, 90, 5, 1, 100, 10, 10, 2}));

  return 0;
}
