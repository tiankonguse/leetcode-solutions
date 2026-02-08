
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 758 / 812 个通过的测试用例
// 765 / 812 个通过的测试用例
int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  ll countSubarrays(vector<int>& nums, ll k) {
    deque<pair<ll,int>> maxVal, minVal;
    ll ans = 0;
    int n = nums.size();
    int maxOffset = 1; // [i, maxOffset)
    maxVal.push_back({nums[0], 0});
    minVal.push_back({nums[0], 0});
    for (int i = 0; i < n; i++) {
      // 入队
      while(maxOffset < n && (maxVal.front().first - minVal.front().first) * (maxOffset - i) <= k) {
        // add maxOffset
        const ll val = nums[maxOffset];
        while(maxVal.size() > 0 && maxVal.back().first <= val){
          maxVal.pop_back();
        }
        maxVal.push_back({val, maxOffset});
        while(minVal.size() > 0 && minVal.back().first >= val){
          minVal.pop_back();
        }
        minVal.push_back({val, maxOffset});
        maxOffset++;
      }
      ll cnt = 1;
      if((maxVal.front().first - minVal.front().first) * (maxOffset - i) <= k){
        MyPrintf("i=%d, lastFix maxOffset=%d\n", i, maxOffset);
        cnt = maxOffset - i;
      }else{
        cnt = maxOffset - i - 1;
      }
     ans += cnt;
      MyPrintf("i=%d, add=%lld maxOffset=%d\n", i, cnt, maxOffset);
      
      
      // 出队
      if(maxVal.front().second == i){
        maxVal.pop_front();
      }
      if(minVal.front().second == i){
        minVal.pop_front();
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