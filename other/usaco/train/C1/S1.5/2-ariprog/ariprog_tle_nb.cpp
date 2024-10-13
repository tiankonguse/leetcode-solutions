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
const int N = 250 * 250 * 2 + 1;
int s[N];
vector<int> nums;
int k;

void Solver() {  //
  scanf("%d%d", &n, &m);
  nums.reserve(N);
  for (int q = 0; q <= m; q++) {
    for (int p = 0; p <= m; p++) {
      int v = q * q + p * p;
      if (s[v] == 0) {
        s[v] = 1;
        nums.push_back(v);
      }
    }
  }

  sort(nums.begin(), nums.end());

  bool hashAns = false;
  int B = nums.back() / (n - 1);
  for (int b = 1; b <= B; b++) {
    for (auto a : nums) {
      if (a + (n - 1) * b > nums.back()) {
        break;  // 剪枝，不满足 n 个
      }
      bool ok = true;
      for (int i = n - 1; i >= 1; i--) {
        if (s[a + b * i] == 0) {
          ok = false;
          break;
        }
      }
      if (ok) {
        hashAns = true;
        printf("%d %d\n", a, b);
      }
    }
  }
  if (!hashAns) {
    printf("NONE\n");
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
