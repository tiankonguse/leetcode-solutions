/*
ID: tiankonguse
TASK: frac1
LANG: C++
*/
#define TASK "frac1"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

vector<pair<int, int>> nums;
void Solver() {  //
  int n;
  scanf("%d", &n);
  nums.reserve(n * n);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      nums.push_back({j, i});
    }
  }
  sort(nums.begin(), nums.end(), [](const auto& a, const auto& b) {
    if (a.first * b.second == b.first * a.second) {
      return a < b;
    } else {
      return a.first * b.second < b.first * a.second;
    }
  });

  pair<int, int> a = nums.front();
  printf("%d/%d\n", a.first, a.second);
  for (auto& b : nums) {
    if (a.first * b.second == b.first * a.second) continue;
    a = b;
    printf("%d/%d\n", a.first, a.second);
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
