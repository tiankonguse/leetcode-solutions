/*
ID: tiankonguse
TASK: theme
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "theme"
#define TASKEX "-step"

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

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod7 = 1000000007,
          mod9 = 1000000007;
const int max3 = 5010, max4 = 20010, max5 = 200010, max6 = 2000010;

const int B7 = 197;
const int B9 = 199;
ll MOD[2] = {mod7, mod9};
ll BASE[2] = {197, 199};
ll h[2][max3];
ll qpowCache[2][max3];

pair<ll, ll> H(int l, int r) {
  ll ans[2];
  for (int i = 0; i < 2; i++) {
    if (l == 0) {
      ans[i] = h[i][r];
    } else {
      ll pre = h[i][l - 1] * qpowCache[i][r - l + 1] % MOD[i];
      ans[i] = (h[i][r] - pre + MOD[i]) % MOD[i];
    }
  }
  return {ans[0], ans[1]};
}

void InitHash(const int* str, int n) {
  for (int k = 0; k < 2; k++) {
    qpowCache[k][0] = 1;
    for (int i = 1; i <= n; i++) {
      qpowCache[k][i] = (qpowCache[k][i - 1] * BASE[k]) % MOD[k];
    }

    ll pre = 0;
    for (int i = 0; i < n; i++) {
      pre = (pre * BASE[k] + str[i]) % MOD[k];
      h[k][i] = pre;
    }
  }
}

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
pair<ll, ll> hashNums[5001];
int hnum;
int m;

bool Check(int j) {
  const int len = j + 1;                           // 实际长度
  for (int offset = 0; offset <= len; offset++) {  // 枚举循环节的偏移量
    int hnum = 0;
    if (len == 7) printf("offset[%d]", offset);
    for (int pos = offset; pos < m;
         pos += len) {    // 统计循环节内相同偏移量的hash
      const int l = pos;  // [k, k+j-1]
      const int r = pos + len - 2;
      if (r > m) continue;
      if (len == 7) {
        printf("->%d", pos);
      }
      if (len >= 5) {
        hashNums[hnum++] = H(l, r);
      }
    }
    if (len == 7) printf("\n");
    sort(hashNums, hashNums + hnum);
    for (int k = 1; k < hnum; k++) {
      if (hashNums[k - 1] == hashNums[k]) {
        return true;
      }
    }
  }
  return false;
}

void Solver() {  //
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
    if (i) {
      nums[i - 1] = nums[i] - nums[i - 1] + 89;
    }
  }

  m = n - 1;
  InitHash(nums, m);
  // for (int i = 0; i + 5 < m; i++) {
  //   int l = i;
  //   int r = i + 5;
  //   auto v = H(i, i + 5);
  //   printf("[%d,%d] diff range(%d,%d) [%lld,%lld]\n", l, i + 6, l, r, v.first,
  //          v.second);
  // }

  int ans = 0;
  const int maxLen = n / 2;
  for (int j = maxLen; j >= 1; j--) {  // 枚举 diff 长度
    if (Check(j)) {
      ans = j + 1;
      break;
    }
  }

  if (ans < 5) {
    ans = 0;
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