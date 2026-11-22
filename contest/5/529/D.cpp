
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

// 901 / 999 个通过的测试用例

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
struct Node {
  ll cost = INT64_MAX;
  ll maxNeg = INT64_MIN;
  ll minNon = INT64_MAX;
  bool isUsed = false;
  Node() {
    this->cost = INT64_MAX;
    this->maxNeg = INT64_MIN;
    this->minNon = INT64_MAX;
    isUsed = false;
  }
  void Set(const ll v, const ll neg = INT64_MIN, const ll non = INT64_MAX) {
    if (!isUsed) {
      isUsed = true;
      cost = v;
      maxNeg = neg;
      minNon = non;
    } else {
      if (v < cost) {
        cost = v;
        maxNeg = neg;
        minNon = non;
      } else if (v == cost && neg > maxNeg) {
        maxNeg = neg;
        minNon = non;
      } else if (v == cost && neg == maxNeg && non < minNon) {
        minNon = non;
      }
    }
  }
};
class Solution {
 public:
  ll minCost(vector<int>& nums) {
    int n = nums.size();
    if (n == 2 || n == 3) {
      return ll(nums.front()) + ll(nums.back());
    }
    ll ans = ll(nums.front()) + ll(nums.back());
    ll negSum = 0, maxNeg = INT64_MIN, minNon = INT64_MAX;
    int negCnt = 0;
    for (int i = 1; i + 1 < n; i++) {
      ll v = ll(nums[i]);
      if (v < 0) {
        negCnt++;
        negSum += v;
        maxNeg = max(maxNeg, v);
      } else {
        minNon = min(minNon, v);
      }
    }
    if (negCnt % 2 == 1) {
      if (maxNeg != INT64_MIN && minNon != INT64_MAX && maxNeg + minNon < 0) {
        negSum += minNon;
      } else {
        negSum -= maxNeg;
      }
    }

    return ans + negSum;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<int>& nums, const ll& ans) { TEST_SMP1(Solution, minCost, ans, nums); }

int main() {
  vector<int> nums;
  ll ans;

  nums = {46, -23, 15, -2, -59, -51};
  ans = -87;
  Test(nums, ans);
  return 0;
}

#endif