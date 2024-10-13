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
vector<pair<int, int>> bucket;

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

  ans.reserve(10000);
  int B = nums.back() - nums.front();
  for (int b = 1; b < B; b++) {
    bucket.clear();
    bucket.resize(b, {0, 0});
    for (auto v : nums) {
      int a = v % b;
      int k = v / b;
      auto& p = bucket[a];
      if (p.second == 0) {  // 首次遇到
        p.first = k;
        p.second = 1;
      } else {
        if (p.first + p.second == k) {  // 连续
          p.second++;
          if (p.second == n) {  // 找到一个答案
            ans.push_back({b, p.first * b + a});
            p.first++;
            p.second--;
          }
        } else {
          p.first = k;
          p.second = 1;
        }
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
