/*
ID: tiankonguse
TASK: twofive
LANG: C++
MAC EOF: ctrl+D
DESC: 把它的25个字母排成一个5*5的矩阵，每行必须有序，列不做要求
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

/*
A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
C(n,r)=C(n-1,r)+C(n-1,r-1)
*/

const int N = 26;
ll str[N][N];  //
ll C(int m, int n) {
  if (str[m][n] != -1) return str[m][n];
  if (m == n || n == 0) return str[m][n] = 1;
  if (m < n) return str[m][n] = 0;
  return str[m][n] = C(m - 1, n - 1) + C(m - 1, n);
}
ll dp[6][6][27];

// 从第i行第j列开始填充，第i行可以从 B 集合里选择的答案书
// C(B, 5-j) * Dfs(i+1, 0, 0, B - (5-j));
ll Dfs(int i, int j, int A, int B) {
  if (i == 5) return 1;  // 出口
  ll& ret = dp[i][j][B];
  if (ret != -1) return ret;
  return ret = C(B, 5 - j) * Dfs(i + 1, 0, 0, (A + B) - (5 - j));
}

char op[10];
void Solver() {  //
  memset(str, -1, sizeof(str));
  memset(dp, -1, sizeof(dp));

  scanf("%s", op);
  if (op[0] == 'N') {
    int m;
    scanf("%d", &m);

    string ans;
    string pre;
    for (int i = 0; i < 25; i++) {
      pre.push_back('A' + i);
    }
    // printf("[%d] %s\n", int(pre.size()), pre.data());
    for (int i = 0; i < 5; i++) {
      string buf;
      for (int j = 0; j < 5; j++) {
        // printf("i=%d j=%d buf=[%s] pre=[%s]\n", i, j, buf.data(), pre.data());
        while (!pre.empty()) {
          int A = buf.size();
          int B = pre.size();
          // printf("A=%d B=%d pos=%d\n", A, B, i * 5 + j);
          B--;
          const ll num = Dfs(i, j + 1, A, B);
          // printf(" i=%d j+1=%d B=%d C(%d, %d)=%lld num=%lld\n", i, j + 1, B, B,
          //        5 - (j + 1), C(B, 5 - (j + 1)), num);
          if (num >= m) {  // 选择 c
            // printf("select c=%c m=%d\n", pre.front(), m);
            ans.push_back(pre.front());
            pre.erase(pre.begin());
            // printf("ans=%s buf=%s pre=%s\n", ans.data(), buf.data(),
            //        pre.data());
            break;
          } else {
            // printf("skip c=%c m=%d\n", pre.front(), m);
            buf.push_back(pre.front());
            pre.erase(pre.begin());
            m -= num;
            // printf("ans=%s buf=%s pre=%s m=%d\n", ans.data(), buf.data(),
            //        pre.data(), m);
          }
        }
      }
      buf.append(pre);
      pre = buf;
    }
    // printf("pre=%s\n", pre.data());
    printf("%s\n", ans.data());
  } else {
    char str[40];
    scanf("%s", str);
    string s = str;
    ll ans = 1;

    printf("%lld\n", ans);
  }

  // printf("C(10,5)=%lld\n", C(10, 5));
  // printf("C(9,4)=%lld\n", C(9, 4));
  // printf("C(8,3)=%lld\n", C(8, 3));
  // printf("C(7,3)=%lld\n", C(7, 3));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*


ABCDE
FGHIJ
KLMNO
PQSRT
UVWY

K = 25 - (i*5 + j);
lineLeft = 5-j;
num = C(K, lineLeft) * f(i+1, 1);

C(10,5)=252
C(9,4)=126
C(8,3)=56
C(7,3)=35

ABCDE
FGHIJ
KLMNO
PQRST
UVWXY

N
2
-> ABCDEFGHIJKLMNOPQRSTUVWX

N
1
-> ABCDEFGHIJKLMNOPQRSTUVWXY

N
100 
-> ABCDEFGHIJKLMNQOPSTVRUWXY

ABCDE
FGHIJ
KLMNQ
OPSTV
RUWXY
*/