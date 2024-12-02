/*
ID: tiankonguse
TASK: hidden
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "hidden"
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
const int maxn = 300010;
int wx[maxn], wy[maxn], *x, *y, wss[maxn], wv[maxn];

bool cmp(int *r, int n, int a, int b, int l) {
  return a + l < n && b + l < n && r[a] == r[b] && r[a + l] == r[b + l];
}
void da(int str[], int sa[], int rank[], int height[], int n, int m) {
  int *s = str;
  int *x = wx, *y = wy, *t, p;
  int i, j;
  for (i = 0; i < m; i++) wss[i] = 0;
  for (i = 0; i < n; i++) wss[x[i] = s[i]]++;
  for (i = 1; i < m; i++) wss[i] += wss[i - 1];
  for (i = n - 1; i >= 0; i--) sa[--wss[x[i]]] = i;
  for (j = 1, p = 1; p < n && j < n; j *= 2, m = p) {
    for (i = n - j, p = 0; i < n; i++) y[p++] = i;
    for (i = 0; i < n; i++)
      if (sa[i] - j >= 0) y[p++] = sa[i] - j;
    for (i = 0; i < n; i++) wv[i] = x[y[i]];
    for (i = 0; i < m; i++) wss[i] = 0;
    for (i = 0; i < n; i++) wss[wv[i]]++;
    for (i = 1; i < m; i++) wss[i] += wss[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wss[wv[i]]] = y[i];
    for (t = x, x = y, y = t, p = 1, i = 1, x[sa[0]] = 0; i < n; i++)
      x[sa[i]] = cmp(y, n, sa[i - 1], sa[i], j) ? p - 1 : p++;
  }
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  for (int i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
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