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
  vector<int> searchRange(vector<int>& nums, int target) {
    auto itLeft = std::lower_bound(nums.begin(), nums.end(), target);
    if (itLeft == nums.end() || *itLeft != target) {
      return {-1, -1};
    }
    auto itRight = std::upper_bound(nums.begin(), nums.end(), target);
    vector<int> ans;
    ans.push_back(itLeft - nums.begin());
    ans.push_back(itRight - nums.begin() - 1);
    return ans;
  }
};

int main() {
  TEST_SMP2(Solution, searchRange, vector<int>({3, 4}),
            vector<int>({5, 7, 7, 8, 8, 10}), 8);
  TEST_SMP2(Solution, searchRange, vector<int>({-1, -1}),
            vector<int>({5, 7, 7, 8, 8, 10}), 6);
  TEST_SMP2(Solution, searchRange, vector<int>({-1, -1}), vector<int>({}), 0);
  TEST_SMP2(Solution, searchRange, vector<int>({3, 3}),
            vector<int>({5, 7, 7, 8, 9, 10}), 8);

  return 0;
}
