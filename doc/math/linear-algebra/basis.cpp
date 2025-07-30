/*
 线性基
https://oi-wiki.org/math/linear-algebra/basis/
https://oi.men.ci/linear-basis-notes/
https://www.cnblogs.com/Plozia/p/16156560.html
https://blog.sengxian.com/algorithms/linear-basis
https://ouuan.github.io/post/%E7%BA%BF%E6%80%A7%E5%9F%BA%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/
https://zhuanlan.zhihu.com/p/139074556
https://ksmeow.moe/linear_basis/
https://www.ruanx.net/linear-basis/
https://www.cnblogs.com/bianchengmao/p/16713133.html


线性基，是线性代数中的概念，在信息学竞赛中，前缀线性基是线性基的扩展，他们主要用于处理有关异或和的极值问题。

一组线性无关的向量即可作为一组基底，张起一个线性的向量空间，这个基底即称为线性基。
利用线性基的基底进行线性运算，可表示向量空间内的所有向量，换句话说，所有向量都可以拆成基底的线性组合。

根据异或的原理，将一个数字拆成他的二进制形式，将二进制形式用向量来表示。
由于一组线性无关的向量可以张起一个向量空间，因此可以考虑构造这样一组数字的二进制形式组成的线性基。
在这个线性基中，通过基底的线性组合、异或运算，从而可以表达所有的异或结果。

性质：
1. 线性基是一个集合，每个元素都是一个向量。
2. 线性基中的向量可以相互异或得到原集合中的任何一个元素；
3. 线性基合并:暴力处理，即将要合并的一组线性基暴力地插入到另一组线性基即可。
4. 线性基二进制最高位互不相同
5. 线性基的异或集合中，每个元素的异或方案唯一 ，且异或集合中不存在 0
6. 线性基中元素互相异或，异或集合不变

功能：
1. 判断一个数能否表示成某数集子集的异或和
2. 求一个数表示成某数集子集异或和的方案数；
3. 求某数集子集的最大/最小/第 k 大/第 k 小异或和；
4. 求一个数在某数集子集异或和中的排名。


题目：
彩灯（洛谷-P3857）(线性基中元素个数)：
元素（HYSBZ-2460）(添加线性基+贪心)：
同题：元素（洛谷-P4570）：
幸运数字（洛谷-P3292）(最大异或和+LCA)：
Operation（HDU-6579）(前缀线性基)：
Ivan and Burgers（CF-1100F）(前缀线性基)：
leetcode-3630,周赛460-P4, 线性基最大异或值 https://leetcode.cn/problems/partition-array-for-maximum-xor-and-and/description/
P4151 [WC2011] 最大XOR和路径 https://www.luogu.com.cn/problem/P4151


*/

#include <bits/stdc++.h>
typedef long long ll;

class LinearBasis {
  static constexpr int K = 32;
  ll basis[K];  // 用于32位整数
  ll unit[K];   // 用于32位整数
  ll cnt;

 public:
  LinearBasis() { Init(); }
  void Init() { fill(basis, basis + 32, 0); }

  // 新加入的数字 x，要么被添加进线性基，要么经过一系列操作后变成了 0
  // 如果变成了 0，说明这个数字 x 对应的二进制向量不属于极大线性无关组。
  void Insert(ll x) {
    for (int i = K - 1; i >= 0; --i) {
      if ((x >> i) & 1) {
        if (basis[i] == 0) {
          basis[i] = x;
          break;
        } else {
          x ^= basis[i];
        }
      }
    }
  }

  // 当两个线性基需要合并时，直接将一个线性基暴力的插入另一个线性基即可
  void Union(const LinearBasis &other) {
    for (int i = 0; i < K; i++) {
      Insert(other.basis[i]);
    }
  }

  // 当要查询最大值时，就从高位向低位扫描线性基，如果异或后使得结果变大，就异或进答案中
  // 由于没有正交化，不能直接使用 1<<i 进行运算
  ll QueryMax() {
    ll x = 0;
    for (int i = K - 1; i >= 0; --i) {
      if ((basis[i] ^ x) > x) {
        x ^= basis[i];  // 根据线性基的性质，对整个数组进行异或，就是最大值
      }
    }
    return x;
  }

  // 当要查询最小值时，最低位上的线性基即为答案
  // 假设我们有数字 3，线性基的第 1 位会存储 3，而此时能表示的最小值就是 3，而不是 1 << 1 = 2
  ll QueryMin() {
    for (int i = 0; i < K; i++) {
      if (basis[i]) {
        return basis[i];
      }
    }
    return 0;
  }

  // 由于线性基二进制最高位互不相同，因此要将线性基改造为每一位相互独立
  void Rebuild() {
    for (int i = K - 1; i >= 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        if (basis[i] & (1LL << j)) {
          basis[i] ^= basis[j];  // 消去 basis[i] 的第 j 位
        }
      }
    }

    cnt = 0;
    for (int i = 0; i < K; i++) {
      if (basis[i]) {
        unit[cnt++] = basis[i];
      }
    }
  }

  // 第 k 小值
  // 查询第k小的值，若要查k大，将k换为n-k+1即可
  ll QueryKth(ll k) {
    ll res = 0;
    if (k >= (1LL << cnt)) {
      return -1;
    }
    for (int i = K - 1; i >= 0; i--) {
      if (k & (1LL << i)) {
        res ^= unit[i];
      }
    }
    return res;
  }
};