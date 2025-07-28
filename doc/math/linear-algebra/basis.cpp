/*
 线性基
https://oi-wiki.org/math/linear-algebra/basis/
https://oi.men.ci/linear-basis-notes/

 性质：
 1. 线性基是一个集合，每个元素都是一个向量。
 2. 线性基中的向量可以相互异或得到原集合中的任何一个元素；
 3. 线性基合并:
暴力处理，即将要合并的一组线性基暴力地插入到另一组线性基即可。单次合并的时间复杂度是O(n^2)（异或线性基）或
O(n^3)（实数线性基）。 功能：
1. 判断一个数能否表示成某数集子集的异或和
2. 求一个数表示成某数集子集异或和的方案数；
3. 求某数集子集的最大/最小/第 k 大/第 k 小异或和；
4. 求一个数在某数集子集异或和中的排名。
*/

#include <bits/stdc++.h>
typedef long long ll;

class LinearBasis {
  static constexpr int K = 32;
  ll basisArray[K];  // 用于32位整数

 public:
  LinearBasis() { Init(); }
  void Init() { fill(basisArray, basisArray + 32, 0); }
  void Insert(ll x) {
    for (int i = 31; i >= 0; --i) {
      if ((x >> i) & 1) {
        if (basisArray[i] == 0) {
          basisArray[i] = x;
          break;
        } else {
          x ^= basisArray[i];
        }
      }
    }
  }
  void mergeFrom(const LinearBasis &other) {
    for (int i = 0; i < K; i++) {
      Insert(other.basisArray[i]);
    }
  }
  ll queryMax() {
    ll x = 0;
    for (int i = K - 1; i >= 0; --i) {
      if ((basisArray[i] ^ x) > x) {
        x ^= basisArray[i];  // 根据线性基的性质，对整个数组进行异或，就是最大值
      }
    }
    return x;
  }
};