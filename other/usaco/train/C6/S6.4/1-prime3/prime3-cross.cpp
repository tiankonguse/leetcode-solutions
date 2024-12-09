/*
ID: tiankonguse
TASK: prime3
LANG: C++
MAC EOF: ctrl+D
*/
#define TASK "prime3"
#define TASKEX "-cross"

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
vector<vector<int>> preRoot;

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

struct LineInfo {
  int order;
  int row, col;  // 起始位置
  int x, y;      // 方向偏移量
  LineInfo(const int order_ = 0) {
    order = order_;
    if (ROW0 <= order_ && order_ <= ROW4) {
      row = order_;
      col = 0;
      x = 0;
      y = 1;
    }
    if (COL0 <= order_ && order_ <= COL4) {
      row = 0;
      col = order_ - COL0;
      x = 1;
      y = 0;
    }
    if (order_ == DOWN) {
      row = 0;
      col = 0;
      x = 1;
      y = 1;
    }
    if (order_ == UP) {
      row = 4;
      col = 0;
      x = -1;
      y = 1;
    }
  }
};
const vector<int> orders = {DOWN, UP,   ROW1, COL0, COL4, ROW3,
                            ROW2, COL1, COL2, COL3, ROW0, ROW4};
vector<LineInfo> lineInfos;
const int O = orders.size();

void InitOrder() {
  lineInfos.reserve(O);
  for (auto o : orders) {
    lineInfos.push_back(LineInfo(o));
  }
}

set<string> ans;
int sum, first;

bool CheckSum(int preSum, int index) {
  if (preSum > sum) {
    return false;
  }

  int leftNum = 4 - index;
  if (leftNum > 0 && preSum == sum) {
    return false;  // 至少为1
  }
  if (preSum + leftNum * 9 < sum) {
    return false;  // 全部是 9
  }
  return true;
}

void UpdateAns() {
  string buf;
  buf.reserve(31);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      buf.push_back('0' + preRoot[i][j]);
    }
    buf.push_back('\n');
  }
  ans.insert(buf);
}

// int maxK = 0;
void Dfs(const int o, const int index, const int root, const int preSum,
         const int preVal) {
  // if (maxK < o) {
  //   maxK = o;
  //   printf("maxK=%d\n", maxK);
  // }
  if (index == 5) {
    Dfs(o + 1, 0, 0, 0, 0);
    return;
  }
  if (o == O) {
    UpdateAns();
    return;
  }

  LineInfo& lineInfo = lineInfos[o];
  int& row = lineInfo.row;
  int& col = lineInfo.col;
  const int& x = lineInfo.x;
  const int& y = lineInfo.y;

  int startIndex = 0, endIndex = 10;
  if (row == 0) {  // 第一行, 不能有前缀 0
    startIndex = 1;
  } else if (col == 0) {  // 第一列, 不能有前缀 0
    startIndex = 1;
  } else {
    startIndex = 0;
  }

  bool valueNoSET = true;
  if (preRoot[row][col] != -1) {
    valueNoSET = false;
    startIndex = preRoot[row][col];
    endIndex = startIndex + 1;
  }
  // printf(
  //     "o=%d row=%d col=%d x=%d y=%d startIndex=%d endIndex=%d preSum=%d "
  //     "preVal=%d\n",
  //     o, row, col, x, y, startIndex, endIndex, preSum, preVal);

  for (int v = startIndex; v < endIndex; v++) {
    const int p = nodes[root].next[v];
    if (p == -1) {
      // printf("preVal=%d v=%d empty\n", preVal, v);
      continue;
    }
    if (!CheckSum(preSum + v, index)) {
      // printf("preVal=%d preSum=%d v=%d index=%d sum no pass\n", preVal,
      // preSum,
      //        v, index);
      continue;
    }
    if (valueNoSET) preRoot[row][col] = v;
    // if (lineInfo.order == ROW3 && col == 4) {
    //   printf("o=%d row=%d col=%d preSum=%d preVal=%d v=%d index=%d\n", o, row,
    //          col, preSum, preVal, v, index);
    // }
    row += x;
    col += y;
    Dfs(o, index + 1, p, preSum + v, preVal * 10 + v);
    row -= x;
    col -= y;
    if (valueNoSET) preRoot[row][col] = -1;
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
  InitOrder();
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

  preRoot.resize(5, vector<int>(5, -1));
  preRoot[0][0] = first;

  Dfs(0, 0, 0, 0, 0);

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
  // printf("ans=%d\n", int(ans.size()));
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  Solver();
  return 0;
}

/*
Executing...
   Test 1: TEST OK [0.011 secs limit:2s, 3208 KB]
   Test 2: TEST OK [0.025 secs limit:2s, 3312 KB]
   Test 3: TEST OK [0.088 secs limit:2s, 3360 KB]
   Test 4: TEST OK [0.070 secs limit:2s, 3444 KB]
   Test 5: TEST OK [0.070 secs limit:2s, 3392 KB]
   Test 6: TEST OK [0.154 secs limit:2s, 3440 KB]
   Test 7: TEST OK [0.182 secs limit:2s, 3484 KB]
   Test 8: TEST OK [0.231 secs limit:2s, 3376 KB]
   Test 9: TEST OK [0.382 secs limit:2s, 3256 KB]
   Test 10: TEST OK [0.382 secs limit:2s, 3340 KB]

All tests OK.
*/