/*
ID: tiankonguse
TASK: point
LANG: C++
https://www.luogu.com.cn/problem/P8814
*/
#define TASK "point"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
constexpr int INF = 1 << 30;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

using int128 = __int128;

void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

int n, K;
vector<pair<ll, ll>> nums;
int dp[510][110];

inline bool Less(pair<ll, ll> a, pair<ll, ll> b) {  //
  return a.first <= b.first && a.second <= b.second;
}
inline int Dis(pair<ll, ll> a, pair<ll, ll> b) {  //
  return abs(a.first - b.first) + abs(a.second - b.second);
}
void Solver() {  //
  scanf("%d%d", &n, &K);
  nums.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &nums[i].first, &nums[i].second);
  }
  sort(nums.begin() + 1, nums.end());
  memset(dp, 0, sizeof(dp));
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k <= K; k++) {
      dp[i][k] = 1 + k;              // 1个输入点 + k 个自由点
      for (int j = 1; j < i; j++) {  // 尝试连接 j -> i
        if (!Less(nums[j], nums[i])) continue;
        const int d = Dis(nums[j], nums[i]);
        const int useK = d - 1;
        if (k < useK) continue;  // 自由点不够
        dp[i][k] = max(dp[i][k], dp[j][k - useK] + d);
      }
      ans = max(ans, dp[i][k]);
    }
  }
  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
