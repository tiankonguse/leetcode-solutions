/*
ID: tiankonguse
TASK: C. z 函数的字符串
LANG: C++
MAC EOF: ctrl+D
link: https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/problem/C
PATH: ITMO 学院：试点课程 » Z 函数 » 步骤2 » 实践
submission: https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/submission/297304623
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

int t;
void InitIO() {  //
  scanf("%d", &t);
}

int Z[55];
char str[55];
int NoExist() {
  str[0] = '!';
  str[1] = '\0';
  return 0;
}

bool TryFill1(const int i, const int n) {
  const int v = Z[i];
  if (v == 0) {
    return str[i] != str[0];
  }
  const int l = i, r = i + v - 1;  // [l, r]
  if (r >= n) return false;

  for (int j = 0; l + j <= r; j++) {
    if (str[l + j] != '\0') {
      if (str[l + j] != str[j]) {
        return false;
      }
    } else {
      str[l + j] = str[j];
    }
  }
  return true;
}

int next_char_index = 0;
char getNext() {
  next_char_index++;
  if (next_char_index >= 26) {
    return 'A' + (next_char_index - 26);
  } else {
    return 'a' + next_char_index;
  }
}

bool TryFill2(const int i, const int n) {  //
  const int v = Z[i];
  if (v == 0) {
    str[i] = getNext();
    return true;
  }
  const int l = i, r = i + v - 1;  // [l, r]
  if (r >= n) return false;
  for (int j = 0; l + j <= r; j++) {
    str[l + j] = str[j];
  }
  return true;
}

int ZZ[55];
void z_function(char* s, const int n, int* z) {  //
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

bool CheckAns(int n) {
  for (int i = 0; i < n; i++) {
    if (Z[i] == ZZ[i]) continue;
    return false;
  }
  return true;
}

int Solver(int n) {  //
  next_char_index = 0;
  if (Z[0] != 0) {
    return NoExist();
  }

  memset(str, '\0', sizeof(str));
  str[0] = 'a';
  for (int i = 1; i < n; i++) {
    if (str[i] != '\0') {  // 已经有值了，检查是否合法
      if (!TryFill1(i, n)) {
        return NoExist();
      }
    } else {
      if (!TryFill2(i, n)) {
        return NoExist();
      }
    }
  }

  z_function(str, n, ZZ);
  if (!CheckAns(n)) {
    // printf("-----------ANS ERROR\n");
    return NoExist();
  }

  return 0;
}

void Solver() {  //
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &Z[i]);
    }
    Solver(n);
    printf("%s\n", str);
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
  // printf("50\n");
  // for (int i = 0; i < 50; i++) {
  //   printf("0 ");
  // }
  // printf("\n");
  InitIO();
  ExSolver();
  return 0;
}

/*

*/