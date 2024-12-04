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
int GetPos(int i, int j) {
  i = 5 - i;
  j = j - 1;
  return i * 5 + j;
}
int allNum = 0;
void Dfs(string& s, char c) {
  if (s[5] == '0') {
    allNum++;
    // allAns.push_back(buf);
    if (allNum % 10000 == 0) {
      printf("allNum=%d\n", allNum);
    }
    return;
  }
  for (int i = 5; i > 0; i--) {
    if (s[i] > s[i - 1]) {  // 可以选择
      int p = GetPos(s[i], i);
      buf[p] = c;
      s[i]--;
      Dfs(s, c + 1);
      s[i]++;
    }
  }
}

ll dp[6][6][6][6][6];
string ans;
int use[30];
ll Dfs1(string& s) {
  auto& ret = dp[s[1] - '0'][s[2] - '0'][s[3] - '0'][s[4] - '0'][s[5] - '0'];
  if (ret != -1) return ret;
  ret = 0;
  for (int i = 5; i > 0; i--) {
    if (s[i] > s[i - 1]) {  // 可以选择
      s[i]--;
      ret += Dfs1(s);
      s[i]++;
    }
  }
  if (ret == 0) {
    ret = 1;
  }
  return ret;
}


char op[10];
void Solver() {  //
  string states = "055555";
  memset(dp, -1, sizeof(dp));
  // 701149020
 printf("%lld\n",  Dfs1(states));

  scanf("%s", op);
  if (op[0] == 'N') {
    int m;
    scanf("%d", &m);
    string ans;
    memset(S, 0, sizeof(S));
    memset(use, 0, sizeof(use));
    for(int i=1;i<=25;i++){
      for(int c=1;c<=25;c++){
        if(use[c]) continue; // 枚举选择 c 是否是答案 
        use[c] = 1;


      }
    }
    printf("%s\n", ans.data());
  } else {
    char str[40];
    scanf("%s", str);
    string s = str;
    ll ans = 1;
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

*/