
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
  // 固定 k 个区间，需要考虑两头的空余空间，都移动到一端，剩下的就是当前最优值
  int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
    int n = startTime.size();
    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += endTime[i] - startTime[i];
      if (i < k - 1) {
        continue;
      }
      int l = i - k < 0 ? 0 : endTime[i - k];
      int r = i + 1 == n ? eventTime : startTime[i + 1];
      ans = max(ans, r - l - sum);
      sum -= endTime[i - k + 1] - startTime[i - k + 1];
    }
    return ans;
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