/*
ID: tiankonguse
TASK: milk3
LANG: C++
*/
#define TASK "milk3"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
//   #ifndef USACO_LOCAL_JUDGE
//     freopen(TASK ".in", "r", stdin);
//     freopen(TASK ".out", "w", stdout);
//   #endif
}

int H(const int a, const int b, const int c) {
  return a * 100 * 100 + b * 100 + c;
}

queue<tuple<int, int, int>> que;
unordered_set<int> flag;
unordered_set<int> h;
vector<int> ans;

void Add(const int a, const int b, const int c) {
  if (a == 0 && h.count(c) == 0) {
    h.insert(c);
    ans.push_back(c);
  }
  int h = H(a, b, c);
  if (flag.count(h) == 0) {
    flag.insert(h);
    que.push({a, b, c});
  }
}

void Solver() {  //
  int A, B, C;
  scanf("%d%d%d", &A, &B, &C);
  const int BIT[3] = {A, B, C};
  ans.reserve(C);

  Add(0, 0, C);
  while (!que.empty()) {
    const auto [a, b, c] = que.front();
    que.pop();

    const int bit[3] = {a, b, c};
    for (int i = 0; i < 3; i++) {
      if (bit[i] == 0) continue;     // bit[i] is empty
      for (int j = 0; j < 3; j++) {  // bit[i] -> bit[j]
        if (i == j) continue;
        if (bit[j] == BIT[j]) continue;  // bit[j] is full
        int dis = bit[i];
        if (bit[i] + bit[j] > BIT[j]) {
          dis = BIT[j] - bit[j];
        }
        int tmp[3] = {bit[0], bit[1], bit[2]};
        tmp[j] += dis;
        tmp[i] -= dis;
        Add(tmp[0], tmp[1], tmp[2]);
      }
    }
  }
  //   printf("ans size=%d\n", ans.size());

  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d%c", ans[i], i + 1 < ans.size() ? ' ' : '\n');
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
