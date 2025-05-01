
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
  vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
    int n = words.size();
    vector<int> nums(n);
    auto minCharCount = [](const string& w) {
      char minChar = 'z';
      int num = 0;
      for (char c : w) {
        if (c < minChar) {
          minChar = c;
          num = 1;
        } else if (c == minChar) {
          num++;
        }
      }
      return num;
    };
    for (int i = 0; i < n; i++) {
      nums[i] = minCharCount(words[i]);
    }
    sort(nums.begin(), nums.end());
    vector<int> ans(queries.size());
    for (int i = 0; i < queries.size(); i++) {
      int t = minCharCount(queries[i]);
      int p = upper_bound(nums.begin(), nums.end(), t) - nums.begin();
      ans[i] = n - p;
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