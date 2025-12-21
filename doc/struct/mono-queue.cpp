/*
单调队列
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int max3 = 2010, max4 = 50010, max5 = 500010, max6 = 2000010;

// 单调递减队列，队首是最大值
struct MonoQueueMax {
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
    while (l < r && idx[l] < pos) l++;
  }
  inline ll top() { return val[l]; }
  inline bool empty() { return l == r; }
};

// 单调递增队列，队首是最小值
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
    while (l < r && idx[l] < pos) l++;
  }
  inline ll top() { return val[l]; }
  inline bool empty() { return l == r; }
};
