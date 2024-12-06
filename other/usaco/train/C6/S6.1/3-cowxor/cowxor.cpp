/*
ID: tiankonguse
TASK: cowxor
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "cowxor"
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

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 1000010;
struct Node {
  int next[2];
};
Node nodes[max6];
const int BIT = 22;
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    memset(node.next, -1, sizeof(node.next));
  }

  int Add() {
    int ret = index;
    Clear(ret);
    index++;
    return ret;
  }

 public:
  /** Initialize your data structure here. */
  Trie() { Init(); }

  void Init() {
    index = 0;
    Add();
  }

  /** Inserts a word into the trie. */
  void Insert(int num, int pos) {
    int root = 0;
    for (int i = BIT; i >= 0; i--) {
      int v = (num >> i) & 1;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      root = nodes[root].next[v];
    }
    nodes[root].next[0] = pos;  // 保留最大的 pos
  }

  /** 返回区间内异或最大的值 */
  int Search(const int num, int root = 0, int index = BIT) {
    // 可以选择自己，所以肯定有答案
    while (index >= 0) {
      int v = (num >> index) & 1;
      int p1 = nodes[root].next[1 - v];
      if (p1 != -1) {
        root = p1;
        index--;
        continue;
      }

      int p0 = nodes[root].next[v];
      if (p0 != -1) {
        root = p0;
        index--;
        continue;
      }
      assert(0);
    }
    return nodes[root].next[0];
  }
};

Trie trie;
vector<int> preXOR;

int n, v;
void Solver() {  //
  scanf("%d", &n);
  preXOR.resize(n + 1, 0);

  trie.Init();
  trie.Insert(0, 0);

  int ans = 0, l = 1, r = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v);
    preXOR[i] = preXOR[i - 1] ^ v;
    int prePos = trie.Search(preXOR[i]);
    int xorVal = preXOR[i] ^ preXOR[prePos];
    // printf("i=%d prePos=%d xorVal=%d\n", i, prePos, xorVal);
    if (xorVal > ans) {
      ans = xorVal;
      l = prePos + 1;
      r = i;
    }

    trie.Insert(preXOR[i], i);
  }
  printf("%d %d %d\n", ans, l, r);
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*

*/