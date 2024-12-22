/*
ID: tiankonguse
TASK: I. Inaccurate Search  I、搜索不准确
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/I?locale=en
PATH: ITMO 学院：试点课程 » Z-функция » 步骤4 » 实践
submission:
*/
#define TASK "I-inaccurate-search"
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

void z_function(char* s, int n, int* z) {  //
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < n; i++) {
    z[i] = 0;
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
}

const int N = 2e6 + 10;
char S[N];
char T[N];
int Z_TS[N];
int Z_RTS[N];
int k;
void InitIO() {  //
  scanf("%s%s%d", S, T, &k);
}

void Solver() {  //
  const int sn = strlen(S);
  const int tn = strlen(T);

  int tsn = tn;
  T[tsn++] = '$';
  for (int i = 0; i < sn; i++) {
    T[tsn++] = S[i];
  }
  T[tsn] = '\0';
  z_function(T, tsn, Z_TS);

  for (int l = 0, r = tn - 1; l < r; l++, r--) {
    swap(T[l], T[r]);
  }
  for (int l = tn + 1, r = tsn - 1; l < r; l++, r--) {
    swap(T[l], T[r]);
  }
  z_function(T, tsn, Z_RTS);

  vector<int> ans;
  for (int i = 0; i + tn <= sn; i++) {  //
    int l = tn + 1 + i;
    int lc = Z_TS[l];

    int r = tn + 1 + (sn - (i + tn));
    int rc = Z_RTS[r];
    if (lc + rc + k >= tn) {
      ans.push_back(i + 1);
    }
  }
  int ansNum = ans.size();
  printf("%d\n", ansNum);
  for (int i = 0; i < ansNum; i++) {
    printf("%d%c", ans[i], i + 1 == ansNum ? '\n' : ' ');
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

*/