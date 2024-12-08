/*
ID: tiankonguse
TASK: calfflac
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "calfflac"
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

// https://oi-wiki.org/string/manacher/
// s 原始字符串; ss 预处理后的字符串;  p 各中心的半径
void Manacher(const string& s, string& ss, vector<int>& p) {
  int n = s.size();
  int nn = n * 2 + 2;
  ss.resize(nn);
  p.resize(nn);

  ss[0] = '$';
  ss[nn - 1] = '#';
  for (int i = 0; i < n; i++) {
    ss[i * 2 + 1] = '#';
    ss[i * 2 + 2] = s[i];
  }
  int r = 0, id = 0;  // 到达最远 r 时，中心为 id, (id-r, id+r)
  for (int i = 1; i < nn; i++) {
    p[i] = 1;
    if (r > i) {
      p[i] = min(p[2 * id - i], r - i);
    }
    while (i + p[i] < nn && i - p[i] > 0 && ss[i + p[i]] == ss[i - p[i]]) {
      p[i]++;
    }
    if (i + p[i] > r) {
      r = i + p[i];
      id = i;
    }
  }
}

char str[100];
string baseStr;
string s;
vector<int> indexPos;

void Solver() {  //
  while (fgets(str, sizeof(str), stdin)) {
    baseStr.append(str);
  }

  s.reserve(baseStr.size());
  indexPos.reserve(baseStr.size() * 2 + 2);
  indexPos.push_back(0);
  for (size_t i = 0; i < baseStr.size(); i++) {
    char c = baseStr[i];
    if (!isalpha(c)) continue;
    c = tolower(c);
    s.push_back(c);
    indexPos.push_back(i);
    indexPos.push_back(i);
  }
  indexPos.push_back(baseStr.size() - 1);

  string ss;
  vector<int> p;
  Manacher(s, ss, p);
  int maxAns = 0;
  int ansL, ansR;
  int nn = ss.size();
  for (int i = 1; i < nn; i++) {
    int r = p[i];  // 半径
    if (r == 1) continue;
    int L = i - r + 1;
    int R = i + r - 1;
    L++, R--;
    int tmpLen = (R - L + 2) / 2;
    if (tmpLen > maxAns) {
      maxAns = tmpLen;
      ansL = indexPos[L];
      ansR = indexPos[R];
    }
  }
  printf("%d\n", maxAns);
  printf("%s\n", baseStr.substr(ansL, ansR - ansL + 1).data());
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/