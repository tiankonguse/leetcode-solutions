
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

typedef long long ll;
// 思路：模拟，并通过hash记录是否访问过该点
class Solution {
  const ll MN = 1e5;
  ll Hash(ll x, ll y) {
    return x * MN + y;  //
  }

 public:
  vector<int> lastVisitedCell(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    unordered_map<ll, int> H;
    int x = 0, y = 0;
    int X = x, Y = y;
    H[0] = 1;
    auto HasNext = [&]() -> bool {
      char c = grid[x][y];
      switch (c) {
        case 'L':
          y--;
          break;
        case 'R':
          y++;
          break;
        case 'U':
          x--;
          break;
        case 'D':
          x++;
          break;
      }
      if (x < 0 || x >= n || y < 0 || y >= m) {
        return false;
      }
      ll h = Hash(x, y);
      if (H.count(h)) {
        return false;
      }
      H[h] = 1;
      return true;
    };
    while (HasNext()) {
      // MyPrintf("c=%c (%d,%d)->(%d,%d)\n", grid[X][Y], X, Y, x, y);
      X = x;
      Y = y;
    }
    return {X, Y};
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif