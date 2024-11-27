/*
ID: tiankonguse
TASK: theme
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "theme"
#define TASKEX ""

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
vector<int> nums;
const int B7 = 197;
const int B9 = 199;
pair<pair<ll, ll>, int> H[5010];
int hnum;
void Solver() {  //
  scanf("%d", &n);
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  if (n <= 9) {
    printf("%d\n", 0);
    return;
  }
  for (int i = 1; i < n; i++) {
    nums[i - 1] = nums[i] - nums[i - 1] + 89;
  }

  vector<pair<ll, ll>> h(n + 1, {0, 0});
  int m = n - 1;
  int ans = 0;
  int maxLen = n / 2;
  for (int j = 0; j < maxLen; j++) {
    const int len = j + 2;
    hnum = 0;
    for (int i = 0; i + j < m; i++) {
      const int l = i;
      const int k = i + j;
      h[i].first = (h[i].first * B7 + nums[k]) % mod7;
      h[i].second = (h[i].second * B9 + nums[k]) % mod9;
      if (len >= 5) {
        H[hnum++] = {h[i], l};
      }
      if (len == 7) {
        printf("[%d,%d] diff range(%d,%d) [%lld,%lld]\n", l, k + 1, l, k,
               h[i].first, h[i].second);
      }
    }
    if (hnum <= 1) {
      continue;
    }

    sort(H, H + hnum);
    for (int i = 0; i < hnum;) {
      const auto val = H[i].first;
      const int l = H[i].second;
      const int r = l + len - 1;
      while (i < hnum && val == H[i].first) {
        i++;
      }
      const int L = H[i - 1].second;
      if (r < L && len > ans) {
        if (len == 7) {
          printf("val=%lld,%lld\n", val.first, val.second);
        }
        ans = len;
      }
    }
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
Executing...
   Test 1: TEST OK [0.007 secs limit:1s, 1688 KB]
   Test 2: TEST OK [0.007 secs limit:1s, 1756 KB]
   Test 3: TEST OK [0.011 secs limit:1s, 1684 KB]
   Test 4: TEST OK [0.007 secs limit:1s, 1688 KB]
   Test 5: TEST OK [0.004 secs limit:1s, 1752 KB]
   Test 6: TEST OK [0.004 secs limit:1s, 1688 KB]
   Test 7: TEST OK [0.014 secs limit:1s, 1688 KB]
   Test 8: TEST OK [0.060 secs limit:1s, 1752 KB]
   Test 9: TEST OK [0.311 secs limit:1s, 1696 KB]
   Test 10: TEST OK [0.004 secs limit:1s, 1620 KB]
   Test 11: TEST OK [2.702 secs limit:3.5s, 3372 KB]
   Test 12: TEST OK [2.590 secs limit:3.5s, 3300 KB]
   Test 13: TEST OK [1.817 secs limit:4.0s, 3312 KB]
   Test 14: TEST OK [3.133 secs limit:3.5s, 3308 KB]
   Test 15: TEST OK [3.160 secs limit:3.5s, 3384 KB]
*/