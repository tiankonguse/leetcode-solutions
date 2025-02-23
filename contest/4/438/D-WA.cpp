
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int maxDistance(const ll side, vector<vector<int>>& points, const int k) {
    // k >=4，可以证明，答案不会超过 side，故不考虑首位，可以按环编号
    int n = points.size();
    vector<ll> rows;
    rows.reserve(2 * n);
    for (auto& p : points) {
      int x = p[0], y = p[1];
      if (y == 0) {  // (x, 0)
        rows.push_back(x);
      } else if (x == side) {  // (side, y)
        rows.push_back(side + y);
      } else if (y == side) {  // (x, side)
        rows.push_back(2 * side + (side - x));
      } else if (x == 0) {  // (0, y)
        rows.push_back(3 * side + (side - y));
      }
    }
    sort(rows.begin(), rows.end());
    for (int i = 0; i < n; i++) {
      // printf("%d ", rows[i]);
      rows.push_back(rows[i] + 4 * side);
    }
    // printf("\n");

    auto checkOne = [side, k, &rows](const int p, const ll mid) -> bool {
      int num = 1;
      const int firstVal = rows[p];
      int preVal = firstVal;
      int offset = p;
      while (num < k) {
        auto it = lower_bound(rows.begin() + offset, rows.end(), preVal + mid);
        if (it == rows.end()) return false;
        preVal = *it;
        offset = it - rows.begin();
        num++;
      }
      if ((firstVal + 4 * side) - preVal < mid) {
        return false;
      }
      return true;
    };
    auto checkAll = [n, &checkOne](const ll mid) -> bool {
      for (int i = 0; i < n; i++) {
        if (checkOne(i, mid)) return true;
      }
      return false;
    };

    ll l = 1, r = side + 1;
    while (l < r) {
      ll mid = (l + r) / 2;
      if (checkAll(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif