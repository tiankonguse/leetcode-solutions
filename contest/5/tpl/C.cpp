
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
  string skill;
  string station;
  int n, m;
  vector<int> leftPos, rightPos;
  void GreedyLeft() {
    int ni = 0, mi = 0;
    leftPos.resize(n);
    while (ni < n && mi < m) {
      if (skill[ni] == station[mi]) {
        leftPos[ni] = mi;
        ni++;
        mi++;
      } else {
        mi++;
      }
    }
  }
  void GreedyRight() {
    int ni = n - 1, mi = m - 1;
    rightPos.resize(n);
    while (ni >= 0 && mi >= 0) {
      if (skill[ni] == station[mi]) {
        rightPos[ni] = mi;
        ni--;
        mi--;
      } else {
        mi--;
      }
    }
  }

 public:
  int maximumGap(string skill_, string station_) {
    skill.swap(skill_);
    station.swap(station_);
    n = skill.size();
    m = station.size();
    if (n == 1) return 0;
    GreedyLeft();
    GreedyRight();
    int ans = 0;
    for (int i = 1; i < n; i++) {
      // 枚举 i-1 与 i 的距离
      ans = max(ans, rightPos[i] - leftPos[i - 1]);
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