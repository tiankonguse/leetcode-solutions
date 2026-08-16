
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
  int GreedyMaxDis(int minDis = 0) {  // 贪心找到一个解
    int ni = 0, mi = 0;
    int preMi = -1;
    int maxDis = 0;
    while (ni < n && mi < m) {
      if (skill[ni] == station[mi] && (preMi == -1 || mi - preMi >= minDis)) {
        if (preMi != -1) {
          maxDis = max(maxDis, mi - preMi);
        }
        preMi = mi;

        ni++;
        mi++;
      } else {
        mi++;
      }
    }
    if (ni == n) return maxDis;
    return -1;
  }

 public:
  int maximumGap(string skill_, string station_) {
    skill.swap(skill_);
    station.swap(station_);
    n = skill.size();
    m = station.size();
    if (n == 1) return 0;

    int left = GreedyMaxDis();
    int right = m;
    MyPrintf("left=%d, right=%d\n", left, right);
    while (left < right) {  // [left, right)
      int mid = (left + right) / 2;
      int res = GreedyMaxDis(mid);
      MyPrintf("mid=%d, res=%d\n", mid, res);
      if (res != -1) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left - 1;
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