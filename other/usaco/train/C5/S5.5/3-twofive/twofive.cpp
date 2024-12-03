/*
ID: tiankonguse
TASK: twofive
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "twofive"
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

ll dp[6][6][6][6][6];

ll Dfs(int s[]) {
  auto& ret = dp[s[1]][s[2]][s[3]][s[4]][s[5]];
  if (ret != -1) return ret;
  ret = 0;
  for (int i = 5; i > 0; i--) {
    if (s[i] > s[i - 1]) {  // 可以选择
      s[i]--;
      ret += Dfs(s);
      s[i]++;
    }
  }
  if (ret == 0) {
    ret = 1;
  }
  return ret;
}

vector<string> dicts = {"", "UPKFA", "VQLGB", "WRMHC", "XSNID", "YTOJE"};

char op[10];
void Solver() {  //
  int states[6] = {0, 5, 5, 5, 5, 5};
  memset(dp, -1, sizeof(dp));
  Dfs(states);

  scanf("%s", op);
  if (op[0] == 'N') {
    int m;
    scanf("%d", &m);

    string ans;
    while (states[5]) {
      for (int i = 5; i > 0; i--) {
        if (states[i] > states[i - 1]) {  // 可以选择 states[i]
          ll num = Dfs(states);           // [1, num]
          if (num >= m) {
            states[i]--;  // 选择
            ans.push_back(dicts[i][states[i]]);
            break;
          } else {
            m -= num;
          }
        }
      }
    }
    printf("%s\n", ans.data());

  } else {
    char str[40];
    scanf("%s", str);
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