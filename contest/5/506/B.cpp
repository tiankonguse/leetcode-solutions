
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
  int getLength(vector<int>& nums) {  //
    int n = nums.size();
    int ans = 1;
    for (int i = 0; i < n; i++) {
      unordered_map<int, int> val_cnt;
      unordered_map<int, int> freq_cnt;

      for (int j = i; j < n; j++) {
        int v = nums[j];
        if (val_cnt.count(v)) {
          freq_cnt[val_cnt[v]]--;
          if (freq_cnt[val_cnt[v]] == 0) freq_cnt.erase(val_cnt[v]);
        }
        val_cnt[v]++;
        freq_cnt[val_cnt[v]]++;
        if (val_cnt.size() == 1) {
          ans = max(ans, j - i + 1);
        } else {
          if (freq_cnt.size() != 2) continue;

          int max_cnt = 0;
          int min_cnt = INT_MAX;
          for (auto& [c, _] : freq_cnt) {
            max_cnt = max(max_cnt, c);
            min_cnt = min(min_cnt, c);
          }
          if (max_cnt == min_cnt * 2) {
            ans = max(ans, j - i + 1);
          }
        }
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