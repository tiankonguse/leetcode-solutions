/*
ID: tiankonguse
TASK: race3
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "race3"
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

vector<vector<int>> g;
int rowNum = 0;

bool readLine() {
  int v;
  do {
    scanf("%d", &v);
    if (v == -1) {
      return false;
    } else if (v == -2) {
      return true;
    } else {
      g[rowNum].push_back(v);
    }
  } while (true);
}

vector<int> flag;
bool check(const int S, const int T, const int C, const int flagVal) {
  queue<int> que;
  que.push(S);
  flag[S] = flagVal;
  while (!que.empty()) {
    auto u = que.front();
    que.pop();
    for (auto v : g[u]) {
      if (v == T) return false;
      if (v == C) continue;
      if (flag[v] > 0) {
        if (flag[v] == flagVal) continue;  // 第一遍，肯定都相等
        return false;  // 第二遍，不相等，说明联通
      }
      flag[v] = flagVal;
      que.push(v);
    }
  }
  return true;
}

void Solver() {  //
  g.resize(55);

  rowNum = 0;
  while (readLine()) {
    rowNum++;
  }

  const int S = 0;
  const int T = rowNum - 1;
  vector<int> ans1;
  vector<int> ans2;

  for (int i = 1; i + 1 < rowNum; i++) {
    flag.clear();
    flag.resize(rowNum, 0);
    if (check(S, T, i, 1)) {
      ans1.push_back(i);
      if (check(i, -1, -1, 2)) {
        ans2.push_back(i);
      }
    }
  }
  int ansNum1 = ans1.size();
  int ansNum2 = ans2.size();
  printf("%d", ansNum1);
  for (auto v : ans1) {
    printf(" %d", v);
  }
  printf("\n");
  printf("%d", ansNum2);
  for (auto v : ans2) {
    printf(" %d", v);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
0: 1 -2 
1: 2 1 -2 
2: 3 0 -2 
3: 3 4 -2 
4: 5 0 -2 
5: 7 6 -2 
6: 7 -2 
7: 8 -2 
8: -2 
*/