/*
ID: tiankonguse
TASK: lamps
LANG: C++
*/
#define TASK "lamps"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll N, C;

// op1: all
// op2: 1 3 5 7 9 1 3 5 7 9
// op3:  2 4 6 8 0 2 4 6 8
// op4: 1  4  7  0  3

// 6 个一周期， [0,6) [6,12)
// op1: all
// op2: 0 2 4
// op3:  1 3 5
// op4: 0  3

vector<ll> ops;
const int MASK = 1 << 6;  // 状态个数
void Init() {
  ops.push_back((1 << 6) - 1);                    // ^ 操作，全部取反
  ops.push_back((1 << 0) | (1 << 2) | (1 << 4));  // 奇数位
  ops.push_back((1 << 1) | (1 << 3) | (1 << 5));  // 偶数位
  ops.push_back((1 << 5) | (1 << 2));             // 3k+1位
}

vector<ll> target;
ll hasAns = 1;
ll onMask = 0;
ll offMask = 0;
void ReadOn() {
  ll on;
  while (true) {
    scanf("%lld", &on);
    if (on == -1) break;
    on--;
    on = on % 6;
    target[on] = 1;
    onMask |= 1 << (5 - on);
  }
}
void ReadOff() {
  ll off;
  while (true) {
    scanf("%lld", &off);
    if (off == -1) break;
    off--;
    off = off % 6;
    if (target[off] == 1) {
      hasAns = 0;  // 循环节内，即开灯，又关灯,没有答案
    }
    target[off] = 0;
    offMask |= 1 << (5 - off);
  }
}

string buf;
string ans;
void Output(const ll v) {
  ans.clear();
  ans.reserve(N);  //
  buf.clear();
  buf.resize(6, '0');
  for (int i = 0; i < 6; i++) {
    if ((v >> i) & 1) {
      buf[i] = '1';
    }
  }
  std::reverse(buf.begin(), buf.end());
  while (ans.size() < N) {
    ans.append(buf);
  }
  ans.resize(N);
  // printf("v=%lld %s\n", v, ans.c_str());
  printf("%s\n", ans.c_str());
}

void Solver() {  //
  Init();
  scanf("%lld%lld", &N, &C);
  target.resize(6, -1);
  ReadOn();
  ReadOff();

  if (hasAns == 0) {
    printf("IMPOSSIBLE\n");
    return;
  }

  vector<ll> pre(MASK, 0);
  vector<ll> tmp(MASK, 0);
  pre[(1 << 6) - 1] = 1;
  // printf("C=%lld ops=%lld\n", C, ll(ops.size()));
  while (C--) {
    tmp.clear();
    tmp.resize(MASK, 0);
    for (int i = 0; i < MASK; i++) {
      if (pre[i] == 0) continue;
      for (auto op : ops) {
        tmp[i ^ op] = 1;
      }
    }
    tmp.swap(pre);
  }
  // printf("onMask: ");
  // Output(onMask);
  // printf("offMask: ");
  // Output(offMask);

  hasAns = false;
  for (int i = 0; i < MASK; i++) {
    if (pre[i] == 0) continue;
    if ((i & onMask) != onMask) continue;
    if ((i & offMask) != 0) continue;
    Output(i);
    hasAns = true;
  }
  if (!hasAns) {
    printf("IMPOSSIBLE\n");
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*



*/