/*
ID: tiankonguse
TASK: theme
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "theme"
#define TASKEX "-v2"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod7 = 1000000007,
          mod9 = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
int n;
int nums[5001];
const int B7 = 197;
const int B9 = 199;
pair<pair<ll, ll>, int> H[5001];
int hnum;
void Solver() {  //
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
    if (i) {
      nums[i - 1] = nums[i] - nums[i - 1] + 89;
    }
  }
  if (n <= 9) {
    printf("%d\n", 0);
    return;
  }

  vector<pair<ll, ll>> h(n + 1, {0, 0});
  const int m = n - 1;
  int ans = 0;
  const int maxLen = n / 2;
  for (int j = 1; j <= maxLen; j++) {
    const int len = j + 2;
    for (int i = 0; i < j; i++) {  // 枚举长度
      for (int k = i; k < m; k += j) {
        const int l = k;
        h[i].first = (h[i].first * B7 + nums[i + k]) % mod7;
        h[i].second = (h[i].second * B9 + nums[i + k]) % mod9;
      }
    }
    hnum = 0;
    for (int i = 0; i + j < m; i++) {
      const int l = i;
      h[i].first = (h[i].first * B7 + nums[i + j]) % mod7;
      h[i].second = (h[i].second * B9 + nums[i + j]) % mod9;
      if (len >= 5) {
        H[hnum++] = {h[i], l};
      }
    }
    if (hnum <= 1) {
      continue;
    }
    sort(H, H + hnum);
    bool flag = false;
    for (int i = 0; i < hnum;) {
      const auto val = H[i].first;
      const int l = H[i].second;
      const int r = l + len - 1;
      while (i < hnum && val == H[i].first) {
        i++;
      }
      const int L = H[i - 1].second;
      if (r < L && len > ans) {
        flag = true;
        ans = len;
      }
    }
    if (!flag) break;
  }

  printf("%d\n", ans);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/