
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
  vector<ll> dp(n + 1, INT64_MAX);

  ll ans = 1;
  for (ll v : nums) {
    auto it = lower_bound(dp.begin(), dp.end(), v);
    // 分几种情况
    if (*it > v) {  // v 不存在且更小，更新答案
      *it = v;
      ans = max(ans, ll(it - dp.begin() + 1));
    }
  }
  return ans;
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