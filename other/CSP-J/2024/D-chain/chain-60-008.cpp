/*
ID: tiankonguse
TASK: chain
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11230?contestId=209924
https://www.luogu.com.cn/record/219584688
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

const int N = 2e5 + 10;
int n, k, q;
vector<pair<int, int>> nums;
vector<pair<int, int>> ranges;  // 计算每个人的数字在所有数字里面的范围，[piLeft, piRight)
vector<int> linkList;
vector<int> linkHead;
int maxR;
int maxOffset = 0;

vector<int> preFlag;  // 上一轮接龙时，记录每个值结尾的有哪些人，-1 代表有多个人，否则是人的编号
vector<pair<int, int>> preList;
int preListNum = 0;

// 这里方法很多，例如线段树、权值线段树、树状数组、递减标记法、左加右减标记法
// 这里采用左加右减标记法
vector<int> flags;
inline void Update(int r, int pi, int left, int right) {  // [left, right]
  flags[left]++;
  flags[right + 1]--;
}

vector<tuple<int, int, int, int>> queries;  // <r, s, i, ans> // 记录第 i 查询的轮次 r 和值 s 的答案 ans
int queryIndex = 0;                         // 查询的索引
int maxS = 1;
void Merge(int R) {
  int nowVal = 0;
  preListNum = 0;
  for (int i = 0, offset = 0; i < n; i++) {
    const auto [piLeft, piRight] = ranges[i];  // [piLeft, piRight)
    for (int j = piLeft; j < piRight; j++, offset++) {
      int S = nums[j].second;
      nowVal += flags[offset];
      flags[offset] = 0;  // 清空标记数组
      if (nowVal > 0) {
        preList[preListNum++] = {S, i};  // 记录这个值可以结尾的人
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
  flags[maxOffset] = 0;  // 最后一个置空
  while (queryIndex < q) {
    auto& [r, S, i, ans] = queries[queryIndex];
    if (r != R) break;  // 如果查询的轮次大于当前轮次，直接跳过
    if (preFlag[S] != -1) {
      ans = 1;
    }
    queryIndex++;
  }
}

void Solver() {  //
  nums.resize(2 * N);
  ranges.resize(N);
  queries.resize(N);
  flags.resize(2 * N, 0);      // 初始化标记数组
  preFlag.resize(2 * N, -1);   // 上一轮接龙的标记
  preList.resize(2 * N);       // 上一轮接龙的标记
  linkHead.resize(2 * N, -1);  // 初始化链表头
  linkList.resize(2 * N, -1);
  int t;
  scanf("%d", &t);
  while (t--) {
    // fill(flags.begin(), flags.end(), 0);  // 清空上一轮接龙的标记
    // fill(preFlag.begin(), preFlag.end(), -1);  // 清空上一轮接龙的标记
    // fill(linkHead.begin(), linkHead.end(), -1);  // 清空上一轮接龙的标记
    // fill(linkList.begin(), linkList.end(), -1);  // 清空上一轮接龙的标记
    maxS = 1;
    maxOffset = 0;
    queryIndex = 0;
    maxR = 1;
    preListNum = 0;

    scanf("%d%d%d", &n, &k, &q);
    for (int i = 0, offset = 0; i < n; i++) {
      int l;
      scanf("%d", &l);
      for (int j = 0; j < l; j++, offset++) {
        int S;
        scanf("%d", &S);
        maxS = max(maxS, S);             // 记录最大的值
        linkList[offset] = linkHead[S];  // 将当前值的链表头指向当前值
        linkHead[S] = offset;            // 更新链表头为当前值的位置
        nums[offset] = {i, S};
      }
      ranges[i] = {maxOffset, maxOffset + l};
      maxOffset += l;
    }

    for (int i = 0; i < q; i++) {
      int r, S;
      scanf("%d%d", &r, &S);
      queries[i] = {r, S, i, 0};  // 记录查询的轮次 r 和值 S
      maxR = max(maxR, r);
    }
    sort(queries.begin(), queries.begin() + q);  // 按照轮次 r 排序

    preList[preListNum++] = {1, -2};   // 初始状态，1 号值可以开始接龙
    preFlag[1] = -2;                   // 初始状态，1 号值可以开始接龙
    for (int r = 1; r <= maxR; r++) {  // 进行 R 轮游戏
      for (int i = 0; i < preListNum; i++) {
        auto [S, pos] = preList[i];
        preFlag[S] = -1;  // 清空上一轮接龙的标记

        // 上一轮接龙，编号为 pos 的人以 S 结尾
        for (int offset = linkHead[S]; offset != -1; offset = linkList[offset]) {
          const int pi = nums[offset].first;
          const auto [piLeft, piRight] = ranges[pi];  // [piLeft, piRight)
          if (pi == pos) continue;                    // 不能接自己的
          if (offset + 1 == piRight) continue;        // 不能接到最后一个
          int left = offset + 1;
          int right = min(offset + k - 1, piRight - 1);  // 下一个值
          Update(r, pi, left, right);                    // 第 r 轮，第 pi 个人，从 left 到 right 接龙的结束位置
        }
      }
      Merge(r);  // 第 r 轮结束后，合并所有人的接龙结果
    }
    sort(queries.begin(), queries.begin() + q, [](const auto& a, const auto& b) {
      return get<2>(a) < get<2>(b);  // 按照值 i 排序
    });
    for (int i = 0; i < q; i++) {
      auto [r, S, idx, ans] = queries[i];
      // printf("r=%lld S=%lld idx=%lld ", r, S, idx);
      printf("%d\n", ans);
    }

    // 最后清理，这样下一轮就不需要初始化了
    for (int i = 0; i < preListNum; i++) {
      auto [S, pos] = preList[i];
      preFlag[S] = -1;  // 清空上一轮接龙的标记
    }
    for (int offset = 0; offset < maxOffset; offset++) {
      linkList[offset] = -1;
      linkHead[nums[offset].second] = -1;
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