/*
ID: tiankonguse
TASK: lgame
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "lgame"
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
void ReInitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  freopen("lgame.dict", "r", stdin);
  // #endif
}

vector<int> scores;
vector<int> strStat;
vector<int> dictStat;
vector<vector<string>> h;
const int maxScore = 50;

void Add(const int v, string s) {
  for (auto c : s) {
    scores[c - 'a'] = v;
  }
}
void Init() {
  scores.resize(26, 0);
  Add(1, "eis");
  Add(2, "rtan");
  Add(3, "ol");
  Add(4, "udc");
  Add(5, "ypghbm");
  Add(6, "wfkv");
  Add(7, "qjzx");
  for (auto v : scores) {
    assert(v != 0);
  }
  h.resize(maxScore);
}

int maxOneScore = 0;

void AddDict(const string& s) {
  int score = 0;
  dictStat.clear();
  dictStat.resize(26, 0);
  for (auto c : s) {
    const int v = c - 'a';
    dictStat[v]++;
    if (dictStat[v] > strStat[v]) return;  // 非法 dict
    score += scores[v];
  }
  maxOneScore = max(maxOneScore, score);
  h[score].push_back(s);
}

void InitStr(const string& str) {
  strStat.resize(26, 0);
  for (const char c : str) {
    strStat[c - 'a']++;
  }
}

bool Check(const string& a, const string& b) {
  dictStat.clear();
  dictStat.resize(26, 0);
  for (char c : a) {
    dictStat[c - 'a']++;
  }
  for (auto c : b) {
    const int v = c - 'a';
    dictStat[v]++;
    if (dictStat[v] > strStat[v]) return false;  // 非法 dict
  }
  return true;
}

bool Check(const int a, const int b) {
  if (h[a].empty() || h[b].empty()) return false;

  for (const string& as : h[a]) {
    for (const string& bs : h[b]) {
      if (Check(as, bs)) return true;
    }
  }

  return false;
}

bool Check(const int sum) {
  if (sum <= maxOneScore) {
    return true;
  }
  for (int i = 1; i <= sum - i; i++) {
    if (Check(i, sum - i)) {
      return true;
    }
  }
  return false;
}

string Merge(const string& as, const string& bs) {
  if (as < bs) {
    return as + " " + bs;
  } else {
    return bs + " " + as;
  }
}

void Solver() {  //
  char tmp[8];
  Init();
  scanf("%s", tmp);
  InitStr(tmp);
  ReInitIO();
  while (true) {
    scanf("%s", tmp);
    if (tmp[0] == '.') break;
    AddDict(tmp);
  }

//   printf("maxOneScore=%d maxScore=%d\n", maxOneScore, maxScore);
  int l = maxOneScore, r = maxScore;
  while (r > l) {
    if (Check(r)) {
      break;
    }
    r--;
  }
  printf("%d\n", r);

  auto& ans = h[r];
  for (int i = 1; i <= r - i; i++) {
    const int a = i, b = r - i;
    if (h[a].empty() || h[b].empty()) continue;
    for (const string& as : h[a]) {
      for (const string& bs : h[b]) {
        if (Check(as, bs)) {
          ans.push_back(Merge(as, bs));
        }
      }
    }
  }

  sort(ans.begin(), ans.end());
  for (auto& s : ans) {
    printf("%s\n", s.data());
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