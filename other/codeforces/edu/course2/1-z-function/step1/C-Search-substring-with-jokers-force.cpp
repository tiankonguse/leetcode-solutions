/*
ID: tiankonguse
TASK: C. 在模式中查找带有通配符的字符串中的子字符串
LANG: C++
MAC EOF: ctrl+D
link:  https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/C
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤1 » 实践
submission: https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/submission/297184523
*/
#define TASK "demo"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

int q;
void InitIO() {  //
  scanf("%d", &q);
}

const int N = 50010;
char str[N];
char pat[111];

vector<int> ans;
bool Check(int n, int m, int l) {
  if (l + m > n) return false;  // 剪枝
  for (int i = 0; i < m; i++, l++) {
    if (pat[i] != '?' && str[l] != pat[i]) return false;
  }
  return true;
}
void Solver(int n, int m) {
  if (m > n) return;  // 剪枝
  for (int i = 0; i < n; i++) {
    if (Check(n, m, i)) {
      ans.push_back(i);
    }
  }
}

void Solver() {  //
  while (q--) {
    scanf("%s%s", str, pat);
    ans.clear();
    Solver(strlen(str), strlen(pat));

    int num = ans.size();
    printf("%d\n", num);
    if (num == 0) printf("\n");
    for (int i = 0; i < num; i++) {
      printf("%d%c", ans[i], i + 1 == num ? '\n' : ' ');
    }
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
  InitIO();
  ExSolver();
  return 0;
}

/*

*/