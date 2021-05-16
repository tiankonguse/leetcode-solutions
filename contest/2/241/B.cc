#include "base.h"

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
  int GetDiffNum(int startFlag, const string& s) {
    int num = 0;
    int flag = startFlag;
    for (auto c : s) {
      int val = c - '0';
      if (flag != val) {
        num++;
      }
      flag = 1 - flag;
    }
    return num;
  }

 public:
  int minSwaps(string& s) {
    int zero = 0, one = 0;
    for (auto c : s) {
      if (c == '0') {
        zero++;
      } else {
        one++;
      }
    }

    if (zero == one + 1) {
      // 010
      int num = GetDiffNum(0, s);
      return num / 2;

    } else if (zero == one) {
      // 01
      int num = min(GetDiffNum(1, s), GetDiffNum(0, s));
      return num / 2;
    } else if (zero + 1 == one) {
      // 101
      int num = GetDiffNum(1, s);
      return num / 2;
    } else {
      return -1;
    }
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
