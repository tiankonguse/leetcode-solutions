
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
  int minimumPairRemoval(const vector<int>& nums) {
    map<ll, ll> indexToValue;  // index -> value
    for (int i = 0; i < int(nums.size()); i++) {
      indexToValue[i] = nums[i];
    }
    int lowerNum = 0;
    map<pair<ll, int>, int> sumToRightIndex;
    for (int i = 0; i + 1 < int(nums.size()); i++) {
      ll sum = nums[i] + nums[i + 1];
      sumToRightIndex[make_pair(sum, i)] = i + 1;
      if (nums[i] > nums[i + 1]) {
        lowerNum++;
      }
    }

    int ans = 0;
    while (lowerNum > 0) {
      ans++;
      const auto itMin = sumToRightIndex.begin();
      const auto [oldSum, leftIndex] = itMin->first;
      const int rightIndex = itMin->second;
      const ll leftOldVal = indexToValue[leftIndex];
      const ll rightOldVal = indexToValue[rightIndex];
      sumToRightIndex.erase(make_pair(leftOldVal + rightOldVal, leftIndex));

      MyPrintf("ans=%d, nums: ", ans);
      // for (auto [k, v] : indexToValue) {
      //   MyPrintf("{%lld,%lld} ", k, v);
      // }
      MyPrintf("\n");
      MyPrintf("oldSum=%lld left{%d,%lld} right{%d,%lld} \n", oldSum, leftIndex, leftOldVal, rightIndex, rightOldVal);
      MyPrintf("begin lowerNum=%d\n", lowerNum);
      // index 和 nextIndex 的和合并到 index，删除 nextIndex

      // 不是第一个，合并后变大，原先可能是 小于，现在非小于
      if (auto it = indexToValue.lower_bound(leftIndex); it != indexToValue.begin()) {
        it--;  // 上一个
        const int preIndex = it->first;
        const ll preValue = it->second;
        if (preValue > leftOldVal && preValue <= oldSum) {
          lowerNum--;
        } else if (preValue <= leftOldVal && preValue > oldSum) {
          lowerNum++;
        }
        sumToRightIndex.erase(make_pair(preValue + leftOldVal, preIndex));
        sumToRightIndex[make_pair(preValue + oldSum, preIndex)] = leftIndex;
      }

      // 不是最后一个，合并后变大，原先可能是 小于，现在大于
      if (auto it = indexToValue.upper_bound(rightIndex); it != indexToValue.end()) {
        // upper_bound 已经是下一个了
        const int nextIndex = it->first;
        const ll nextValue = it->second;
        if (rightOldVal <= nextValue && oldSum > nextValue) {
          lowerNum++;
        } else if (rightOldVal > nextValue && oldSum <= nextValue) {
          lowerNum--;
        }
        sumToRightIndex.erase(make_pair(rightOldVal + nextValue, rightIndex));
        sumToRightIndex[make_pair(oldSum + nextValue, leftIndex)] = nextIndex;
      }

      if (leftOldVal > rightOldVal) {
        lowerNum--;
      }
      indexToValue.erase(rightIndex);
      indexToValue[leftIndex] = oldSum;
      MyPrintf("end lowerNum=%d\n", lowerNum);
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