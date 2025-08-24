
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  bool partitionArray(vector<int>& nums, const int K) {
    int n = nums.size();
    if (n % K != 0) return false;
    const int D = n / K;
    sort(nums.begin(), nums.end());
    int pre = nums.front();
    int num = 0;
    for (auto x : nums) {
      if (pre != x) {
        pre = x;
        num = 0;
      }
      num++;
      if (num > D) {
        return false;
      }
    }
    return true;
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