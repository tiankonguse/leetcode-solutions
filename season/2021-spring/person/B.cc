#include "base.h"



typedef long long ll;
class Solution {
  ll mymin(ll a, ll b ){
    return a<b?a:b;
  }
  int dfs(ll n, ll x, ll y, ll start) {
    // printf("base n=%lld\n", n);
    while (true) {
      // printf("n=%lld x=%lld y=%lld start=%lld\n", n, x, y, start);
      if (x == 0) {  // 上
        return (start + x + y) % 9;
      }
      if (y + 1 == n) {  // 右
        return (start + y + x) % 9;
      }
      if (x + 1 == n) {  // 下
        return (start + 3 * (n - 1) - y) % 9;
      }
      if (y == 0) {  // 左
        return (start + 4 * (n - 1) - x) % 9;
      }

      ll lev = n;
      lev = mymin(lev, x - 0 + 1);
      lev = mymin(lev, n - x);
      lev = mymin(lev, y - 0 + 1);
      lev = mymin(lev, n - y);
      lev = lev - 1;

      // 此时 lev 肯定大于 1
      // 4 * (n-1) + 4 * (n-2) + .. + 4 * (n - lev)
      ll pos = 4 * ((n - 1) + (n - 1 - (lev - 1) * 2)) * lev  / 2;
      // printf("lev= %lld pos = %lld\n", lev, pos);
      start = (start +  pos) % 9;
      x -= lev;
      y -= lev;
      n -= lev * 2;
    }
    return 0;
  }

 public:
  int orchestraLayout(int num, int x, int y) { return dfs(num, x, y, 0) + 1; }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  TEST_SMP3(Solution, orchestraLayout, 1, 1, 0, 0);
  TEST_SMP3(Solution, orchestraLayout, 1, 2, 0, 0);
  TEST_SMP3(Solution, orchestraLayout, 2, 2, 0, 1);
  TEST_SMP3(Solution, orchestraLayout, 3, 2, 1, 1);
  TEST_SMP3(Solution, orchestraLayout, 4, 2, 1, 0);
  TEST_SMP3(Solution, orchestraLayout, 1, 3, 0, 0);
  TEST_SMP3(Solution, orchestraLayout, 2, 3, 0, 1);
  TEST_SMP3(Solution, orchestraLayout, 3, 3, 0, 2);
  TEST_SMP3(Solution, orchestraLayout, 4, 3, 1, 2);
  TEST_SMP3(Solution, orchestraLayout, 5, 3, 2, 2);
  TEST_SMP3(Solution, orchestraLayout, 6, 3, 2, 1);
  TEST_SMP3(Solution, orchestraLayout, 7, 3, 2, 0);
  TEST_SMP3(Solution, orchestraLayout, 8, 3, 1, 0);
  TEST_SMP3(Solution, orchestraLayout, 9, 3, 1, 1);
  TEST_SMP3(Solution, orchestraLayout, 1, 4, 0, 0);
  TEST_SMP3(Solution, orchestraLayout, 2, 4, 0, 1);
  TEST_SMP3(Solution, orchestraLayout, 3, 4, 0, 2);
  TEST_SMP3(Solution, orchestraLayout, 4, 4, 0, 3);
  TEST_SMP3(Solution, orchestraLayout, 5, 4, 1, 3);
  TEST_SMP3(Solution, orchestraLayout, 6, 4, 2, 3);
  TEST_SMP3(Solution, orchestraLayout, 7, 4, 3, 3);
  TEST_SMP3(Solution, orchestraLayout, 8, 4, 3, 2);
  TEST_SMP3(Solution, orchestraLayout, 9, 4, 3, 1);
  TEST_SMP3(Solution, orchestraLayout, 1, 4, 3, 0);
  TEST_SMP3(Solution, orchestraLayout, 2, 4, 2, 0);
  TEST_SMP3(Solution, orchestraLayout, 3, 4, 1, 0);
  TEST_SMP3(Solution, orchestraLayout, 4, 4, 1, 1);
  TEST_SMP3(Solution, orchestraLayout, 5, 4, 1, 2);
  TEST_SMP3(Solution, orchestraLayout, 6, 4, 2, 2);
  TEST_SMP3(Solution, orchestraLayout, 7, 4, 2, 1);
  TEST_SMP3(Solution, orchestraLayout, 8, 5, 1, 1);
  TEST_SMP3(Solution, orchestraLayout, 9, 5, 1, 2);
  TEST_SMP3(Solution, orchestraLayout, 1, 5, 1, 3);
  TEST_SMP3(Solution, orchestraLayout, 7, 5, 2, 2);

  return 0;
}
