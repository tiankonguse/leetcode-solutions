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
  vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
    int n = nums.size();
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + nums[i - 1];
    }

    vector<int> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; i++) {
      if (i == 1) {
        ans.push_back(sum[n] - n * nums[i - 1]);
      } else if (i == n) {
        ans.push_back(n * nums[i - 1] - sum[n]);
      } else {
        int tmp = 0;
        tmp += (sum[n] - sum[i - 1]) - (n - i + 1) * nums[i - 1];  //后缀
        tmp += i * nums[i - 1] - sum[i];
        ans.push_back(tmp);
      }
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, getSumAbsoluteDifferences, vector<int>({4, 3, 5}),
            vector<int>({2, 3, 5}));
  TEST_SMP1(Solution, getSumAbsoluteDifferences,
            vector<int>({24, 15, 13, 15, 21}), vector<int>({1, 4, 6, 8, 10}));

  return 0;
}
