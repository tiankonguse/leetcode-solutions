/*
ID: tiankonguse
TASK: wormhole
LANG: C++
*/
#define TASK "wormhole"

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
unordered_map<int, set<pair<int, int>>> h;
vector<pair<int, int>> nums;
vector<int> nexts;

vector<int> bit;
vector<int> flag;

bool Check() {  //
  flag.clear();
  flag.resize(n, -1);
  for (int i = 0; i < n; i++) {
    if (flag[i] != -1) continue;

    int p = i;
    while (true) {
      flag[p] = i;
    //   printf("p=%d i=%d next=%d\n", p, i, nexts[p]);
      p = nexts[p];
      auto [x, y] = nums[p];
      auto it = h[y].upper_bound({x, p});
      if (it == h[y].end()) {
        break;
      }

      p = it->second;
      if (flag[p] == i) return true;
      if (flag[p] != -1) break;
    }
  }
  return false;
}
void Dfs(const int last) {
  if (last < 0) {
    if (Check()) {
    //   printf("true: ");
    //   for (int i = 0; i < n; i++) {
    //     printf("%d->%d ", i, nexts[i]);
    //   }
    //   printf("\n");
      ans++;
    } else {
    //   printf("false: ");
    //   for (int i = 0; i < n; i++) {
    //     printf("%d->%d ", i, nexts[i]);
    //   }
    //   printf("\n");
    }
    return;
  }

  const int a = bit[0];
  swap(bit[0], bit[last]);

  for (int i = 0; i < last; i++) {
    const int b = bit[i];
    swap(bit[i], bit[last - 1]);

    nexts[a] = b;
    nexts[b] = a;

    Dfs(last - 2);

    swap(bit[i], bit[last - 1]);
  }

  swap(bit[0], bit[last]);
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    h[y].insert({x, i});
    nums.push_back({x, y});
  }
  nexts.resize(n, -1);
  bit.resize(n, 0);
  for (int i = 0; i < n; i++) {
    bit[i] = i;
  }

  ans = 0;

  Dfs(n - 1);

  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
