/*
ID: tiankonguse
TASK: chain
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11230?contestId=209924
https://www.luogu.com.cn/record/219584376
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
vector<pair<ll, ll>> nums(2 * N);
vector<pair<ll, ll>> ranges(N);                          // 计算每个人的数字在所有数字里面的范围，[piLeft, piRight)
unordered_map<ll, vector<pair<ll, ll>>> valToPersonPos;  // 记录每个值在哪些人和位置出现
ll R;
ll sum = 0;

vector<ll> preFlag(2 * N, 0);  // 上一轮接龙时，记录每个值结尾的有哪些人，-1 代表有多个人，否则是人的编号
vector<pair<ll, ll>> preList(2 * N);
int preListNum = 0;

// 这里方法很多，例如线段树、权值线段树、树状数组、递减标记法、左加右减标记法
// 这里采用左加右减标记法
vector<ll> flags(2 * N, 0);
inline void Update(ll r, ll pi, ll left, ll right) {  // [left, right]
  flags[left]++;
  flags[right + 1]--;
}

vector<tuple<ll, ll, ll, ll>> queries(N);  // <r, s, i, ans> // 记录第 i 查询的轮次 r 和值 s 的答案 ans
ll queryIndex = 0;                         // 查询的索引
void Merge(ll R) {
  ll sum = 0;
  ll offset = 0;
  preList.clear();  // 清空上一轮接龙的结果
  preListNum = 0;
  for (ll i = 0; i < n; i++) {
    const auto [piLeft, piRight] = ranges[i];  // [piLeft, piRight)
    for (ll j = piLeft; j < piRight; j++, offset++) {
      ll S = nums[j].second;
      sum += flags[offset];
      if (sum > 0) {
        preList[preListNum++] = {S, i};
        if (preFlag[S] == -1) {
          // printf("R=%lld S=%lld P=%lld\n", R, S, i + 1);
          preFlag[S] = i;  // 记录这个值可以结尾
        } else {
          if (preFlag[S] != i) {  // 如果已经有了，说明有多个人接龙到这个值
            preFlag[S] = -2;      // 标记为多个人
          }
        }
      }
    }
  }
  while (queryIndex < q) {
    auto [r, S, i, _] = queries[queryIndex];
    if (r != R) break;  // 如果查询的轮次大于当前轮次，直接跳过
    if (preFlag[S] != -1) {
      queries[queryIndex] = {r, S, i, 1};
    }
    queryIndex++;
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
    for (ll i = 0; i < n; i++) {
      ll l;
      scanf("%lld", &l);
      ranges[i] = {sum, sum + l};
      for (ll j = 0; j < l; j++) {
        ll S;
        scanf("%lld", &S);
        maxS = max(maxS, S);  // 记录最大的值
        nums[sum + j] = {i, S};
        valToPersonPos[S].emplace_back(i, sum + j);  // 记录每个值在哪些人和位置出现
      }
      sum += l;
    }

    R = 1;
    for (ll i = 0; i < q; i++) {
      ll r, v;
      scanf("%lld%lld", &r, &v);
      queries[i] = {r, v, i, 0};  // 记录查询的轮次 r 和值 v
      R = max(R, r);
    }
    queryIndex = 0;
    sort(queries.begin(), queries.begin() + q);  // 按照轮次 r 排序

    flags.resize(sum + 2, 0);
    preListNum = 0;
    preList[preListNum++] = {1, -1};           // 初始状态，1 号值可以开始接龙
    fill(preFlag.begin(), preFlag.end(), -1);  // 清空上一轮接龙的标记
    preFlag[1] = -2;                           // 初始状态，1 号值可以开始接龙
    for (ll r = 1; r <= R; r++) {              // 进行 R 轮游戏
      fill(flags.begin(), flags.end(), 0);     // 清空标记数组
      for (int i = 0; i < preListNum; i++) {
        auto [S, pos] = preList[i];
        preFlag[S] = -1;  // 清空上一轮接龙的标记
        // 上一轮接龙，编号为 pos 的人以 v 结尾
        for (const auto& [pi, offset] : valToPersonPos[S]) {
          const auto [piLeft, piRight] = ranges[pi];  // [piLeft, piRight)
          if (pi == pos) continue;                    // 不能接自己的
          if (offset + 1 == piRight) continue;        // 不能接到最后一个
          ll left = offset + 1;
          ll right = min(offset + k - 1, piRight - 1);  // 下一个值
          Update(r, pi, left, right);                   // 第 r 轮，第 pi 个人，从 left 到 right 接龙的结束位置
        }
      }
      Merge(r);  // 第 r 轮结束后，合并所有人的接龙结果
    }
    sort(queries.begin(), queries.begin() + q, [](const auto& a, const auto& b) {
      return get<2>(a) < get<2>(b);  // 按照值 i 排序
    });
    for (ll i = 0; i < q; i++) {
      auto [r, S, idx, ans] = queries[i];
      // printf("r=%lld S=%lld idx=%lld ", r, S, idx);
      printf("%lld\n", ans);
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