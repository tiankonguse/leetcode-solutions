
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
  int maxDistinctElements(vector<int>& nums, ll k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    ll pre = INT_MIN;
    int ans = 0;
    for (ll v : nums) {
      ll l = v - k;
      ll r = v + k;
      if(pre < l){
        pre = l;
        ans++;
      }else if(l<=pre && pre < r){
        pre = pre + 1;
        ans++;
      }
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