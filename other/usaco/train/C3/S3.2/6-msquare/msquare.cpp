/*
ID: tiankonguse
TASK: msquare
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "msquare"

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

int t = 0;

const int N = 5000;

/*
A:
8	7	6	5
1	2	3	4

B:
4	1	2	3
5	8	7	6

C:
1	7	2	4
8	6	3	5
*/
int dp[3][8] = {{8, 7, 6, 5, 4, 3, 2, 1},
                {4, 1, 2, 3, 6, 7, 8, 5},
                {1, 7, 2, 4, 5, 3, 6, 8}};
/*
1	2	3	4
8	7	6	5
*/
int base[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int baseIndex[8];  // 记录每个值对应的位置
void Init() {
  for (int i = 0; i < 8; i++) {
    base[i]--;
    baseIndex[base[i]] = i;
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      dp[i][j]--;
    }
  }
}
int Trans(const int type, const int u) {
  const int* p = dp[type];
  int ans = 0;
  //   printf("u=%o\n", u);
  for (int i = 0; i < 8; i++) {
    const int val = p[i];
    int j = baseIndex[val];
    // j -> i
    // printf("j=%d[%d] -> i=%d\n", j, ((u >> (j * 3)) & 7) , i);
    ans |= ((u >> (j * 3)) & 7) << (i * 3);
  }
  //   printf("ans=%o\n", ans);
  return ans;
}

unordered_map<int, pair<int, int>> pre;  // u -> {pre, type}

void Bfs(const int s) {
  queue<int> que;
  //   assert(s < N * N);
  pre[s] = {0, 0};
  que.push(s);
  //   printf("s=%o\n", s);

  while (!que.empty()) {
    const int u = que.front();
    que.pop();

    for (int i = 0; i < 3; i++) {
      const int v = Trans(i, u);
      //   assert(v < N * N);
      if (pre.count(v) == 0) {
        // printf("%o -> %o i=%d\n", u, v, i);
        pre[v] = {u, i};
        que.push(v);
        if (v == t) {
          return;
        }
      }
    }
  }
}

// void Test(const int s, const string& buf) {
//   int u = s;
//   for (auto c : buf) {
//     int type = c - 'A';
//     const int v = Trans(type, u);
//     printf("%o -> %o i=%d %c\n", u, v, type, c);
//     u = v;
//   }
// }

void Solver() {
  Init();

  int s = 0;
  for (int i = 0; i < 8; i++) {
    s |= base[i] << (i * 3);
  }

  //   Test(s, "BCABCCB");

  for (int i = 0; i < 8; i++) {
    int v;
    scanf("%d", &v);
    t |= (v - 1) << (i * 3);
  }

  Bfs(s);

  int tCost = 0;
  string ans;
  int u = t;
  //   printf("s=%o\n", s);
  while (u != s) {
    const auto [uPre, uType] = pre[u];
    ans.push_back('A' + uType);
    // printf("%o -> %o\n", uPre, u);
    u = uPre;
    tCost++;
  }
  //   printf("t=%o\n", t);
  std::reverse(ans.begin(), ans.end());
  printf("%d\n%s\n", tCost, ans.data());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/