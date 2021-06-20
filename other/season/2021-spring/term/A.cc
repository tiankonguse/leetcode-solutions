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
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
 public:
  int storeWater(vector<int>& bucket, vector<int>& vat) {
    int n = vat.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cnt += vat[i];
    }
    if (cnt == 0) return 0;
    int ans = 0x3f3f3f3f;
    for (int i = 10000; i >= 1; i--) {
      int tmp = i;
      for (int j = 0; j < n; j++) {
        if (vat[j] == 0) continue;
        int need = vat[j] / i;
        if (need * i < vat[j]) need++;
        tmp += max(0, need - bucket[j]);
      }
      ans = min(ans, tmp);
    }
    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
