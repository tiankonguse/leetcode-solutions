
#include <bits/stdc++.h>

// 莫队
namespace MoQueue {

vector<int> sorted_A;  // 1-base
vector<int> B;         // 离散化后的值, 值是1-base
int BLOCK_SIZE = 0;    // 每个组的大小

int current_size = 0;
long long total_ops = 0;

struct Query {
  int l, r, id;
  long long answer;  // 存储答案
  Query(int l, int r, int id) : l(l), r(r), id(id), answer(0) {}
};

void Add(int x) {
  // 1. 更新总操作次数（基于旧中位数）
  long long raw_x = sorted_A[x];  // 离散化值 x 对应的原始值

  current_size++;
  // update total_ops
}

void Remove(int x) {
  // 1. 更新总操作次数（基于旧中位数）
  long long raw_x = sorted_A[x];

  current_size--;
  // update total_ops
}

void Init(vector<int>& A) {
  int n = A.size();
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

  total_ops = 0;
  current_size = 0;
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