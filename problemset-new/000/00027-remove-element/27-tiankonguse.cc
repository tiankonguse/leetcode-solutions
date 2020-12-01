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
  int removeElement(vector<int>& nums, int val) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      if (nums[i] == val) {
        nums[i] = nums[n - 1];
        n--;
        i--;
      }
    }
    return n;
  }
};

int main() {
  TEST_SMP2(Solution, removeElement, 2, vector<int>({3, 2, 2, 3}), 3);
  TEST_SMP2(Solution, removeElement, 5, vector<int>({0, 1, 2, 2, 3, 0, 4, 2}),
            2);

  return 0;
}
