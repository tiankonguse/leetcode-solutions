/*
ID: tiankonguse
TASK: checker
LANG: C++
MAC EOF: ctrl+D
HINT: Checker problem: Hint 4
DESC: SYMMETRY. Can you eliminate half or 3/4 of the cases you test by studying
rotations, reflections, or something like that? [hint: yes]
*/
#define TASK "checker"
#define TASKEX "-dance-link"

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

int N;
enum { UU = 0, UR = 1, RR = 2, RD = 3, DD = 4, DL = 5, LL = 6, LU = 7 };
int dir8[8][2] = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                  {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
int NN;
struct DanceLink {
  int flag;    // 桩
  int dir[8];  // 8 个方向的 id
};
DanceLink danceLinks[400];

vector<int> buf;
int& Next(int id, int d) { return danceLinks[id].dir[d]; }
int End(int id) { return danceLinks[id].flag; }

vector<int> dirs = {DL, DD, RD};
void Remove(const int id) {
  for (const int d : dirs) {
    const int dd = (d + 4) % 8;
    for (int ID = Next(id, d); !End(ID); ID = Next(ID, d)) {  //
      for (int i = 0; i < 8; i++) {
        if (i == d || i == dd) continue;
        const int ii = (i + 4) % 8;
        Next(Next(ID, i), ii) = Next(ID, ii);
      }
    }
  }
}
vector<int> rdirs = {RD, DD, DL};
void Recover(const int id) {
  for (const int d : rdirs) {
    const int dd = (d + 4) % 8;
    for (int ID = Next(id, d); !End(ID); ID = Next(ID, d)) {  //
      for (int i = 0; i < 8; i++) {
        if (i == d || i == dd) continue;
        const int ii = (i + 4) % 8;
        Next(Next(ID, i), ii) = ID;
      }
    }
  }
}

int ans = 0;
vector<vector<int>> top3;
void Dfs(const int p) {  // 枚举第 p 行
  if (p == N + 1) {
    if (ans < 3) {
      top3.push_back(buf);
    }
    ans++;
    return;
  }
  const int S = p * NN;
  for (int id = Next(S, RR); !End(id); id = Next(id, RR)) {
    buf.push_back(id % NN);
    Remove(id);
    Dfs(p + 1);
    Recover(id);
    buf.pop_back();
  }
}

void Init(const int x, const int y, const int id) {
  memset(danceLinks[id].dir, -1, sizeof(danceLinks[id].dir));
  for (int i = 0; i < 8; i++) {
    const int X = x + dir8[i][0];
    const int Y = y + dir8[i][1];
    if (X < 0 || X >= NN || Y < 0 || Y >= NN) continue;
    const int ID = X * NN + Y;
    danceLinks[id].dir[i] = ID;
  }
  if (x == 0 || x + 1 == NN || y == 0 || y + 1 == NN) {
    danceLinks[id].flag = 1;
  } else {
    danceLinks[id].flag = 0;
  }
}

void Init() {  //
  int id = 0;
  for (int i = 0; i < NN; i++) {
    for (int j = 0; j < NN; j++) {
      Init(i, j, id);
      // for (int k = 0; k < 8; k++) {
      //   printf("(%d, %d) id=%d dir[%d] -> id[%d]\n", i, j, id, k,
      //          danceLinks[id].dir[k]);
      // }
      ++id;
    }
  }

  // connect row
}
void SolverInput() {  //
  scanf("%d", &N);
  NN = N + 2;
}

void Solver() {  //
  Init();
  // 由于对称性，第一行只需要枚举一半
  Dfs(1);
  for (auto& vs : top3) {
    for (int i = 0; i < N; i++) {
      printf("%d%c", vs[i], i + 1 == N ? '\n' : ' ');
    }
  }
  printf("%d\n", ans);
}

void ExSolver() {
  SolverInput();
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
   Test 1: TEST OK [0.007 secs limit:1s, 1812 KB]
   Test 2: TEST OK [0.004 secs limit:1s, 1696 KB]
   Test 3: TEST OK [0.004 secs limit:1s, 1744 KB]
   Test 4: TEST OK [0.007 secs limit:1s, 1708 KB]
   Test 5: TEST OK [0.025 secs limit:1s, 1696 KB]
   Test 6: TEST OK [0.081 secs limit:1s, 1636 KB]
   Test 7: TEST OK [0.354 secs limit:1s, 1748 KB]
  > Run 8: Execution error: Your program (`checker') used more than
        the allotted runtime of 1 seconds (it ended or was stopped at
        1.855 seconds) when presented with test case 8. It used 1732 KB of
        memory. 

        ------ Data for Run 8 [length=3 bytes] ------
        13 
        ----------------------------
    Test 8: RUNTIME 1.855>1 (1732 KB)

13
1 3 5 2 9 12 10 13 4 6 8 11 7
1 3 5 7 9 11 13 2 4 6 8 10 12
1 3 5 7 12 10 13 6 4 2 8 11 9
73712
my 用时: 2541ms
*/