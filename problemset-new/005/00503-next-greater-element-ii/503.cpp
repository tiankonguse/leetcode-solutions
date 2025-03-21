
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
  vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    vector<int> orderStack;
    for (int i = n - 2; i >= 0; i--) {
      int v = nums[i];
      while (orderStack.size() && orderStack.back() <= v) {
        orderStack.pop_back();
      }
      orderStack.push_back(v);
    }

    for (int i = n - 1; i >= 0; i--) {
      int v = nums[i];
      while (orderStack.size() && orderStack.back() <= v) {
        orderStack.pop_back();
      }
      if (orderStack.size()) {
        ans[i] = orderStack.back();
      }
      orderStack.push_back(v);
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