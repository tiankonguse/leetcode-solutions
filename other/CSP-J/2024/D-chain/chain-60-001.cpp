/*
ID: tiankonguse
TASK: chain
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11230?contestId=209924
https://www.luogu.com.cn/record/219570046
*/
#define TASK "chain"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

const int N = 1e5 + 10;
ll n, k, q;
pair<ll, ll> nums[2 * N];
pair<ll, ll> ranges[N];  // 计算每个人的数字在所有数字里面的范围，[piLeft, piRight)
vector<vector<ll>> dp;   // 记录第 r 轮，值 v 是否可以结尾
pair<ll, ll> queries[N];
unordered_map<ll, vector<pair<int, ll>>> valToPersonPos;  // 记录每个值在哪些人和位置出现
ll R;
ll sum = 0;

unordered_map<ll, ll> pre;  // 上一轮接龙时，记录每个值结尾的有哪些人，-1 代表有多个人，否则是人的编号
unordered_map<ll, ll> now;

// 这里方法很多，例如线段树、权值线段树、树状数组、递减标记法、左加右减标记法
// 这里采用左加右减标记法
vector<int> flags;
inline void Update(int r, int pi, ll left, ll right) {  // [left, right]
  flags[left]++;
  flags[right + 1]--;
}
void Merge(int r) {
  int nowNum = 0;
  int offset = 0;
  pre.clear();
  for (int i = 0; i < n; i++) {
    const auto [piLeft, piRight] = ranges[i];  // [piLeft, piRight)
    for (int j = piLeft; j < piRight; j++, offset++) {
      int v = nums[j].second;
      nowNum += flags[offset];
      if (nowNum > 0) {
        dp[r][v] = 1;  // 记录这个值可以结尾
        if (pre.count(v) == 0) {
          pre[v] = i;
        } else {
          if (pre[v] != i) {  // 如果已经有了，说明有多个人接龙到这个值
            pre[v] = -1;      // 标记为多个人
          }
        }
      }
    }
  }
}

void Solver() {  //
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll maxS = 1;
    valToPersonPos.clear();
    scanf("%lld%lld%lld", &n, &k, &q);
    sum = 0;
    for (int i = 0; i < n; i++) {
      ll l;
      scanf("%lld", &l);
      ranges[i] = {sum, sum + l};
      for (int j = 0; j < l; j++) {
        ll S;
        scanf("%lld", &S);
        maxS = max(maxS, S);  // 记录最大的值
        nums[sum + j] = {i, S};
        valToPersonPos[S].emplace_back(i, sum + j);  // 记录每个值在哪些人和位置出现
      }
      sum += l;
    }

    R = 1;
    for (int i = 0; i < q; i++) {
      scanf("%lld%lld", &queries[i].first, &queries[i].second);
      R = max(R, queries[i].first);
    }

    dp.clear();
    dp.resize(R + 1, vector<ll>(maxS + 1, 0));  // dp[r][v] = 1 表示第 r 轮可以以 v 结尾

    flags.clear();
    flags.resize(sum + 2, 0);

    pre.clear();
    pre[1] = -1;                    // 初始状态，1 号值可以开始接龙
    for (int r = 1; r <= R; r++) {  // 进行 R 轮游戏
      for (auto [v, pos] : pre) {
        // 上一轮接龙，编号为 pos 的人以 v 结尾
        for (const auto& [pi, offset] : valToPersonPos[v]) {
          const auto [piLeft, piRight] = ranges[pi];  // [piLeft, piRight)
          if (pi == pos) continue;                    // 不能接自己的
          if (offset + 1 == piRight) continue;        // 不能接到最后一个
          ll left = offset + 1;
          ll right = min(offset + k - 1, piRight - 1);  // 下一个值
          Update(r, pi, left, right);                   // 第 r 轮，第 pi 个人，从 left 到 right 接龙的结束位置
        }
      }
      Merge(r);  // 第 r 轮结束后，合并所有人的接龙结果
      flags.clear();
      flags.resize(sum + 2, 0);
    }
    for (int i = 0; i < q; i++) {
      ll r = queries[i].first;
      ll v = queries[i].second;
      if (v > maxS) {
        printf("0\n");
        continue;
      }
      printf("%d\n", dp[r][v] ? 1 : 0);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
5 5
*/