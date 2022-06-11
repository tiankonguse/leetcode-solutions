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
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  ll GetSum(int n, ll value) {
    if (value >= n) {
      ll firstVal = value - n + 1;
      return (firstVal + value) * n / 2;
    } else {
      return (value + 1) * value / 2 + (n - value);
    }
  }
  bool check(ll n, ll index, ll maxSum, ll value) {
    ll sum = -value;

    // sum[0, index]
    sum += GetSum(index + 1, value);

    // sum[index, n-1]
    sum += GetSum(n - index, value);

    if (sum > maxSum) {
      return false;
    } else {
      return true;
    }
  }

 public:
  int maxValue(int n, int index, int maxSum) {
    ll low = 1, high = maxSum + 1;
    while (low < high) {
      ll mid = (low + high + 1) / 2;
      if (check(n, index, maxSum, mid)) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    return low;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
