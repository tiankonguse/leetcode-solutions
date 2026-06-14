
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

class Solution {
 public:
  ll maxRatings(vector<vector<int>>& units) {  //
    int n = units.size();
    int m = units[0].size();
    if (m == 1) {
      ll ans = 0;
      for (int i = 0; i < n; i++) ans += units[i][0];
      return ans;
    }
    int minRow = 0;
    ll sumColSecond = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        int minPos = j;
        for (int k = j + 1; k < m; k++) {
          if (units[i][k] < units[i][minPos]) minPos = k;
        }
        swap(units[i][j], units[i][minPos]);
      }
      if (units[i][0] < units[minRow][0]) minRow = i;
      sumColSecond += units[i][1];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans = max(ans, sumColSecond - units[i][1] + units[minRow][0]);
    }
    return ans;
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