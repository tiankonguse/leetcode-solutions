
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
  int minRotations(int n, string s) {
    vector<int> suf(n + 1, 0);
    int pre = s.back() - '0';
    for (int i = n - 1; i >= 0; i--) {
      int v = s[i] - '0';
      int dis = abs(v - pre);
      int disCost = min(dis, 10 - dis);
      suf[i] = suf[i + 1] + disCost;
      pre = v;
    }
    pre = 0;
    int ans = 0;
    for (auto c : s) {
      int v = c - '0';
      int dis = abs(v - pre);
      int disCost = min(dis, 10 - dis);
      ans += disCost;
      pre = v;
    }
    MyPrintf("base ans=%d\n", ans);

    pre = 0;
    const int last = s.back() - '0';
    int preAns = 0;
    for (int i = 0; i < n; i++) {
      int dis = abs(pre - last);
      int disCost = min(dis, 10 - dis);
      int curAns = preAns + disCost + suf[i];
      ans = min(ans, curAns);
      int v = s[i] - '0';
      dis = abs(v - pre);
      disCost = min(dis, 10 - dis);
      preAns += disCost;
      pre = s[i] - '0';
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