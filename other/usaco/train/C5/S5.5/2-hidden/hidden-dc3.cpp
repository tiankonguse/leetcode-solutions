/*
ID: tiankonguse
TASK: hidden
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "hidden"
#define TASKEX "-dc3"

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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
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
const int maxn = 300010;  // 所有下标都是0~n-1，height[0]无意义。
// 所有相关数组都要开三倍
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
int wa[maxn * 3], wb[maxn * 3], wv[maxn * 3], sa_ws[maxn * 3];
int c0(int *r, int a, int b) {
  return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
int c12(int k, int *r, int a, int b) {
  if (k == 2)
    return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
  else
    return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
}
void sort(int *r, int *a, int *b, int n, int m) {
  int i;
  for (i = 0; i < n; i++) wv[i] = r[a[i]];
  for (i = 0; i < m; i++) sa_ws[i] = 0;
  for (i = 0; i < n; i++) sa_ws[wv[i]]++;
  for (i = 1; i < m; i++) sa_ws[i] += sa_ws[i - 1];
  for (i = n - 1; i >= 0; i--) b[--sa_ws[wv[i]]] = a[i];
  return;
}
void dc3(int *r, int *sa, int n, int m) {
  int i, j, *rn = r + n;
  int *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
  r[n] = r[n + 1] = 0;
  for (i = 0; i < n; i++)
    if (i % 3 != 0) wa[tbc++] = i;
  sort(r + 2, wa, wb, tbc, m);
  sort(r + 1, wb, wa, tbc, m);
  sort(r, wa, wb, tbc, m);
  for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
    rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
  if (p < tbc)
    dc3(rn, san, tbc, p);
  else
    for (i = 0; i < tbc; i++) san[rn[i]] = i;
  for (i = 0; i < tbc; i++)
    if (san[i] < tb) wb[ta++] = san[i] * 3;
  if (n % 3 == 1) wb[ta++] = n - 1;
  sort(r, wb, wa, ta, m);
  for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
  for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
    sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
  for (; i < ta; p++) sa[p] = wa[i++];
  for (; j < tbc; p++) sa[p] = wb[j++];
}
//`str和sa也要三倍`
void da(int str[], int sa[], int rank[], int height[], int n, int m) {
  for (int i = n; i < n * 3; i++) str[i] = 0;
  dc3(str, sa, n + 1, m);
  int i, j, k;
  for (i = 0; i < n; i++) {
    sa[i] = sa[i + 1];
    rank[sa[i]] = i;
  }
  for (i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
    if (rank[i] > 0)
      for (k ? k-- : 0, j = sa[rank[i] - 1];
           i + k < n && j + k < n && str[i + k] == str[j + k]; k++);
}

int str[maxn], sa[maxn], sa_rank[maxn], sa_height[maxn];

int n;
char input[100];
string s;
void Solver() {  //
  scanf("%d", &n);
  int len = 0;
  while (len < n) {
    scanf("%s", input);
    for (int i = 0; input[i]; i++, len++) {
      str[len] = input[i];
    }
  }
  for (int i = 0; i < n; i++, len++) {
    str[len] = str[i];
  }
  str[len++] = 127;

  da(str, sa, sa_rank, sa_height, len, 128);
  //   for (int i = 0; i < len; i++) {
  //     printf("i=%d sa=%d rank=%d height=%d\n", i, sa[i], sa_rank[i],
  //            sa_height[i]);
  //   }
  printf("%d\n", sa[0]);
}

int main(int argc, char **argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/