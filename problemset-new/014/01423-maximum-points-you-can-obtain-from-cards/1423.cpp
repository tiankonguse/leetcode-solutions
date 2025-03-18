
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
  // 求前缀加后缀 k 个数字的最大值，等价于总和减去中间 n-k 个数字的最小值
  int maxScore(vector<int>& cardPoints, int k) {
    ll sum = accumulate(cardPoints.begin(), cardPoints.end(), 0ll);
    int n = cardPoints.size();
    if (n == k) return sum;

    int left = n - k;
    ll minSum = __LONG_LONG_MAX__;
    ll curSum = 0;
    for (int i = 0; i < n; i++) {
      curSum += cardPoints[i];
      if (i < left - 1) {
        continue;
      }
      minSum = min(minSum, curSum);
      curSum -= cardPoints[i - (left - 1)];
    }
    return sum - minSum;
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