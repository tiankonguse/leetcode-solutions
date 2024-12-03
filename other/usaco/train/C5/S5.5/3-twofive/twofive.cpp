/*
ID: tiankonguse
TASK: twofive
LANG: C++
MAC EOF: ctrl+D
DESC: 把它的25个字母排成一个5*5的矩阵，它的每一行和每一列都必须是递增的
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

ll dp[6][6][6][6][6];

ll Dfs(string& s) {
  auto& ret = dp[s[1] - '0'][s[2] - '0'][s[3] - '0'][s[4] - '0'][s[5] - '0'];
  if (ret != -1) return ret;
  ret = 0;
  for (int i = 5; i > 0; i--) { // 枚举最小值可以选择的位置
    if (s[i] > s[i - 1]) {  // 可以选择
      s[i]--;
      ret += Dfs(s);
      s[i]++;
    }
  }
  if (ret == 0) {
    ret = 1;
  }
  return ret;
}

vector<string> dicts = {"",       //
                        "UPKFA",  //
                        "VQLGB",  //
                        "WRMHC",  //
                        "XSNID",  //
                        "YTOJE"};

char op[10];
void Solver() {  //
  string states = "055555";
  memset(dp, -1, sizeof(dp));
  Dfs(states);

  scanf("%s", op);
  if (op[0] == 'N') {
    int m;
    scanf("%d", &m);

    string ans;
    set<char> S;
    for (int i = 0; i < 25; i++) {
      S.insert('A' + i);
    }
    for (int i = 1; i <=5 ; i++) {
      for (int j = 1; j <= 5; j++) {
        states[j]--;
        ll num = Dfs(states);  // [1, num]
        printf("i=%d j=%d num=%lld m=%d\n", i, j, num, m);
        int index = 0;
        for (const char c : S) {
          index++;
          if (num >= m) {  // 选择 c
            ans.push_back(c);
            S.erase(c);
            break;
          } else {
            m -= num;
          }
        }
        printf("index=%d c=%c m=%d\n", index, ans.back(), m);
      }
    }
    printf("%s\n", ans.data());
  } else {
    char str[40];
    scanf("%s", str);
    string s = str;
    ll ans = 1;
    for (const char c : s) {
      for (int i = 5; i > 0; i--) {
        if (states[i] > states[i - 1]) {  // 可以选择 states[i]
          states[i]--;                    // 选择
          ll num = Dfs(states);           // [1, num]
          if (c == dicts[i][states[i] - '0']) {
            break;
          } else {
            states[i]++;  // 选择
            ans += num;
          }
        }
      }
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
ABCDE
FGHIJ
KLMNQ
OPSTV
RUWXY

K = 25 - (i*5 + j);
lineLeft = 5-j;
num = C(K, lineLeft) * f(i+1, 1);
*/