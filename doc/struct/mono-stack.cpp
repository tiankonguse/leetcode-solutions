/*
单调栈：满足单调性的栈
https://oi-wiki.org/ds/monotonous-stack/

应用1：离线 RMQ
n 个元素，Q 次询问，每次询问 [l,r] 区间最大值。 
所有询问按右端点排序，r 之前的入单调递减栈，二分查找，第一个大于等于 l 的是答案。  
复杂度：O(q * log(q) + q * log(n) )
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int max3 = 2010, max4 = 50010, max5 = 500010, max6 = 2000010;

// 单调递减栈，栈顶是最小值
struct MonoStackMax {
  int idx[max4];
  ll val[max4];
  int l, r;
  inline void reset() { l = 0, r = 0; }
  inline void push(ll v, int pos) {
    while (l < r && val[r - 1] <= v) r--;
    val[r] = v;
    idx[r] = pos;
    r++;
  }
  inline void pop(int pos) {
    while (l < r && idx[r - 1] < pos) r--;
  }
  inline ll top() { return val[r - 1]; }
  inline bool empty() { return l == r; }
};

// 单调递增栈，栈顶是最大值
struct MonoQueueMin {
  int idx[max4];
  ll val[max4];
  int l, r;
  inline void reset() { l = 0, r = 0; }
  inline void push(ll v, int pos) {
    while (l < r && val[r - 1] >= v) r--;
    val[r] = v;
    idx[r] = pos;
    r++;
  }
  inline void pop(int pos) {
    while (l < r && idx[r - 1] < pos) r--;
  }
  inline ll top() { return val[r - 1]; }
  inline bool empty() { return l == r; }
};