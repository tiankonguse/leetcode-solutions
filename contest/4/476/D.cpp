
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
// 解答错误 1028 / 1041 个通过的测试用例©leetcode
/*
线段树：单点更新，区间查询
特征：不需要延迟标记与PushDown，log(N)的更新时间复杂度

输入数组： vector<int> str; [0, n-1]

SegTree segTree;
segTree.Init(str); // 内部会对数组进行右移，转化为 [1,n]
segTree.Build();
segTree.Update(l, val); // 单点 l 都加上 val, 数据范围 [1,n]
segTree.QueryMax/QueryMin/QuerySum 区间查询, 数据范围 [1,n]
*/

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct Node {
  ll sumVal;
  pair<ll, int> leftNumVal;   // <len, val>
  pair<ll, int> rightNumVal;  // <len, val>
  ll len;
};
struct SegTree {
  vector<Node> NodeVal;
  vector<ll> str;
  vector<pair<ll, ll>> ranges;

  void Init(vector<int>& str_, const ll default_val = 0) {
    maxNM = str_.size() + 1;
    NodeVal.resize(maxNM << 2);
    str.resize(maxNM << 2);
    ranges.resize(maxNM << 2);

    str.clear();
    // default_val 初始值按需设置，一般是0，也可以按需设置为最大值或者最小值
    str.resize(maxNM + 1, default_val);
    for (int i = 0; i < str_.size(); i++) {
      str[i + 1] = str_[i];
    }
  }

  void Merge(Node& parent, Node& leftChild, Node& rightChild) {
    parent.len = leftChild.len + rightChild.len;
    if (leftChild.rightNumVal.second <= rightChild.leftNumVal.second) {
      if (leftChild.rightNumVal.first == leftChild.len && rightChild.leftNumVal.first == rightChild.len) {  // 全部升序
        parent.leftNumVal = {leftChild.len + rightChild.len, leftChild.leftNumVal.second};
        parent.rightNumVal = {leftChild.len + rightChild.len, rightChild.rightNumVal.second};
        parent.sumVal = leftChild.len * rightChild.len + leftChild.sumVal + rightChild.sumVal;
      } else if (leftChild.rightNumVal.first == leftChild.len) {  // 左边全部升序
        parent.leftNumVal = {leftChild.len + rightChild.leftNumVal.first, leftChild.leftNumVal.second};
        parent.rightNumVal = rightChild.rightNumVal;
        parent.sumVal = rightChild.leftNumVal.first * leftChild.len + leftChild.sumVal + rightChild.sumVal;
      } else if (rightChild.leftNumVal.first == rightChild.len) {  // 右边全部升序
        parent.leftNumVal = leftChild.leftNumVal;
        parent.rightNumVal = {leftChild.rightNumVal.first + rightChild.len, rightChild.rightNumVal.second};
        parent.sumVal = leftChild.rightNumVal.first * rightChild.len + leftChild.sumVal + rightChild.sumVal;
      } else {  // 中间连接处升序
        parent.leftNumVal = leftChild.leftNumVal;
        parent.rightNumVal = rightChild.rightNumVal;
        parent.sumVal =
            leftChild.rightNumVal.first * rightChild.leftNumVal.first + leftChild.sumVal + rightChild.sumVal;
      }

    } else {  // 没有关系
      parent.leftNumVal = leftChild.leftNumVal;
      parent.rightNumVal = rightChild.rightNumVal;
      parent.sumVal = leftChild.sumVal + rightChild.sumVal;
    }
  }

  // 合并函数，按需进行合并
  void PushUp(int rt, int l, int r) {
    int L = rt << 1;
    int R = rt << 1 | 1;
    Merge(NodeVal[rt], NodeVal[L], NodeVal[R]);
  }
  int Num(pair<ll, ll> p) { return p.second - p.first + 1; }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    ranges[rt] = {l, r};
    if (l == r) {
      NodeVal[rt].sumVal = 1;
      NodeVal[rt].leftNumVal = NodeVal[rt].rightNumVal = {1, str[l]};
      NodeVal[rt].len = 1;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt, l, r);
  }

  Node Query(int QL, int QR, int l = 1, int r = maxNM, int rt = 1) {
    if (QL <= l && r <= QR) {
      return NodeVal[rt];
    }
    int m = (l + r) >> 1;
    Node ret;
    if (QL <= m && m < QR) {  // 跨越两个区间
      auto leftPart = Query(QL, QR, lson);
      auto rightPart = Query(QL, QR, rson);
      Merge(ret, leftPart, rightPart);
    } else if (QL <= m) {  // 只在左区间
      ret = Query(QL, QR, lson);
    } else if (m < QR) {  // 只在右区间
      ret = Query(QL, QR, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
    segTree.Init(nums);
    segTree.Build();

    vector<long long> res;
    res.reserve(queries.size());
    for (auto& q : queries) {
      int l = q[0] + 1;
      int r = q[1] + 1;
      auto node = segTree.Query(l, r);
      res.push_back(node.sumVal);
    }
    return res;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif