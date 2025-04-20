
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
  int maximumPossibleSize(vector<int>& nums) {
    vector<int> st;
    st.reserve(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i) {
      while (!st.empty() && st.back() < nums[i]) {
        st.pop_back();
      }
      st.push_back(nums[i]);
    }
    return st.size();
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