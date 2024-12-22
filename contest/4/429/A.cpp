
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
  int minimumOperations(vector<int>& nums) {
    int n = nums.size();
    unordered_set<int> h;
    for (int i = n - 1; i >= 0; i--) {
      int v = nums[i];
      if (h.count(v)) {   // 需要删除 [0, i]
        int m = i + 1;    // 至少删除 m 个数字
        m = (m + 2) / 3;  // 向上取整
        return min(m, n);
      }
      h.insert(v);
    }
    return 0;
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