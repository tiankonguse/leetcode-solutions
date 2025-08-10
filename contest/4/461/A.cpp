
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
  bool isTrionic(vector<int>& nums) {
    int n = nums.size();

    // 第一步：计算出有序性的分割线
    vector<int> nodes;
    nodes.reserve(n);
    int dir = 0;  // 0: 未知, 1: 上升, -1: 下降
    nodes.push_back(0);
    for (int i = 1; i < n; i++) {
      int newDir = 0;
      if (nums[i - 1] < nums[i]) {
        newDir = 1;
      } else if (nums[i - 1] > nums[i]) {
        newDir = -1;
      }

      if (dir != 0 && dir == newDir) {
        nodes.pop_back();
      }

      nodes.push_back(i);  // 相等的情况,当做分割线
      dir = newDir;
    }

    const int m = nodes.size();
    if (m != 4) return false;
    const int l = nodes[0];
    const int p = nodes[1];  // 上升的结束点
    const int q = nodes[2];  // 下降的结束点
    const int r = nodes[3];  // 上升的结束点
    return nums[l] < nums[p] && nums[p] > nums[q] && nums[q] < nums[r];
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