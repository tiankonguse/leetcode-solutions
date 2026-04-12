
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
  vector<double> internalAngles(vector<int>& sides) {
    int a = sides[0], b = sides[1], c = sides[2];
    if (a + b <= c || a + c <= b || b + c <= a) return {};
    double A = acos((b * b + c * c - a * a) / (2.0 * b * c)) * 180.0 / M_PI;
    double B = acos((a * a + c * c - b * b) / (2.0 * a * c)) * 180.0 / M_PI;
    double C = 180.0 - A - B;
    vector<double> ans = {A, B, C};
    sort(ans.begin(), ans.end());
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