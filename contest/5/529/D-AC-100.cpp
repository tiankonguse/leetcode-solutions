
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
    vector<Node> preCost(4);  // 最小成本，最大负数, 最小非负数
    // preCost[0] 负数个数为偶数个的最小成本
    // preCost[1] 负数个数为奇数个数，剩余负数未使用的的最小成本
    // preCost[2] 负数个数为奇数个数，剩余负数已使用的的最小成本
    // preCost[3] 当前位置为右区间的最小成本
    preCost[0].Set(ll(nums[0]));

    for (int i = 1; i < n; i++) {
      const ll v = ll(nums[i]);
      vector<Node> tmpCost(4);
      if (preCost[3].isUsed) {
        tmpCost[0].Set(preCost[3].cost + v);
      }

      if (v >= 0) {
        // 0 -> 0
        if (preCost[0].isUsed) {
          tmpCost[0].Set(preCost[0].cost, preCost[0].maxNeg, min(preCost[0].minNon, v));
        }

        // 1 ->
        if (preCost[1].isUsed) {
          if (preCost[1].maxNeg != INT64_MIN && preCost[1].maxNeg + v < 0) {
            tmpCost[2].Set(preCost[1].cost + preCost[1].maxNeg + v, preCost[1].maxNeg, v);
          } else {
            tmpCost[1].Set(preCost[1].cost, preCost[1].maxNeg, min(preCost[1].minNon, v));
          }
        }

        // 2 ->
        if (preCost[2].isUsed) {
          if (preCost[2].minNon != INT64_MAX && v < preCost[2].minNon) {
            tmpCost[2].Set(preCost[2].cost - preCost[2].minNon + v, preCost[2].maxNeg, v);
          } else {
            tmpCost[2].Set(preCost[2].cost, preCost[2].maxNeg, preCost[2].minNon);
          }
        }
      } else {
        // 0 ->
        if (preCost[0].isUsed) {
          if (preCost[0].minNon != INT64_MAX && max(preCost[0].maxNeg, v) + preCost[0].minNon < 0) {
            tmpCost[2].Set(preCost[0].cost + preCost[0].minNon + v, max(preCost[0].maxNeg, v), preCost[0].minNon);
          } else {
            if (preCost[0].maxNeg != INT64_MIN && v < preCost[0].maxNeg) {
              tmpCost[1].Set(preCost[0].cost - preCost[0].maxNeg + v, preCost[0].maxNeg, preCost[0].minNon);
            } else {
              tmpCost[1].Set(preCost[0].cost, v, preCost[0].minNon);
            }
          }
        }

        // 1 -> 0
        if (preCost[1].isUsed && preCost[1].maxNeg != INT64_MIN) {
          tmpCost[0].Set(preCost[1].cost + preCost[1].maxNeg + v, max(preCost[1].maxNeg, v), preCost[1].minNon);
        }

        // 2 -> 0
        if (preCost[2].isUsed && preCost[2].minNon != INT64_MAX) {
          tmpCost[0].Set(preCost[2].cost - preCost[2].minNon + v, max(preCost[2].maxNeg, v), preCost[2].minNon);
        }
      }

      for (int j = 0; j < 3; j++) {
        if (preCost[j].isUsed) {
          tmpCost[3].Set(preCost[j].cost + v);
        }
      }

      preCost = tmpCost;
    }
    return preCost[3].cost;
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