
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
/*
贪心

操作时，对一个元素的十进制重排序，先按所有数字降序排序可以得到最大的数字。
一次操作会使这个数字增加一定的值。
题目要求最终和最大，显然每次需要选择增加值最大的元素。

故，计算出每个元素的增加值，按增加值从大到小排序，然后选择前 K 个增加值即可。

*/
class Solution {
  ll CalDis(const ll v) {
    string s = to_string(v);
    sort(s.begin(), s.end(), greater<char>());
    return stoll(s) - v;
  }

 public:
  long long maximizeSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<pair<ll, ll>> A(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      ll v = nums[i];
      ll dis = CalDis(v);
      A[i] = {dis, v};
      sum += v;
    }
    sort(A.begin(), A.end(), greater<pair<ll, ll>>());
    ll ans = sum;
    for (int i = 0; i < k; i++) {
      ans += A[i].first;
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