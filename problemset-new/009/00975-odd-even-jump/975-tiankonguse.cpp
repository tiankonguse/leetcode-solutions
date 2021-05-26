#include "base.h"

// https://leetcode-cn.com/problems/odd-even-jump/

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于
// vector/array: upper_bound(vec.begin(), vec.end(), v)
// map: m.upper_bound(v)
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);
// unordered_map / unordered_set
// 排序，小于是升序：[](auto&a, auto&b){ return a < b; })
// 优先队列 priority_queue<Node>：大于是升序
// struct Node{
//     int t;
//     bool operator<(const Node & that)const { return this->t > that.t; }
// };

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

class Solution {
  vector<int> next[2];
  unordered_map<int, bool> cache[2];
  int n;

  void Init(vector<int>& arr) {
    n = arr.size();

    next[0].resize(n, -1);  // 偶数调的下一个位置，小于等于，且最大的
    next[1].resize(n, -1);  // 奇数跳的下一个位置，大于等于，且最小的

    next[0][n - 1] = n;
    next[1][n - 1] = n;

    map<int, int> m;
    m[arr[n - 1]] = n - 1;  // 插入最后一个元素
    // build index
    for (int i = n - 2; i >= 0; i--) {
      int v = arr[i];

      auto it = m.lower_bound(v);
      if (it != m.end()) {  // 有奇数索引
        next[1][i] = it->second;
      }

      if (m.begin()->first <= v) {  // 有偶数索引
        // printf("i=%d have even next, first[%d]<v[%d]\n", i, m.begin()->first,
        //        v);
        if (it == m.end() || it->first > v) {
          it--;
        }
        next[0][i] = it->second;
      }

      m[v] = i;
    }

    // for (int i = 0; i < n; i++) {
    //   printf("i=%d old[%d] even[%d]\n", i, next[1][i], next[0][i]);
    // }

    cache[0][n] = cache[1][n] = true;
  }

  bool Check(int pos, int flag) {
    if (cache[flag].count(pos)) {
      return cache[flag][pos];
    }

    if (next[flag][pos] == -1) {
      return cache[flag][pos] = false;
    }

    int v = next[flag][pos];

    return cache[flag][pos] = Check(v, 1 - flag);
  }

 public:
  int oddEvenJumps(vector<int>& arr) {
    Init(arr);

    // search good starting index
    int ans = 0;

    for (int i = n - 1; i >= 0; i--) {
      if (Check(i, 1)) {
        ans++;
      }
    }

    return ans;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
