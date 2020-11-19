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
  int minOperations(const vector<int>& nums, int x) {
    int ans = -1;

    ll sum = 0;
    for (auto v : nums) {
      sum += v;
    }
    if(sum < x){
        return -1;
    }
    ll target = sum - x;

    int left = 0, right = 0;
    ll tmpSum = 0;
    while (right < nums.size()) {
      if (right < nums.size()) {
        tmpSum += nums[right];
        right++;
      }

      while (tmpSum > target) {
        tmpSum -= nums[left];
        left++;
      }

      if (tmpSum == target) {
        ans = std::max(ans, right - left);
      }
    }

    if (ans != -1) {
      ans = nums.size() - ans;
    }

    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, minOperations, 2, vector<int>({1, 1, 4, 2, 3}), 5);
  TEST_SMP2(Solution, minOperations, -1, vector<int>({5, 6, 7, 8, 9}), 4);
  TEST_SMP2(Solution, minOperations, 5, vector<int>({3, 2, 20, 1, 1, 3}), 10);
  TEST_SMP2(Solution, minOperations, -1, vector<int>({1, 1}), 3);

  return 0;
}