
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
  int minSwaps(vector<int>& nums) {
    int n = nums.size();
    vector<int> bitSums(n);
    vector<int> indexs(n);
    for (int i = 0; i < n; i++) {
      indexs[i] = i;
      int v = nums[i];
      int sum = 0;
      while (v) {
        sum += v % 10;
        v /= 10;
      }
      bitSums[i] = sum;
    }
    sort(indexs.begin(), indexs.end(), [&](auto a, auto b) {
      if (bitSums[a] == bitSums[b]) {
        return nums[a] < nums[b];
      }
      return bitSums[a] < bitSums[b];
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (indexs[i] != i) {
        ans++;
        swap(indexs[i], indexs[indexs[i]]);
        i--;
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