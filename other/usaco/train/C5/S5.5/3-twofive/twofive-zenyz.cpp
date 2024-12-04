/*
ID: tiankonguse
TASK: twofive
LANG: C++
MAC EOF: ctrl+D
DESC: https://www.cnblogs.com/Zenyz/p/10311267.html
*/
#define TASK "twofive"
#define TASKEX "-zenyz"

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

int S[26], ans;

inline bool check(int letter, int pos) {
  return (!S[pos]) || (letter == S[pos]);
}

int f[6][6][6][6][6];
bool ok[30];
int dfs(int a, int b, int c, int d, int e, int letter) {
  if (letter > 25) return 1;
  if (f[a][b][c][d][e]) return f[a][b][c][d][e];
  int cnt = 0;
  if (a < 5 && check(letter, a + 1)) {
    cnt += dfs(a + 1, b, c, d, e, letter + 1);
  }
  if (b < a && check(letter, b + 6)) {
    cnt += dfs(a, b + 1, c, d, e, letter + 1);
  }
  if (c < b && check(letter, c + 11)) {
    cnt += dfs(a, b, c + 1, d, e, letter + 1);
  }
  if (d < c && check(letter, d + 16)) {
    cnt += dfs(a, b, c, d + 1, e, letter + 1);
  }
  if (e < d && check(letter, e + 21)) {
    cnt += dfs(a, b, c, d, e + 1, letter + 1);
  }
  return f[a][b][c][d][e] = cnt;
}

char op[10];
void Solver() {  //
  scanf("%s", op);
  if (op[0] == 'N') {
    int num;
    scanf("%d", &num);
    int preNum = 0;
    string ans;
    for (int i = 1; i <= 25; i++) {
      for (S[i] = 1;; S[i]++) {
        if (ok[S[i]]) continue;
        ok[S[i]] = 1;
        memset(f, 0, sizeof(f));  // 记得清零
        int tmp = dfs(0, 0, 0, 0, 0, 1);
        if (preNum + tmp >= num) {
          ans.push_back('A' + S[i] - 1);
          break;
        }
        preNum += tmp;
        ok[S[i]] = 0;
      }
    }
    printf("%s\n", ans.data());
  } else {
    char str[40];
    scanf("%s", str);
    string s = str;
    ll ans = 1;
    for (int i = 0; i < 25; i++) {
      for (S[i + 1] = 1; S[i + 1] <= s[i] - 'A'; S[i + 1]++) {
        if (ok[S[i + 1]]) continue;
        ok[S[i + 1]] = 1;
        memset(f, 0, sizeof(f));
        ans += dfs(0, 0, 0, 0, 0, 1);
        ok[S[i + 1]] = 0;
      }
    }
    printf("%lld\n", ans);
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/