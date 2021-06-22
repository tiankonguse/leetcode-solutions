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

// 基本思路，计算出一个值后，检查之后的值是否可以更优
// 复杂度：O(n^2)
// 可以构造出极端数据，使得内部循环退化
// 构造方法：后缀为临时答案为逆序，比如 v, v-1,...,3,2,1。前缀越靠前，跳数依次增大。结果是，每轮需要将所有的值都减一
class Solution {
 public:
  int minJump(vector<int>& jump) {
    int n = jump.size();

    vector<int> ans(n, 1);
    for (int i = n - 2; i >= 0; i--) {
      int next_pos = i + jump[i];
      if (next_pos >= n) {
        ans[i] = 1;
      } else {
        ans[i] = ans[next_pos] + 1;
      }

      for (int j = i + 1; j < n && ans[j] >= ans[i] + 1; j++) {
        ans[j] = ans[i] + 1;
      }
    }

    return ans[0];
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}