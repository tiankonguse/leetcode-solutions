
/*
ID: tiankonguse
TASK: lis
LANG: C++
CONTEST: 2021 年 CCF NOI线上教师培训测试
OJ:
*/
#define TASK "lis"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

ll Lis(const vector<ll>& nums) {
  ll n = nums.size();
  vector<ll> dp(n);
  dp[0] = 1;  // 第一个数字答案是自己
  for (ll i = 1; i < n; i++) {
    ll maxNum = 0;
    for (ll j = 0; j < i; j++) {
      if (nums[j] < nums[i]) {
        maxNum = max(maxNum, dp[j]);
      }
    }
    dp[i] = maxNum + 1;
  }
  return dp[n - 1];
}
void Solver() {  //
  ll n;
  vector<ll> nums;

  scanf("%lld", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  printf("%lld\n", Lis(nums));
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
10
3 18 7 14 10 12 23 41 16 24
*/