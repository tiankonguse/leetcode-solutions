
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

namespace FenwickTree {
// 树状数组 (BIT) 的最大尺寸
vector<int> BIT;
int n;

void bit_init(int n_) {
  n = n_;
  BIT.resize(n + 1);
  fill(BIT.begin(), BIT.end(), 0);
}

void bit_update(int idx, int delta) {
  for (; idx <= n; idx += idx & -idx) {
    BIT[idx] += delta;
  }
}

int bit_query(int idx) {  // 查询 [1, idx] 的总数
  int sum = 0;
  for (; idx > 0; idx -= idx & -idx) {
    sum += BIT[idx];
  }
  return sum;
}
// O(log N) 查找排名第 K 的元素 (即中位数)
// 使用二分查找在 BIT 上定位
int find_kth(int k, int median_val) {
  if (k <= 0) return median_val;
  int low = 1, high = n;
  int median = n;

  // 经典二分查找
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (bit_query(mid) >= k) {
      median = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return median;
}

};  // namespace FenwickTree

// 莫队
namespace MoQueue {

vector<int> sorted_A;  // 1-base
vector<int> B;         // 离散化后的值, 值是1-base
int BLOCK_SIZE = 0;    // 每个组的大小

long long total_ops = 0;
int median_val = 1;  // 离散化值从 1 开始
int current_size = 0;

struct Query {
  int l, r, id;
  long long answer;  // 存储答案
  Query(int l, int r, int id) : l(l), r(r), id(id), answer(0) {}
};

void Update(int new_c) {  // 预期只移动一次
  if (new_c == median_val) return;

  if (new_c > median_val) {  // 中位数向右 (增大)
    // C -> C+1 (在离散化值上)
    for (int c = median_val; c < new_c; ++c) {
      // less_equal_c: 离散化值 <= c 的元素个数
      long long raw_x = sorted_A[c];  // 离散化值 x 对应的原始值
      long long raw_c = sorted_A[c + 1];

      long long less_equal_c = FenwickTree::bit_query(c);
      long long greater_c = current_size - less_equal_c;
      total_ops += (less_equal_c - greater_c) * (raw_c - raw_x);
    }
  } else {  // 中位数向左 (减小)
    // C -> C-1
    for (int c = median_val; c > new_c; --c) {
      // less_than_c: 离散化值 < c 的元素个数
      long long raw_x = sorted_A[c];  // 离散化值 x 对应的原始值
      long long raw_c = sorted_A[c - 1];
      long long less_than_c = FenwickTree::bit_query(c - 1);
      long long greater_equal_c = current_size - less_than_c;
      total_ops += (greater_equal_c - less_than_c) * (raw_c - raw_x);
    }
  }

  median_val = new_c;
}
void Add(int x) {
  // 1. 更新总操作次数（基于旧中位数）
  long long raw_x = sorted_A[x];  // 离散化值 x 对应的原始值
  long long raw_c = sorted_A[median_val];

  total_ops += abs(raw_x - raw_c);
  current_size++;

  // 2. 更新 BIT
  FenwickTree::bit_update(x, 1);

  // 3. 检查中位数是否需要调整
  int rank = (current_size + 1) / 2;
  int new_median = FenwickTree::find_kth(rank, median_val);
  Update(new_median);
}

void Remove(int x) {
  // 1. 更新总操作次数（基于旧中位数）
  long long raw_x = sorted_A[x];
  long long raw_c = sorted_A[median_val];

  total_ops -= abs(raw_x - raw_c);
  current_size--;

  // 2. 更新 BIT
  FenwickTree::bit_update(x, -1);

  if (current_size == 0) {
    assert(total_ops == 0);
    median_val = 1;  // 重置中位数，因为窗口为空
    return;
  }

  // 3. 检查中位数是否需要调整
  int rank = (current_size + 1) / 2;
  int new_median = FenwickTree::find_kth(rank, median_val);

  // 4. 修正总操作次数（中位数变动）
  Update(new_median);
}

void Init(vector<int>& A) {
  int n = A.size();
  MyPrintf("Init, n=%d\n", n);
  // 离散化
  vector<int> temp_A = A;
  sort(temp_A.begin(), temp_A.end());
  temp_A.erase(unique(temp_A.begin(), temp_A.end()), temp_A.end());

  sorted_A.resize(temp_A.size() + 1, 0);
  map<int, int> valToIdx;  // 值到下标，1-base
  for (int i = 1; i <= temp_A.size(); ++i) {
    int v = temp_A[i - 1];
    valToIdx[v] = i;  // 离散化值从 1 开始
    sorted_A[i] = v;
  }
  B.resize(n);
  for (int i = 1; i <= n; i++) {
    B[i - 1] = valToIdx[A[i - 1]];
  }
  int V_MAX = temp_A.size();
  BLOCK_SIZE = sqrt(n);
  MyPrintf("V_MAX=%d, BLOCK_SIZE=%d\n", V_MAX, BLOCK_SIZE);
  MyPrintf("A: ");
  for (int i = 0; i < n; i++) {
    MyPrintf("[%d]=%d ", i, A[i]);
  }
  MyPrintf("\n");

  MyPrintf("sorted_A: ");
  for (int i = 1; i <= V_MAX; i++) {
    MyPrintf("[%d]=%d ", i, sorted_A[i]);
  }
  MyPrintf("\n");
  MyPrintf("B: ");
  for (int i = 0; i < n; i++) {
    MyPrintf("[%d]=%d ", i, B[i]);
  }
  MyPrintf("\n");

  FenwickTree::bit_init(V_MAX);

  total_ops = 0;
  current_size = 0;
  median_val = 1;
}

void Solver(vector<int>& A, vector<MoQueue::Query>& queries) {
  Init(A);
  sort(queries.begin(), queries.end(), [](const Query& qa, const Query& qb) {
    int block_l_a = qa.l / BLOCK_SIZE;
    int block_l_b = qb.l / BLOCK_SIZE;

    if (block_l_a != block_l_b) {
      return block_l_a < block_l_b;
    }
    // 奇偶优化 (Mo's odd-even optimization)
    if (block_l_a % 2 == 0) {
      return qa.r < qb.r;
    } else {
      return qa.r > qb.r;
    }
  });

  int current_l = 0, current_r = -1;
  for (auto& q : queries) {
    // L 移动
    while (current_l > q.l) {
      current_l--;
      Add(B[current_l]);
    }
    while (current_l < q.l) {
      Remove(B[current_l]);
      current_l++;
    }

    // R 移动
    while (current_r < q.r) {
      current_r++;
      Add(B[current_r]);
    }
    while (current_r > q.r) {
      Remove(B[current_r]);
      current_r--;
    }

    // 存储答案
    q.answer = total_ops;
  }
}

};  // namespace MoQueue

class Solution {
 public:
  vector<ll> minOperations(vector<int>& A, int k, vector<vector<int>>& queries) {
    int n = A.size();
    vector<pair<int, int>> AB(n, {0, 0});  //{a, b}, nums[i] = a * k + b
    for (int i = 0; i < n; i++) {
      ll v = A[i];
      AB[i] = {v / k, v % k};
      A[i] = v / k;
    }

    vector<int> sameLeft(n, 0);
    for (int i = 1; i < n; i++) {
      if (AB[i].second == AB[i - 1].second) {
        sameLeft[i] = sameLeft[i - 1];
      } else {
        sameLeft[i] = i;
      }
    }
    int Q = queries.size();
    vector<ll> ans(Q, -1);
    vector<MoQueue::Query> queriesB;
    queriesB.reserve(Q);
    for (int i = 0; i < Q; i++) {
      auto& q = queries[i];
      int l = q[0], r = q[1];
      if (sameLeft[r] > l) {
        continue;  // b 不同，没有答案
      }
      queriesB.emplace_back(l, r, i);
    }
    if (queriesB.size() > 0) {
      MoQueue::Solver(A, queriesB);
      for (auto& q : queriesB) {
        ans[q.id] = q.answer;
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<int>& A, int k, vector<vector<int>>& queries, const vector<ll>& ans) {
  TEST_SMP3(Solution, minOperations, ans, A, k, queries);
}

int main() {
  // {
  //   vector<int> A = {1};
  //   int k = 1;
  //   vector<vector<int>> queries = {{0, 0}};
  //   const vector<ll> ans = {0};
  //   Test(A, k, queries, ans);
  // }
  {
    // 59958 - 32146 = 27812
    // 29979 - 16073 = 13906
    vector<int> A = {59958, 32146};
    int k = 2;
    vector<vector<int>> queries = {{0, 1}};
    const vector<ll> ans = {13906};
    Test(A, k, queries, ans);
  }
  return 0;
}

#endif