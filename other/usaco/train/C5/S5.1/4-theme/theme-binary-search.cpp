/*
ID: tiankonguse
TASK: theme
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "theme"
#define TASKEX "-binary-search"

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
pair<pair<ll, ll>, ll> hashNums[5001];
int hnum;
int m;

bool Check(int j) {
  const int len = j + 1;  // 实际长度
  hnum = 0;
  for (int i = 0; i < m; i++) {
    const int l = i;
    const int k = i + j - 1;
    if (k >= m) break;
    hashNums[hnum++] = {H(l, k), l};
    // if (len == 7) {
    //   printf("[%d,%d] diff range(%d,%d) [%lld,%lld]\n", l, k + 1, l, k,
    //          h[i].first, h[i].second);
    // }
  }
  sort(hashNums, hashNums + hnum);
  for (int i = 0; i < hnum;) {
    const auto val = hashNums[i].first;
    const int l = hashNums[i].second;
    const int r = l + len - 1;
    while (i < hnum && val == hashNums[i].first) {
      i++;
    }
    const int L = hashNums[i - 1].second;
    if (r < L) {
      return true;
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

  int ans = 0;
  // const int maxLen = n / 2;
  int l = 4, r = n;
  while (l < r) {
    int mid = (l + r) / 2;
    if (Check(mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  ans = r;

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
21 
10 1 1 3 4 5 6 7 8 10 10 1 1 3 4 5 6 7 8 10 
10 
=> 10

40 
31 62 34 47 8 25 35 57 8 81 14 39 45 25 55 73 79 43 18 59 
80 14 77 56 46 4 42 85 25 75 51 55 24 41 72 44 57 18 35 45
=>7

30
25 27 30 34 39 45 52 60 69 79 69 60 52 45 39 34 30 26 22 18
82 78 74 70 66 67 64 60 65 80
=> 5

137 
55 20 10 45 4 56 56 16 88 79 65 31 59 18 5 83 72 75 4 72 
59 12 25 22 53 64 66 60 8 11 70 62 31 55 18 10 22 73 2 86 
39 66 4 73 84 72 67 43 58 71 26 4 58 51 26 87 2 67 58 9 
77 15 70 83 70 87 69 67 47 70 64 85 47 44 45 18 27 87 60 85 
69 86 64 15 24 65 13 25 43 46 9 8 60 78 66 17 52 46 84 74 
27 35 46 50 78 2 43 17 88 15 77 45 76 52 35 11 29 47 11 47 
68 83 54 39 48 32 56 75 53 27 60 80 61 17 17 51 18 
4=>0

Executing...
   Test 1: TEST OK [0.004 secs limit:1s, 1688 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1684 KB]
   Test 3: TEST OK [0.007 secs limit:1s, 1756 KB]
   Test 4: TEST OK [0.004 secs limit:1s, 1684 KB]
   Test 5: TEST OK [0.007 secs limit:1s, 1684 KB]
   Test 6: TEST OK [0.004 secs limit:1s, 1624 KB]
   Test 7: TEST OK [0.007 secs limit:1s, 1688 KB]
   Test 8: TEST OK [0.007 secs limit:1s, 1684 KB]
   Test 9: TEST OK [0.014 secs limit:1s, 1684 KB]
   Test 10: TEST OK [0.004 secs limit:1s, 1684 KB]
   Test 11: TEST OK [0.025 secs limit:3.5s, 3292 KB]
   Test 12: TEST OK [0.028 secs limit:3.5s, 3256 KB]
   Test 13: TEST OK [0.028 secs limit:4.0s, 3216 KB]
   Test 14: TEST OK [0.021 secs limit:3.5s, 3244 KB]
   Test 15: TEST OK [0.028 secs limit:3.5s, 3196 KB]
 */