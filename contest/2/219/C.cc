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

int dp[max3][max3];
int sum[max3];

class Solution {
 public:
  int stoneGameVII(vector<int>& str) {
    int n = str.size();

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + str[i - 1];
    }

    for (int i = n; i >= 1; i--) {
      for (int j = i; j <= n; j++) {
        if (i == j) {
          dp[i][j] = 0;
          continue;
        }
        ll left_val = sum[j] - sum[i] - dp[i + 1][j];
        ll right_val = sum[j - 1] - sum[i - 1] - dp[i][j - 1];
        dp[i][j] = max(left_val, right_val);
      }
    }

    return dp[1][n];
  }
};

int main() {
  TEST_SMP1(Solution, stoneGameVII, 6, vector<int>({5, 3, 1, 4, 2}));
  TEST_SMP1(Solution, stoneGameVII, 122,
            vector<int>({7, 90, 5, 1, 100, 10, 10, 2}));

  return 0;
}
