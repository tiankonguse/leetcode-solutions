/*
ID: tiankonguse
TASK: B. 求 5D 的和
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/3/lesson/10/3/practice/contest/324368/problem/B
PATH: 社区课程 » 前缀和与差数组 » 步骤3 » 实践
submission: https://codeforces.com/edu/course/3/lesson/10/3/practice/contest/324368/submission/296407470
soulution: 计算前缀和 与 计算区间和是等价的
初始化：前缀和 = 大小为1的区间 + 不包含大小为1的区间
求答案：大小为1的区间和 = 前缀和 - 不包含大小为1的区间
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int n1, n2, n3, n4, n5;
ll g[16][16][16][16][16];
void InitIO() {  //
  scanf("%d%d%d%d%d", &n1, &n2, &n3, &n4, &n5);
  for (int i1 = 0; i1 < n1; i1++) {
    for (int i2 = 0; i2 < n2; i2++) {
      for (int i3 = 0; i3 < n3; i3++) {
        for (int i4 = 0; i4 < n4; i4++) {
          for (int i5 = 0; i5 < n5; i5++) {
            scanf("%lld", &g[i1][i2][i3][i4][i5]);
          }
        }
      }
    }
  }
}

ll G[17][17][17][17][17];

int P[5];
ll RongChi(const vector<int>& R, const vector<int>& L, const int lev,
           const int firstNum = 0) {
  if (lev == 5) {
    int sign = firstNum % 2 == 0 ? 1 : -1;
    return sign * G[P[0]][P[1]][P[2]][P[3]][P[4]];
  }
  ll ans = 0;
  P[lev] = R[lev];  // 选择 R
  ans += RongChi(R, L, lev + 1, firstNum);

  P[lev] = L[lev];  // 选择 R
  ans += RongChi(R, L, lev + 1, firstNum + 1);
  return ans;
}

void Solver() {  //
  memset(G, 0, sizeof(G));
  vector<int> L(5), R(5);
  for (int i1 = 0; i1 < n1; i1++) {
    for (int i2 = 0; i2 < n2; i2++) {
      for (int i3 = 0; i3 < n3; i3++) {
        for (int i4 = 0; i4 < n4; i4++) {
          for (int i5 = 0; i5 < n5; i5++) {
            R = {i1 + 1, i2 + 1, i3 + 1, i4 + 1, i5 + 1};
            L = {i1, i2, i3, i4, i5};

            ll tmp = RongChi(R, L, 0);
            G[i1 + 1][i2 + 1][i3 + 1][i4 + 1][i5 + 1] =
                g[i1][i2][i3][i4][i5] - tmp;
          }
        }
      }
    }
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    for (int i = 0; i < 5; i++) {
      scanf("%d", &L[i]);
      L[i]--;
    }
    for (int i = 0; i < 5; i++) {
      scanf("%d", &R[i]);
    }
    printf("%lld\n", RongChi(R, L, 0));
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  InitIO();
  ExSolver();
  return 0;
}

/*

*/