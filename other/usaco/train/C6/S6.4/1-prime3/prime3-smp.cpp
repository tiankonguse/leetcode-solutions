/*
ID: tiankonguse
TASK: prime3
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "prime3"
#define TASKEX "-smp"

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
const int max3 = 2010, max4 = 15481, max5 = 500010, max6 = 2000010;

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

const int N = 600;
const int M = 200;
// bool is[N];
bitset<N> is;  // 初始化
int prm[M];
int K;
int getprm() {
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  prm[k++] = 2;
  is.set(0);
  is.set(1);
  // is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is.set(i);
  for (i = 3; i < e; i += 2) {
    if (!is.test(i)) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is.set(j);
    }
  }
  for (; i < N; i += 2)
    if (!is.test(i)) prm[k++] = i;
  return K = k;
}

struct Node {
  int val;
  int next[10];
};
vector<Node> nodes;
// Node nodes[max4];
const int BIT = 5;
const int BASE[] = {1, 10, 100, 1000, 10000};
class Trie {
 public:
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    // node.endFlag = 0;
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
    nodes.resize(5000);
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

      // if (25121 == num) {
      //   printf("insert 25121, v=%d root=%d\n", v, root);
      // }
    }
    // nodes[root].endFlag = 1;
    // if (25121 == num) {
    //   printf("insert 25121 root=%d\n", root);
    // }
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

bool Check(int index, int num, int preVal) {
  int root = preRoot[index].back();
  if (nodes[root].next[num] == -1) {
    // if (preVal == 25121)
    //   printf("index=%d root=%d num=%d empty\n", index, root, num);
    return false;
  }
  if (preSum[index] + num > sum) {
    // if (preVal == 25121)
    //   printf("preSum=%d index=%d num=%d > sum=%d \n", preSum[index], index,
    //   num,
    //          sum);
    return false;
  }

  int leftNum = MaxBit - 1 - preRoot[index].size();
  if (leftNum > 0 && preSum[index] + num == sum) {
    // if (preVal == 25121)
    //   printf("preSum=%d index=%d num=%d  sum=%d leftNum=%d > 0\n",
    //          preSum[index], index, num, sum, leftNum);
    return false;  // 至少为1
  }
  if (preSum[index] + num + leftNum * 9 < sum) {
    // if (preVal == 25121)
    //   printf("preSum=%d index=%d num=%d  leftNum=%d  9*leftNum=%d < sum=%d
    //   \n",
    //          preSum[index], index, num, leftNum, leftNum * 9, sum);
    return false;  // 全部是 9
  }
  return true;
}

bool CheckUp(int num) {
  int root = 0;
  int tmpSum = num;
  if (nodes[root].next[num] == -1) return false;
  root = nodes[root].next[num];

  for (int i = 3, j = 1; i >= 0; i--, j++) {
    int p = preRoot[i][j + 1];
    int v = nodes[p].val;
    tmpSum += v;
    if (nodes[root].next[v] == -1 || tmpSum > sum) return false;
    root = nodes[root].next[v];
  }

  return tmpSum == sum;
}

bool Add(const int index, const int num) {
  int root = preRoot[index].back();
  int p = nodes[root].next[num];
  preRoot[index].push_back(p);
  preSum[index] += num;
  return true;
}

bool Remove(const int index, const int num) {
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

int maxK = 0;
void Dfs(int row, int col, int k, int preVal) {
  if (k == 25) {
    UpdateAns();
    return;
  }
  if (col == 5) {
    row++;
    col = 0;
  }
  // if (preVal == 25121)
  //   printf("old row=%d col=%d preVal=%d\n", row, col, preVal);
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
    rootRow = preRoot[ROW0 + row].back();
  }

  // if (preVal == 25121)
  //   printf("startIndex=%d rootRow=%d\n", startIndex, rootRow);

  for (int v = startIndex; v < 10; v++) {
    int p = nodes[rootRow].next[v];
    if (p == -1) {
      // if (preVal == 25121) printf("v=%d no next\n", v);
      continue;
    }
    // 选择 v
    if (!Check(ROW0 + row, v, preVal)) {
      // if (preVal == 25121)
      //   printf("row check no pass, row=%d v=%d\n", ROW0 + row, v);
      continue;
    }
    if (!Check(COL0 + col, v, preVal)) {
      // if (preVal == 25121)
      //   printf("col check no pass, col=%d v=%d\n", COL0 + col, v);
      continue;
    }
    if (row == col && !Check(DOWN, v, preVal)) {
      // if (preVal == 25121)
      //   printf("down check no pass, DOWN=%d v=%d\n", DOWN, v);
      continue;
    }
    if (row == 4 && col == 0 && !CheckUp(v)) {
      // if (preVal == 25121) printf("UP check no pass, UP=%d v=%d\n", UP,
      // v);
      continue;
    }

    Add(ROW0 + row, v);
    Add(COL0 + col, v);
    row == col&& Add(DOWN, v);
    // row + col == 4 && Add(UP, v);

    Dfs(row, col + 1, k + 1, preVal * 10 + v);

    Remove(ROW0 + row, v);
    Remove(COL0 + col, v);
    row == col&& Remove(DOWN, v);
    // row == 4 && col == 0 && Remove(UP, v);
  }
}

bool IsSumEq(int v) {
  int tmpSum = 0;
  while (v) {
    tmpSum += v % 10;
    v /= 10;
  }
  return tmpSum == sum;
}
bool IsPrm(int v) {
  for (int k = 0; k < K && prm[k] * prm[k] <= v; k++) {
    if (v % prm[k] == 0) return false;
  }
  return true;
}

void Solver() {  //
  scanf("%d%d", &sum, &first);

  getprm();
  // printf("K=%d\n", K);
  trie.Init();
  for (int k = 10001; k < 100000; k += 2) {
    if (IsSumEq(k) && IsPrm(k)) {
      trie.Insert(k);
    }
  }
  // printf("index=%d\n", trie.index);

  preSum.resize(END);
  preRoot.resize(END);
  for (int i = 0; i < END; i++) {
    preRoot[i].push_back(0);  // 插入根节点
  }

  Add(ROW0, first);
  Add(COL0, first);
  Add(DOWN, first);
  Dfs(0, 1, 1, first);

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
Executing...
   Test 1: TEST OK [0.021 secs limit:2s, 3364 KB]
   Test 2: TEST OK [0.052 secs limit:2s, 3436 KB]
   Test 3: TEST OK [0.319 secs limit:2s, 3260 KB]
   Test 4: TEST OK [0.637 secs limit:2s, 3472 KB]
   Test 5: TEST OK [0.612 secs limit:2s, 3416 KB]
  > Run 6: Execution error: Your program (`prime3') used more than the
        allotted runtime of 2 seconds (it ended or was stopped at 2.607
        seconds) when presented with test case 6. It used 3432 KB of
        memory. 

        ------ Data for Run 6 [length=5 bytes] ------
        17 1 
        ----------------------------
    Test 6: RUNTIME 2.607>2 (3432 KB)
*/