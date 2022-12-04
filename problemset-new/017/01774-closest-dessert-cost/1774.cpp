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
// reserve

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  int dis(int a, int b) {
    if (a >= b) {
      return a - b;
    } else {
      return b - a;
    }
  }
  int updateAns(int a, int b, int mid) {
    int lena = dis(a, mid);
    int lenb = dis(b, mid);
    if (lena < lenb) {
      return a;
    } else if (lena > lenb) {
      return b;
    } else {
      return a < b ? a : b;
    }
  }

 public:
  int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts,
                  int target) {
    int ans = baseCosts[0];

    vector<int> weight;  // 最多选择两个，复制一份，就是 01 背包了
    for (auto v : toppingCosts) {
      weight.push_back(v);
      weight.push_back(v);
    }

    vector<int> dp(2 * target + 1, 0);
    printf("next\n");
    for (auto a : baseCosts) {
      ans = updateAns(ans, a, target);

      if (a >= target) {
        continue;
      }

      int V = 2 * target;  // 由于可以超过容量，使用二倍法

      dp.clear();
      dp.resize(V + 1, 0);

      int n = weight.size();
      // 背包大小为 V，有 n 个物品
      for (int i = 1; i <= n; i++) {
        for (int j = V; j >= weight[i - 1]; j--) {
          dp[j] = max(dp[j], dp[j - weight[i - 1]] + weight[i - 1]);
        }
      }

      for (auto v : dp) {
        ans = updateAns(ans, v + a, target);
      }
    }

    return ans;
  }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
