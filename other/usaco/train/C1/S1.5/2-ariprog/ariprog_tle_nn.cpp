/*
ID: tiankonguse
TASK: ariprog
LANG: C++
*/
#define TASK "ariprog"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
int n, m;
unordered_set<int> s;
vector<int> nums;
int k;
vector<pair<int, int>> ans;

bool Check(int a, int b) {
  for (int i = n - 1; i >= 2; i--) {
    if (!s.count(a + b * i)) {
      return false;
    }
  }
  return true;
}
void Solver() {  //
  scanf("%d%d", &n, &m);
  for (int q = 0; q <= m; q++) {
    for (int p = 0; p <= m; p++) {
      s.insert(q * q + p * p);
    }
  }

  k = s.size();
  nums.reserve(k);
  for (auto v : s) {
    nums.push_back(v);
  }
  sort(nums.begin(), nums.end());

  for (int i = 0; i < k; i++) {
    int a = nums[i];
    for (int j = i + 1; j < k; j++) {
      int b = nums[j] - a;
      if (Check(a, b)) {
        ans.push_back({b, a});
      }
    }
  }
  if (ans.size() == 0) {
    printf("NONE\n");
  } else {
    sort(ans.begin(), ans.end());
    for (auto [b, a] : ans) {
      printf("%d %d\n", a, b);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
