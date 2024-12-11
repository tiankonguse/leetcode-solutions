/*
ID: tiankonguse
TASK: clocks
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "clocks"
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

int g[10];

vector<pair<int, int>> H;
vector<string> moves = {"ABDE", "ABC",  "BCEF", "ADG", "BDEFH",
                        "CFI",  "DEGH", "GHI",  "EFHI"};
int Trans(int h, int i) {
  const string& s = moves[i];
  for (auto C : s) {
    int c = C - 'A';
    int v = (h >> (c * 2)) & 3;
    h ^= v << (c * 2);  // set 0
    v = (v + 1) & 3;    // +1
    h ^= v << (c * 2);  // set next val
  }
  return h;
}
// pair<int, int> Dfs(const int h) {
//   auto& [ret, moveIndex] = H[h];
//   if (ret != -1) return H[h];
//   if (h == 0) return H[h] = {0, -1};
//   ret = INT_MAX;
//   moveIndex = -1;
//   for (int i = 0; i < 9; i++) {
//     auto [childRet, childMove] = Dfs(Trans(h, i));
//     if (childRet + 1 < ret) {
//       ret = childRet + 1;
//       moveIndex = i;
//     }
//   }
//   return H[h];
// }

void Bfs(const int S, const int T) {
  queue<int> que;  // {h}
  que.push(S);
  H[S] = {0, -1};

  while (!que.empty()) {
    const int U = que.front();
    que.pop();

    for (int i = 0; i < 9; i++) {
      const int V = Trans(U, i);
      if (H[V].first != -1) continue;
      H[V] = {U, i};
      if (V == T) return;
      que.push(V);
    }
  }
}

void Solver() {  //
  int h = 0;
  for (int i = 0; i < 9; i++) {
    scanf("%d", &g[i]);
    g[i] = g[i] / 3 % 4;
    h |= g[i] << (i * 2);
  }
  H.resize(1 << 20, {-1, -1});
  Bfs(h, 0);

  vector<int> ans;

  int S = 0;
  while (S != h) {
    ans.push_back(H[S].second + 1);
    S = H[S].first;
  }
  int n = ans.size();
  //   printf("%d\n", n);
  std::reverse(ans.begin(), ans.end());
  for (int i = 0; i < n; i++) {
    printf("%d%c", ans[i], i + 1 == n ? '\n' : ' ');
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
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.018 secs limit:1s, 3252 KB]
   Test 2: TEST OK [0.018 secs limit:1s, 3340 KB]
   Test 3: TEST OK [0.025 secs limit:1s, 3260 KB]
   Test 4: TEST OK [0.035 secs limit:1s, 3356 KB]
   Test 5: TEST OK [0.060 secs limit:1s, 3400 KB]
   Test 6: TEST OK [0.130 secs limit:1s, 3384 KB]
   Test 7: TEST OK [0.168 secs limit:1s, 3408 KB]
   Test 8: TEST OK [0.126 secs limit:1s, 3408 KB]
   Test 9: TEST OK [0.123 secs limit:1s, 3380 KB]

All tests OK.
*/