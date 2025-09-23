
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
  int minJump(vector<int>& jump) {  //
    return accumulate(jump.begin(), jump.end(), 0);
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  unordered_map<ll, ll> m;
  ll minVal = 0;
  vector<ll> nums;
  nums.push_back(0);

  while (nums.back() < 1e9 && nums.size() <= 5e4) {
    while (m.count(minVal)) minVal++;
    ll lastVal = nums.back() + minVal;
    ll maxNum = 0;
    for (auto v : nums) {
      ll d = lastVal - v;
      m[d]++;
      maxNum = max(maxNum, m[d]);
    }
    nums.push_back(nums.back() + minVal);
    if (nums.size() % 100 == 0) {
      MyPrintf("n=%d v=%lld d=%d minVal=%lld maxNum=%lld\n", int(nums.size()), nums.back(), int(m.size()), minVal,
               maxNum);
    }
  }
  MyPrintf("n=%d v=%lld d=%d minVal=%lld \n", int(nums.size()), nums.back(), int(m.size()), minVal);

  return 0;
}

#endif