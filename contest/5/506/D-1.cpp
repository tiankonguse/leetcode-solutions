
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
  ll maxSum(vector<int>& nums, const int k) {  //
    int n = nums.size();
    int max_ans = -1e9;

    for (int i = 0; i < n; ++i) {
      multiset<int> out_set;
      for (int p = 0; p < i; ++p) out_set.insert(nums[p]);
      for (int p = i; p < n; ++p) out_set.insert(nums[p]);

      multiset<int> in_set;
      int current_window_sum = 0;

      for (int j = i; j < n; ++j) {
        int val = nums[j];

        auto it = out_set.find(val);
        if (it != out_set.end()) {
          out_set.erase(it);
        }
        in_set.insert(val);
        current_window_sum += val;

        int t = min({k, (int)in_set.size(), (int)out_set.size()});

        int temp_sum = current_window_sum;

        auto it_in = in_set.begin();
        auto it_out = out_set.rbegin();

        for (int m = 0; m < t; ++m) {
          if (*it_out > *it_in) {
            temp_sum += (*it_out - *it_in);
            it_in++;
            it_out++;
          } else {
            break;
          }
        }

        max_ans = max(max_ans, temp_sum);
      }
    }
    return max_ans;
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