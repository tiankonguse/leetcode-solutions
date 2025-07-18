/*
ID: tiankonguse
TASK: fruit
LANG: C++
MAC EOF: ctrl+D
link:  https://www.luogu.com.cn/problem/P7912
PATH:  P7912 [CSP-J 2021] 小熊的果篮
submission:
*/
#define TASK "fruit"
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
int debug_assert = 0;
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

void InitIO(int fileIndex) {  //
#ifdef USACO_LOCAL_JUDGE
#define USACO_TASK_FILE 3
#define TASKNO 1
#ifndef USACO_TASK_FILE
  fileIndex = TASKNO;
#endif
  string fileInName = string(TASK) + to_string(fileIndex) + ".in";
  string fileOutName = string(TASK) + to_string(fileIndex) + ".out";
  freopen(fileInName.c_str(), "r", stdin);
  freopen(fileOutName.c_str(), "w", stdout);
#endif
}

const int N = 400010;

struct LinkList {
  int val = 0;
  int pre = 0;
  int next = 0;
} linkList[N];
int linkListIndex = 0;

void InitLinkList() { linkListIndex = 0; }
int NewLinkListNode(const int v) {
  const int cur = ++linkListIndex;
  linkList[cur].val = v;
  linkList[cur].next = cur;
  linkList[cur].pre = cur;
  return cur;
}
int MergeLinkListNode(const int firstHead, const int secondHead) {
  const int firstTail = linkList[firstHead].pre;
  const int secondTail = linkList[secondHead].pre;

  linkList[firstTail].next = secondHead;
  linkList[secondHead].pre = firstTail;
  linkList[secondTail].next = firstHead;
  linkList[firstHead].pre = secondTail;
  return firstHead;
}

int RemoveFirstLinkListNode(const int head) {
  if (linkList[head].next == head) {
    return 0;  // 只有一个，删除后是空
  }
  const int tail = linkList[head].pre;
  const int newHead = linkList[head].next;
  linkList[tail].next = newHead;
  linkList[newHead].pre = tail;
  return newHead;
}

vector<pair<int, int>> segs;
vector<pair<int, int>> segsTmp;

void DumpSeg(vector<pair<int, int>>& segs) {
  for (auto [color, head] : segs) {
    printf("color=%d: ", color);
    int cur = head;
    do {
      printf(" %d,", linkList[cur].val);
      cur = linkList[cur].next;
    } while (cur != head);
    printf("\n");
  }
}

void Solver() {  //
  InitLinkList();
  segs.clear();
  segsTmp.clear();

  int n;

  scanf("%d", &n);
  segs.reserve(n);
  segsTmp.reserve(n);
  auto add = [](vector<pair<int, int>>& segs, int color, int head) {
    if (head == 0) return;  // 空列表
    if (segs.empty() || segs.back().first != color) {
      segs.push_back({color, head});
    } else {
      segs.back().second = MergeLinkListNode(segs.back().second, head);
    }
  };

  for (int i = 1; i <= n; i++) {
    int color;
    scanf("%d", &color);
    add(segs, color, NewLinkListNode(i));
  }
//   DumpSeg(segs);
  while (!segs.empty()) {
    segsTmp.clear();
    bool firstVal = true;
    for (auto [color, head] : segs) {
      const int val = linkList[head].val;
      add(segsTmp, color, RemoveFirstLinkListNode(head));
      if (firstVal) {
        printf("%d", val);
        firstVal = false;
      } else {
        printf(" %d", val);
      }
    }
    printf("\n");
    swap(segs, segsTmp);
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t1 = std::chrono::steady_clock::now();
#endif
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
#ifdef USACO_TASK_FILE
  auto t2 = std::chrono::steady_clock::now();
  auto my = std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  int fileIndex = 1;
#ifdef USACO_TASK_FILE
  for (int i = 1; i <= USACO_TASK_FILE; i++) {
    fileIndex = i;
#endif
    InitIO(fileIndex);
    ExSolver();
#ifdef USACO_TASK_FILE
  }
#endif
  return 0;
}

/*

*/