/*
ID: tiankonguse
TASK: charrec
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "charrec"
#define FONT "font"
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

const int N = 1210;
const int C20 = 20;
enum { E19 = 0, E20 = 1, E21 = 2 };
enum { V19 = C20 - 1, V20 = C20, V21 = C20 + 1 };
int F = 27;
int lines[N];
const string S = "  abcdefghijklmnopqrstuvwxyz";

char str[22];
int ReadLine() {
  scanf("%s", str);
  int v = 0;
  for (int j = 0; j < C20; j++) {
    if (str[j] == '1') {
      v |= 1 << j;
    }
  }
  return v;
}

struct Font {
  int bits[20];
  char v;
  void Input(const char v) {
    this->v = v;
    for (int i = 0; i < C20; i++) {
      bits[i] = ReadLine();
    }
  }
} fonts[30];

void InitFont() {
#ifndef USACO_LOCAL_JUDGE
  freopen(FONT ".in", "r", stdin);
#endif
  int _;
  scanf("%d", &_);
  for (int i = 1; i <= F; i++) {
    fonts[i].Input(S[i]);
  }
}

int RangeType(int n) { return n - V19; }
int Solver(const int l, const int n, const int k) {  //
  auto& font = fonts[k];
  int ans = 0;
  if (n == V19) {  // 少一行
    ans = INT_MAX;
    for (int i = 0; i < C20; i++) {  // 枚举缺的行数
      int ret = 0;
      for (int j = 0, p = l; j < C20; j++, p++) {
        if (j == i) {
          p--;  // 少了第 i 行，不能加
          continue;
        }
        int v = lines[p] ^ font.bits[j];
        ret += __builtin_popcount(v);
      }
      ans = min(ans, ret);
    }
  } else if (n == V20) {  // 精确匹配
    ans = 0;
    int ret = 0;
    for (int j = 0, p = l; j < C20; j++, p++) {
      int v = lines[p] ^ font.bits[j];
      ret += __builtin_popcount(v);
    }
    ans = ret;
  } else {
    ans = INT_MAX;
    for (int i = 0; i < C20; i++) {  // 枚举多的行数
      int ret = 0;
      for (int j = 0, p = l; j < C20; j++, p++) {
        if (i == j) {
          int v1 = lines[p] ^ font.bits[j];
          p++;  // 重复行，多加1次
          int v2 = lines[p] ^ font.bits[j];
          ret += min(__builtin_popcount(v1), __builtin_popcount(v2));
        } else {
          int v = lines[p] ^ font.bits[j];
          ret += __builtin_popcount(v);
        }
      }
      ans = min(ans, ret);
    }
  }
  //   ans/400 <= 30/100
  if (ans * 100 <= 30 * 400) {
    return ans;
  }
  return -1;
}

vector<vector<pair<int, char>>> dpRange;
pair<int, char> Solver(int l, int n) {
  const int cv = RangeType(n);
  auto& [ret, c] = dpRange[l][cv];
  if (ret != INT_MAX) return dpRange[l][cv];

  for (int i = 1; i <= F; i++) {
    int retFont = Solver(l, n, i);
    // printf("dpRange l=%d n=%d i=%d[%c] ret=%d\n", l, n, i, S[i], retFont);
    if (retFont != -1) {
      if (retFont < ret) {
        ret = retFont;
        c = S[i];
      }
    }
  }

  if (ret == INT_MAX) {
    ret = -1;
  }
  //   printf("dpRange l=%d n=%d ret=%d c=[%c]\n", l, n, ret, c);
  return dpRange[l][cv];
}

vector<pair<int, string>> dpLine;
const pair<int, string> rmptyLine = {0, ""};
const pair<int, string>& Dfs(int n) {  // 前 n 行的最优答案
  if (n == 0) return rmptyLine;        // 出口
  auto& [ret, buf] = dpLine[n];
  if (ret != INT_MAX) return dpLine[n];

  for (int i = V19; i <= n && i <= V21; i++) {
    const auto& [retLine, retBuf] = Dfs(n - i);
    const auto& [retRange, c] = Solver(n - i + 1, i);
    if (retLine != -1 && retRange != -1) {
      if (retLine + retRange < ret) {
        ret = retLine + retRange;
        buf = retBuf + c;
      }
    }
  }
  if (ret == INT_MAX) {
    ret = -1;
  }
  //   printf("dpLine: n=%d ret=%d buf=%s\n", n, ret, buf.data());
  return dpLine[n];
}

void Solver() {  //
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    lines[i] = ReadLine();
  }
  InitFont();
  dpLine.resize(n + 1, {INT_MAX, ""});
  dpRange.resize(n + 1, vector<pair<int, char>>(E21 + 1, {INT_MAX, ' '}));
  auto ans = Dfs(n);
  //   printf("%d->%s\n", ans.first, ans.second.data());
  printf("%s\n", ans.second.data());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/