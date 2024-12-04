/*
ID: tiankonguse
TASK: twofive
LANG: C++
MAC EOF: ctrl+D
DESC: 把它的25个字母排成一个5*5的矩阵，它的每一行和每一列都必须是递增的
ERROR: 理解为必须从左到右、从上到下读取
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

vector<string> allAns;
string buf;

/*
  1 2 3 4 5
5
4
3
2
1
*/
int GetPos(int i, int j) {  // 下标从 0 开始
  i = 5 - i;
  j = j - 1;
  return i * 5 + j;
}
ll dp[6][6][6][6][6];
ll Dfs(string& s, const char c, const string& ans, const vector<int>& use) {
  if (c == 'Z') return 1;
  const int ansNum = ans.size();
  auto& ret = dp[s[1] - '0'][s[2] - '0'][s[3] - '0'][s[4] - '0'][s[5] - '0'];
  if (ret != -1) return ret;
  ret = 0;
  for (int i = 5; i > 0; i--) {
    if (s[i] > s[i - 1]) {  // 可以选择
      const int p = GetPos(s[i] - '0', i);
      // printf("s[%s] i=%d p=%d ansNum=%d c=%c \n", s.data(), i, p, ansNum, c);
      if (use[c - 'A' + 1] && p >= ansNum) continue;  // 已使用，必须满足下标
      if (p < ansNum && ans[p] != c) continue;

      s[i]--;
      ret += Dfs(s, c + 1, ans, use);
      s[i]++;
    }
  }
  return ret;
}

char op[10];
void Solver() {  //
  // 701149020

  scanf("%s", op);
  if (op[0] == 'N') {
    int m;
    scanf("%d", &m);
    string ans;
    vector<int> use(26, 0);
    string pre;
    for (int i = 0; i < 25; i++) {
      pre.push_back('A' + i);
    }
    for (int i = 0; i < 5; i++) {
      string buf;
      for (int j = 0; j < 5; j++) {
        while (!pre.empty()) {
          const char c = pre.front();
          pre.erase(pre.begin());

          use[c - 'A' + 1] = 1;
          ans.push_back(c);

          memset(dp, -1, sizeof(dp));
          string states = "055555";
          ll num = Dfs(states, 'A', ans, use);
          // printf("i=%d j=%d c=%c ans[%s] pre[%s] buf[%s] num=%lld\n", i, j,
          // c,
          //        ans.data(), pre.data(), buf.data(), num);
          if (num >= m) {  // 选择 c
            break;
          } else {
            ans.pop_back();
            use[c - 'A' + 1] = 0;
            buf.push_back(c);
            m -= num;
          }
        }
      }
      buf.append(pre);
      pre = buf;
    }

    printf("%s\n", ans.data());
  } else {
    char str[40];
    scanf("%s", str);
    ll ans = 1;

    vector<int> use(26, 0);
    string buf;
    for (int i = 0; i < 25; i++) {
      for (int c = 1; c < str[i] - 'A' + 1; c++) {
        if (use[c]) continue;
        buf.push_back(c + 'A' - 1);
        use[c] = 1;
        memset(dp, -1, sizeof(dp));
        string states = "055555";
        ans += Dfs(states, 'A', buf, use);
        buf.pop_back();
        use[c] = 0;
      }
      buf.push_back(str[i]);
      use[str[i] - 'A' + 1] = 1;
    }

    printf("%lld\n", ans);
  }
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

------- test 1 [length 4 bytes] ----
N
1
------- test 2 [length 28 bytes] ----
W
ABCDEFGHIJKLMNOPQRSTUVWXY
------- test 3 [length 6 bytes] ----
N
100
------- test 4 [length 28 bytes] ----
W
ABCDEFGHIJKLMNQOPSTVRUWXY
------- test 5 [length 8 bytes] ----
N
10000
------- test 6 [length 28 bytes] ----
W
ABCDEFGHIKJMNQRLOTVXPSUWY
------- test 7 [length 12 bytes] ----
N
701149020
------- test 8 [length 28 bytes] ----
W
AFKPUBGLQVCHMRWDINSXEJOTY
------- test 9 [length 12 bytes] ----
N
152798377
------- test 10 [length 28 bytes] ----
W
ABDILCEMPSFGNTVHKOUXJQRWY
------- test 11 [length 12 bytes] ----
N
192837465
------- test 12 [length 28 bytes] ----
W
ABCJQDFIMREGKPSHLTUWNOVXY

*/