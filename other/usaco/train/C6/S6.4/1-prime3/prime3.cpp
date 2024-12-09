/*
ID: tiankonguse
TASK: prime3
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "prime3"
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
const int max3 = 2010, max4 = 20010, max5 = 500010, max6 = 2000010;

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

const int N = 100000;
const int M = 9600;
bool is[N];
int prm[M];
int K;
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return K = k;
}

struct Node {
  int endFlag;
  int val;
  int next[10];
};
Node nodes[max5];
const int BIT = 5;
const int BASE[] = {1, 10, 100, 1000, 10000};
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = 0;
    node.val = 0;
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
  void Insert(const int num) {
    int root = 0;
    for (int i = BIT - 1; i >= 0; i--) {
      int v = (num / BASE[i]) % 10;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      root = nodes[root].next[v];
      nodes[root].val = v;
    }
    nodes[root].endFlag = 1;
  }
};

Trie trie;
vector<int> preSum;  // [0,5) [5,10) 10, 11
vector<vector<int>> preRoot;
const int MaxBit = 6;  // 增加前缀0

enum {
  ROW0 = 0,
  ROW1 = 1,
  ROW2 = 2,
  ROW3 = 3,
  ROW4 = 4,
  COL0 = 5,
  COL1 = 6,
  COL2 = 7,
  COL3 = 8,
  COL4 = 9,
  DOWN = 10,
  UP = 11,
  END = 12
};

set<string> ans;
int sum, first;

bool Check(int index, int num) {
  int root = preRoot[index].back();
  if (nodes[root].next[num] == -1) {
    // printf("index=%d root=%d num=%d empty\n", index, root, num);
    return false;
  }
  if (preSum[index] + num > sum) {
    // printf("preSum=%d index=%d num=%d > sum=%d \n", preSum[index], index,
    // num,
    //        sum);
    return false;
  }

  int leftNum = MaxBit - 1 - preRoot[index].size();
  if (leftNum > 0 && preSum[index] + num == sum) {
    // printf("preSum=%d index=%d num=%d  sum=%d leftNum=%d > 0\n",
    // preSum[index],
    //        index, num, sum, leftNum);
    return false;  // 至少为1
  }
  if (preSum[index] + num + leftNum * 9 < sum) return false;  // 全部是 9
  return true;
}

bool Add(int index, int num) {
  int root = preRoot[index].back();
  int p = nodes[root].next[num];
  preRoot[index].push_back(p);
  preSum[index] += num;
  return true;
}

bool Remove(int index, int num) {
  preRoot[index].pop_back();
  preSum[index] -= num;
  return true;
}

void UpdateAns() {
  string buf;
  buf.reserve(31);
  for (int i = 0; i < 5; i++) {
    for (int j = 1; j <= 5; j++) {
      buf.push_back('0' + nodes[preRoot[i][j]].val);
    }
    buf.push_back('\n');
  }
  ans.insert(buf);
}

/*
(0,0)
(1,0) (0,1)                    -> (-1,2)
(2,0) (1,1) (0,2)              -> (-1,3)
(3,0) (2,1) (1,2) (0,3)        -> (-1,4)
(4,0) (3,1) (2,2) (1,3) (0,4)  -> (-1,5)
      (4,1) (3,2) (2,3) (1,4)  -> ( 0,5)
            (4,2) (3,3) (2,4)  -> ( 1,5)
                  (4,3) (3,4)  -> ( 2,5)
                        (4,4)  -> ( 3,5)
*/
void Dfs(int row, int col, int k) {
  if (k == 25) {
    UpdateAns();
    return;
  }
  //   printf("old row=%d col=%d\n", row, col);
  if (row == -1 && col == 5) {  // 右上角
    row = 4;
    col = 1;
  } else if (row == -1) {  // 第一行到头
    row = col;
    col = 0;
  } else if (col == 5) {  // 最后一列
    col = row + 2;
    row = 4;
  }
  //   printf("update row=%d col=%d\n", row, col);
  int rootRow = 0;
  int startIndex = 0;
  if (row == 0) {  // 第一行, 不能有前缀 0
    rootRow = preRoot[ROW0].back();
    startIndex = 1;
  } else if (col == 0) {  // 第一列, 不能有前缀 0
    rootRow = preRoot[COL0].back();
    startIndex = 1;
  } else {
    startIndex = 0;
    if (row < col) {
      rootRow = preRoot[row].back();  // 行列都可以，取行的
    } else {
      rootRow = preRoot[col].back();  // 行列都可以，取行的
    }
  }
  //   printf("startIndex=%d rootRow=%d\n", startIndex, rootRow);

  for (int v = startIndex; v < 10; v++) {
    int p = nodes[rootRow].next[v];
    if (p == -1) {
      //   printf("v=%d no next\n", v);
      continue;
    }
    // 选择 v
    if (!Check(ROW0 + row, v)) {
      //   printf("row check no pass, row=%d v=%d\n", ROW0 + row, v);
      continue;
    }
    if (!Check(COL0 + col, v)) {
      //   printf("col check no pass, col=%d v=%d\n", COL0 + col, v);
      continue;
    }
    if (row == col && !Check(DOWN, v)) {
      //   printf("down check no pass, DOWN=%d v=%d\n", DOWN, v);
      continue;
    }
    if (row + col == 4 && !Check(UP, v)) {
      //   printf("UP check no pass, UP=%d v=%d\n", UP, v);
      continue;
    }

    Add(ROW0 + row, v);
    Add(COL0 + col, v);
    row == col&& Add(DOWN, v);
    row + col == 4 && Add(UP, v);

    Dfs(row - 1, col + 1, k + 1);

    Remove(ROW0 + row, v);
    Remove(COL0 + col, v);
    row == col&& Remove(DOWN, v);
    row + col == 4 && Remove(UP, v);
  }
}

void Solver() {  //
  getprm();
  trie.Init();
  for (int k = lower_bound(prm, prm + K, 10000) - prm; k < K; k++) {
    trie.Insert(prm[k]);
  }

  preSum.resize(END);
  preRoot.resize(END);
  for (int i = 0; i < END; i++) {
    preRoot[i].push_back(0);  // 插入根节点
  }

  scanf("%d%d", &sum, &first);
  Add(ROW0, first);
  Add(COL0, first);
  Add(DOWN, first);
  Dfs(1, 0, 1);

  int ansNum = ans.size();
  if (ansNum == 0) {
    printf("NONE\n");
  } else {
    bool first = true;
    for (auto& s : ans) {
      if (!first) {
        printf("\n");
      }
      first = false;
      printf("%s", s.data());
    }
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