
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
  std::vector<int> factors;
  void CalFactor(int N) {
    factors.clear();
    for (int i = 1; i * i <= N; i++) {
      if (N % i == 0) {
        int j = N / i;
        factors.push_back(i);
        if (i != j) {
          factors.push_back(j);
        }
      }
    }
  }
  int n;
  vector<int> nums;
  vector<int> sortNums;
  int FindMinPos(int l, int r) {  // [l,r)
    for (int i = r - 2; i >= l; i--) {
      if (nums[i] <= nums[i + 1]) {
        continue;
      } else {
        return i + 1;
      }
    }
    return l;
  }
  bool Check(const int k) {
    for (int l = 0; l < n; l += k) {
      const int r = l + k;
      int minPos = FindMinPos(l, r);
      MyPrintf("l=%d, r=%d, minPos=%d\n", l, r, minPos);
      for (int i = l; i < r; i++) {
        if (sortNums[i] != nums[(i - l + minPos) % k + l]) {
          return false;
        }
      }
    }
    return true;
  }

 public:
  int sortableIntegers(vector<int>& nums_) {
    nums.swap(nums_);
    sortNums = nums;
    sort(sortNums.begin(), sortNums.end());
    n = nums.size();
    CalFactor(n);
    int ans = 0;
    for (auto k : factors) {
      MyPrintf("k=%d\n", k);
      if (Check(k)) {
        ans += k;
      }
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