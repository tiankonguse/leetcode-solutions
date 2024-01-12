/*
ID: tiankonguse
TASK: skidesign
LANG: C++
*/
#define TASK "skidesign"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
int n;
int ans;
vector<int> nums;

void Solver() {  //
  scanf("%d", &n);
  nums.reserve(n);
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    nums.push_back(v);
  }

  sort(nums.begin(), nums.end());

  ans = INT_MAX;
  for (int i = nums.front(); i + 17 <= nums.back(); i++) {
    const int low = i;
    const int high = low + 17;

    int tmp = 0;
    for (auto v : nums) {
      if (v < low) {
        tmp += (low - v) * (low - v);
      } else if (v > high) {
        tmp += (high - v) * (high - v);
      }
    }
    ans = min(ans, tmp);
  }
  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
