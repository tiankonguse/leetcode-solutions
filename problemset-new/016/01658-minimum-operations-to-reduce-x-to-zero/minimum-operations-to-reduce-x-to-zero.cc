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
  unordered_map<ll, pair<int, int>> m;
  int ans;
  void update(int i, ll d) {
    if (m.count(d) && m[d].second > 0) {
      int tmpAns = m[d].first + i;
      if (ans == -1) {
        ans = tmpAns;
      } else {
        ans = min(ans, tmpAns);
      }
    }
  }

 public:
  int minOperations(const vector<int>& nums, int x) {
    //  也可以使用 map 的 low_bound 也可以做这道题
    // 这里使用 O(1) 的方法
    m[0] = {0, 1};
    ll sum = 0;
    for (int i = nums.size() - 1; i >= 0; i--) {
      sum += nums[i];
      if (m.count(sum) == 0) {
        m[sum] = {nums.size() - i, 1};
      } else {
        m[sum].second++;
      }
    }

    ans = -1;

    ll sumPre = 0;
    update(0, x);
    for (int i = 0; i < nums.size(); i++) {
      m[sum].second--;
      sum -= nums[i];
      sumPre += nums[i];
      update(i + 1, x - sumPre);
    }

    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, minOperations, 2, vector<int>({1, 1, 4, 2, 3}), 5);
  TEST_SMP2(Solution, minOperations, -1, vector<int>({5, 6, 7, 8, 9}), 4);
  TEST_SMP2(Solution, minOperations, 5, vector<int>({3, 2, 20, 1, 1, 3}), 10);

  return 0;
}