
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
  vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2) {  //
    int n1 = series1.size();
    int n2 = series2.size();
    vector<vector<int>> result;
    result.reserve(n1 + n2);
    int i1 = 0;
    int i2 = 0;
    while (i1 < n1 && i2 < n2) {
      int t1 = series1[i1][0];
      int v1 = series1[i1][1];
      int t2 = series2[i2][0];
      int v2 = series2[i2][1];
      if (t1 == t2) {
        result.push_back({t1, v1 + v2});
        i1++;
        i2++;
      } else if (t1 < t2) {
        result.push_back({t1, v1 + v2});
        i1++;
      } else {
        result.push_back({t2, v1 + v2});
        i2++;
      }
    }

    while (i1 < n1) {
      int t1 = series1[i1][0];
      int v1 = series1[i1][1];
      result.push_back({t1, v1});
      i1++;
    }
    while (i2 < n2) {
      int t2 = series2[i2][0];
      int v2 = series2[i2][1];
      result.push_back({t2, v2});
      i2++;
    }

    return result;
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