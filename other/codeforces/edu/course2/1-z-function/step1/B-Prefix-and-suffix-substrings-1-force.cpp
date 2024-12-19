/*
ID: tiankonguse
TASK: B. 前缀和后缀子串 - 1
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/B
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤1 » 实践
submission:
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

const int N = 550;
char str[N];

int prefix[555][555];
int suffix[555][555];

int Solver(const int n) {
  memset(prefix, 0, sizeof(prefix));
  memset(suffix, 0, sizeof(suffix));

  for (int i = 0; i < n; i++) {                // 枚举起始位置
    for (int j = i, d = 0; j < n; j++, d++) {  // 枚举结束位置
      if (str[d] == str[j]) {
        prefix[i][j] = 1;  // [i,j] = [0, j-i+1]
      } else {
        break;
      }
    }
  }

  for (int j = n - 1; j >= 0; j--) {  // 枚举结束位置
    for (int i = j, d = n - 1; i >= 0; i--, d--) {
      if (str[d] == str[i]) {
        suffix[i][j] = 1;
      } else {
        break;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {    // 枚举起始位置
    for (int j = i; j < n; j++) {  // 枚举结束位置
      ans += prefix[i][j] ^ suffix[i][j];
    }
  }

  return ans;
}

void Solver() {  //
  getchar();     // skip \n
  while (q--) {
    fgets(str, N, stdin);
    int n = strlen(str);  // skip \n
    str[--n] = '\0';
    printf("%d\n", Solver(n));
  }
}
// str[barbarmiakirkudu] n[16]

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