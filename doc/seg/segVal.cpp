
/*
权值线段树， 只有值当做下标

由于值的范围很大，普通线段树储存不下，这里每个点储存一个区间线段，插入时进行动态开点


SegTreeVal segTreeVal;
segTreeVal.Init(minVal, maxVal);
segTreeVal.Insert(k, v); // 生成一个独立的线段树
segTreeVal.Merge(x, y); // 合并两个线段树
segTreeVal.Add(k, x); // 等价于 Merge(Insert(k, 0), x)

*/


const int N = 10e5;
const int M = 20 * N;


struct Node {
  int L, R;
  int V;              // 当前子树上节点个数
  int F;              // 标记是否需要pushdown
  pair<int, int> LR;  // 左右区间
  pair<int, int> KV;   // 储存的值
} nodes[M];

struct SegTreeVal {
  int maxL, maxR;  // [maxL, maxR] key 范围
  int index;       // 0 代表空树

  void Init(int l, int r) {
    index = 0;
    maxL = l;
    maxR = r;
  }

  // 插入一个值，生成一个新的线段树
  int Insert(int k, int v = 1) { return Insert(maxL, maxR, k, v); }

  int Add(int k, int x) { return Merge(Insert(k), x); }

  void PushDown(int x) {
    auto& node = nodes[x];

    if (node.LR.first == node.LR.second) return;  // 不可拆分
    if (node.F == 0) return;                      // 已经拆分
    node.F = 0;

    auto& [l, r] = node.LR;
    auto& [k, v] = node.KV;
    int mid = (l + r) >> 1;
    if (k <= mid) {
      node.L = Insert(l, mid, k, v);
    } else {
      node.R = Insert(mid + 1, r, k, v);
    }
  }

  // 合并线段树
  int Merge(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;

    PushDown(x);
    PushDown(y);

    nodes[x].V += nodes[y].V;
    nodes[x].L = Merge(nodes[x].L, nodes[y].L);
    nodes[x].R = Merge(nodes[x].R, nodes[y].R);
    return x;
  }

  int Find(int k, int x) {
    if (x == 0) return -1;

    auto& node = nodes[x];

    if (node.F == 1) {  // 叶子节点
      if (node.KV.first == k) {
        return x;
      } else {
        return -1;
      }
    }

    auto& [l, r] = node.LR;
    int mid = (l + r) >> 1;
    if (k <= mid) {
      return Find(k, node.L);
    } else {
      return Find(k, node.R);
    }
  }

  int PreCount(int k, int x) {
    if (x == 0) return 0;

    auto& node = nodes[x];
    auto& [l, r] = node.LR;

    if (k >= r) return node.V;  // 整个树都满足要求
    if (k < l) return 0;        // 整个树都不满足要求

    if (node.F == 1) {  // 叶子节点
      if (node.KV.first <= k) {
        return node.KV.second;
      } else {
        return 0;
      }
    }

    return PreCount(k, node.L) + PreCount(k, node.R);
  }

 private:
  int Insert(int l, int r, int k, int v) {
    int x = ++index;
    auto& node = nodes[x];
    node.L = node.R = 0;
    node.V = 1;
    node.F = 1;
    node.KV = {k, v};
    node.LR = {l, r};
    return x;
  }
};

ValSegTree valSegTree;