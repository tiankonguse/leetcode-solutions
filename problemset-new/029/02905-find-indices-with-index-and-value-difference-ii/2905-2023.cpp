
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

typedef long long ll;
class Solution {
 public:
  vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
    int n = nums.size();
    int minPos = 0, maxMos = 0;
    int l = 0, r = indexDifference;  //[l, r)
    l++;

    while (r < n) {
      ll v = nums[r];

      if (abs(v - nums[minPos]) >= valueDifference) {
        return {r, minPos};
      }

      if (abs(v - nums[maxMos]) >= valueDifference) {
        return {r, maxMos};
      }

      if (l < n) {
        if (nums[l] < nums[minPos]) {
          minPos = l;
        }
        if (nums[l] > nums[maxMos]) {
          maxMos = l;
        }
        l++;
      }
      r++;
    }
    return {-1, -1};
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