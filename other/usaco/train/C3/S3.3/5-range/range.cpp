/*
ID: tiankonguse
TASK: range
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "range"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK);
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

char str[300][300];
int n;
vector<int> ans;
int bottom[330][330];

void Solver() {  //
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
  }
  for (int j = 0; j < n; j++) {
    int lastOne = n - 1;
    for (int i = n - 1; i >= 0; i--) {
      if (str[i][j] == '0') {
        lastOne = i - 1;
      }
      bottom[i][j] = lastOne;
    }
  }
  ans.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (str[i][j] == '0') continue;
      int H = n;
      for (int k = j; k < n; k++) {
        const int edge = k - j + 1;
        const int h = bottom[i][k] - i + 1;
        H = min(H, h);
        if (edge > H) break;
        ans[edge]++;
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    if (ans[i] == 0) break;
    printf("%d %d\n", i, ans[i]);
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