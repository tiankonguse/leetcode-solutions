/*
ID: tiankonguse
TASK: expr
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7073
PATH:  P7073 [CSP-J2020] 表达式
submission:
*/
#define TASK "expr"
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

#ifdef USACO_LOCAL_JUDGE
int debug_log = 0;
int debug_assert = 1;
#define MyPrintf(...)                   \
  do {                                  \
    if (debug_log) printf(__VA_ARGS__); \
  } while (0)

#define MyAssert(...)                      \
  do {                                     \
    if (debug_assert) assert(__VA_ARGS__); \
  } while (0)
#else
#define MyPrintf(...)
#define MyAssert(...)
#endif

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

void InitIO() {  //
#ifdef USACO_LOCAL_JUDGE
// #define TASKNO "4"
//   freopen(TASK TASKNO ".in", "r", stdin);
//   freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

enum { E_VAL = 0, E_AND, E_OR, E_NOT };
struct Node {
  int type;  //
  // int idx;
  int val;
  int left, right;
};

Node nodes[max6];
int nodeIdx = 0;

char buf[10];
stack<int> sta;
unordered_map<int, int> nameToIdx;
unordered_map<int, int> idxToName;
vector<int> names;
int NewNode(int type, int val = 0, int left = 0, int right = 0) {
  int idx = ++nodeIdx;
  nodes[idx].type = type;
  // nodes[idx].idx = idx;
  nodes[idx].val = val;
  nodes[idx].left = left;
  nodes[idx].right = right;
  return idx;
}

int ToInt(const char* s) {
  int i = 0;
  while (*s) {
    i = i * 10 + *s - '0';
    s++;
  }
  return i;
}
bool AddNode() {
  scanf("%s", buf);
  const char c = buf[0];
  if (c == 'x') {
    int idx = NewNode(E_VAL, 0);
    int name = ToInt(buf + 1);
    nameToIdx[name] = idx;
    idxToName[idx] = name;
    sta.push(idx);
  } else if (c == '|') {
    int rightIdx = sta.top();
    sta.pop();
    int leftIdx = sta.top();
    sta.pop();
    int idx = NewNode(E_OR, 0, leftIdx, rightIdx);
    sta.push(idx);
  } else if (c == '&') {
    int rightIdx = sta.top();
    sta.pop();
    int leftIdx = sta.top();
    sta.pop();
    int idx = NewNode(E_AND, 0, leftIdx, rightIdx);
    sta.push(idx);
  } else if (c == '!') {
    int leftIdx = sta.top();
    sta.pop();
    int idx = NewNode(E_NOT, 0, leftIdx, 0);
    sta.push(idx);
  } else {
    return false;
  }
  return true;
}

int root;

int DfsInit(int pre) {
  if (nodes[pre].type == E_AND) {
    int left = DfsInit(nodes[pre].left);
    int right = DfsInit(nodes[pre].right);
    return nodes[pre].val = left && right;
  } else if (nodes[pre].type == E_OR) {
    int left = DfsInit(nodes[pre].left);
    int right = DfsInit(nodes[pre].right);
    return nodes[pre].val = left || right;
  } else if (nodes[pre].type == E_NOT) {
    int left = DfsInit(nodes[pre].left);
    return nodes[pre].val = 1 - left;
  } else {
    return nodes[pre].val;
  }
}

vector<int> ignoreIdxs;
int LeftVal(int pre) { return nodes[nodes[pre].left].val; }
int RightVal(int pre) { return nodes[nodes[pre].right].val; }

void DfsFlag(int pre, bool flag) {
  if (pre == 0) return;
  MyPrintf("pre=%d, flag=%d, type=%d val=%d, left=%d, right=%d\n", pre, flag, nodes[pre].type, nodes[pre].val,
           nodes[pre].left, nodes[pre].right);
  if (flag) {
    if (nodes[pre].type == E_VAL) {
      int name = idxToName[pre];
      MyPrintf("ignore name=%d\n", name);
      ignoreIdxs[pre] = 1;
    }
    DfsFlag(nodes[pre].left, flag);
    DfsFlag(nodes[pre].right, flag);
    return;
  }

  if (nodes[pre].type == E_AND) {
    DfsFlag(nodes[pre].left, !RightVal(pre));
    DfsFlag(nodes[pre].right, !LeftVal(pre));
  } else if (nodes[pre].type == E_OR) {
    DfsFlag(nodes[pre].left, RightVal(pre));
    DfsFlag(nodes[pre].right, LeftVal(pre));
  } else if (nodes[pre].type == E_NOT) {
    DfsFlag(nodes[pre].left, false);
  } else {
    // do nothing
  }
}

void Solver() {  //
  while (AddNode()) {
    continue;
  }
  root = sta.top();
  MyPrintf("root=%d\n", root);
  int n = ToInt(buf);
  names.resize(n + 1);
  for (int name = 1; name <= n; name++) {
    scanf("%d", &names[name]);
    int idx = nameToIdx[name];
    nodes[idx].val = names[name];
  }
  DfsInit(root);
  ignoreIdxs.resize(nodeIdx + 1, 0);
  DfsFlag(root, false);
  int q;
  scanf("%d", &q);
  while (q--) {
    int name;
    scanf("%d", &name);
    int idx = nameToIdx[name];
    if (ignoreIdxs[idx]) {
      printf("%d\n", nodes[root].val);  // 这个位置变化不影响答案
    } else {
      printf("%d\n", 1 - nodes[root].val);  // 这个位置影响答案，即翻转
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
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
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