/*
ID: tiankonguse
TASK: F.最短超弦
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/F
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤4 » 实践
submission: https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/submission/297386680
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

void z_function(char* s, int n, int* z) {  //
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < n; i++) {
    z[i] = 0;
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
}

const int N = 2e6 + 10;
char S[N];
char T[N];
int Z_ST[N];
int Z_TS[N];
int q;
void InitIO() {  //
  scanf("%d", &q);
}

int ansLen = INT_MAX;
int ans1Left = 0, ans1Right = 0;
char* ans1Point = nullptr;
int ans2Left = 0, ans2Right = 0;
char* ans2Point = nullptr;

void Update(char* p1, int l1, int r1, char* p2, int l2, int r2) {  // [l, r)
  int len = r1 - l1 + r2 - l2;
  if (len < ansLen) {
    ansLen = len;

    ans1Left = l1;
    ans1Right = r1;
    ans1Point = p1;

    ans2Left = l2;
    ans2Right = r2;
    ans2Point = p2;
  }
}

void Solver(char* S, char* T) {
  int sn = strlen(S);
  int tn = strlen(T);
  if (sn < tn) {  // 保证 |S| >= |T|
    swap(sn, tn);
    swap(S, T);
  }
  ansLen = INT_MAX;
  Update(S, 0, sn, T, 0, tn);

  // S$T
  int stn = sn;
  S[stn++] = '$';
  for (int i = 0; i < tn; i++) {
    S[stn++] = T[i];
  }
  S[stn] = '\0';

  int tsn = tn;
  T[tsn++] = '$';
  for (int i = 0; i < sn; i++) {
    T[tsn++] = S[i];
  }
  T[tsn] = '\0';

  z_function(S, stn, Z_ST);
  z_function(T, tsn, Z_TS);

  // printf("S:%s sn=%d stn=%d\n", S, sn, stn);
  // printf("T:%s tn=%d tsn=%d\n", T, tn, tsn);
  // 判断 S 是否包含 T
  for (int i = tn + 1; i < tsn; i++) {  // 保证 |S| >= |T|
    // printf("Z_TS[%d]=%d\n", i, Z_TS[i]);
    if (Z_TS[i] == tn) {  // 答案就是 S
      Update(S, 0, sn, T, 0, 0);
      return;
    }
  }

  for (int i = sn + 1; i < stn; i++) {  // S$T => pre(T) + mid(T,S) + suf(S)
    if (i + Z_ST[i] == stn) {
      int mid = Z_ST[i];
      Update(T, 0, tn, S, mid, sn);
    }
  }
  for (int i = tn + 1; i < tsn; i++) {  // T$S => pre(S) + mid(S,T) + suf(T)
    if (i + Z_TS[i] == tsn) {
      int mid = Z_TS[i];
      Update(S, 0, sn, T, mid, tn);
    }
  }
}

void Solver() {  //
  while (q--) {
    scanf("%s%s", S, T);
    Solver(S, T);
    ans1Point[ans1Right] = '\0';
    ans2Point[ans2Right] = '\0';
    printf("%s%s\n", ans1Point + ans1Left, ans2Point + ans2Left);
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