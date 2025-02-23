
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
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
 public:
  ll maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
    for (auto& g : grid) {
      sort(g.begin(), g.end(), [](auto a, auto b) { return a > b; });
    }
    int n = grid.size();
    min_queue<ll> que;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < limits[i]; j++) {
        que.push(grid[i][j]);
        if (int(que.size()) > k) {
          que.pop();
        }
      }
    }
    ll sum = 0;
    while (!que.empty()) {
      sum += que.top();
      que.pop();
    }
    return sum;
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