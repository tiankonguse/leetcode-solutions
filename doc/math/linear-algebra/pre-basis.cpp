/*
 前缀线性基
https://www.cnblogs.com/bianchengmao/p/16713133.html
*/

#include <bits/stdc++.h>
typedef long long ll;

class PrefixLinearBasis {
  static constexpr int K = 32;
  vector<vector<ll>> basis;  // 前缀线性基
  vector<vector<ll>> pos;    // 最后一个修改i这个位置的数
  int num = 0;               // 线性基中元素个数

 public:
  PrefixLinearBasis() {}
  void Init(int n) {  //
    basis.resize(n + 1, vector<ll>(K, 0));
    pos.resize(n + 1, vector<ll>(K, 0));
    num = 0;
  }

  // 如果对于基底的某个位置上的数有能更新的数，就进行替换
  // 以保证对于某个右端点 R 能尽可能的用靠近 R 的数作为基
  // 也就保证了所有 [L,R] 中的数都尽可能的参与构造这个数。
  void Insert(ll x) {
    num++;
    for (int i = 0; i < K; i++) {  // 复制前num-1个线性基
      basis[num][i] = basis[num - 1][i];
      pos[num][i] = pos[num - 1][i];
    }

    ll P = num;
    for (int i = K - 1; i >= 0; i--) {
      if ((x >> i) & 1) {
        if (basis[num][i]) {      // 插入失败
          if (pos[num][i] < P) {  // 交换位置
            swap(pos[num][i], P);
            swap(basis[num][i], x);
          }
          x ^= basis[num][i];  // 异或
        } else {               // 插入成功
          basis[num][i] = x;
          pos[num][i] = P;
          break;
        }
      }
    }
  }
  int QueryMax(int l, int r) {  // 查询[l,r]中的最大值
    int res = 0;
    for (int i = K - 1; i >= 0; i--) {
      if (pos[r][i] < l) continue;
      if ((res ^ basis[r][i]) > res) res ^= basis[r][i];
    }
    return res;
  }
  int QueryMin(int l, int r) {  // 查询[l,r]中的最小值
    for (int i = 0; i < K; i++) {
      if (pos[r][i] < l) continue;
      if (basis[r][i]) return basis[r][i];
    }
    return 0;
  }
};