/*
ID: tiankonguse
TASK: barn1
LANG: C++
*/
#define TASK "barn1"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
void Solver() {  //
  int m, s, c;
  scanf("%d%d%d", &m, &s, &c);
  vector<int> nums;
  nums.reserve(c);
  for (int i = 0; i < c; i++) {
    int v;
    scanf("%d", &v);
    nums.push_back(v);
  }

  sort(nums.begin(), nums.end());

  int ans = nums.back() - nums.front() + 1;
  vector<int> dis;
  dis.reserve(c);
  int pre = nums.front();
  for (auto v : nums) {
    if (pre + 1 < v) {
      dis.push_back(v - pre - 1);
    }
    pre = v;
  }

  sort(dis.begin(), dis.end(), [](auto a, auto b) { return a > b; });

  for (int i = 0; i < m - 1 && i < dis.size(); i++) {
    ans -= dis[i];
  }

  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
