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

int dp[30][30][30][2];  // {min, max}

class Solution {
 public:
  Solution() { memset(dp, 0, sizeof(dp)); }

  int MyMin(int& a, int b) {
    if (a == 0) {
      a = b;
    } else {
      a = min(a, b);
    }
    return a;
  }
  int MyMax(int& a, int b) {
    if (a == 0) {
      a = b;
    } else {
      a = max(a, b);
    }
    return a;
  }
  int dfs(int n, int a, int b, int flag) {
    int& ans = dp[n][a][b][flag];
    if (ans != 0) return ans;

    if (a + b == n + 1) {  // 直接碰面了
      return ans = 1;
    }

    int half_n = n / 2;
    int next_n = half_n + n % 2;

    for (int state = 0; state < (1 << half_n); state++) {
      int left = 0, mid = 0;

      int up_i = 1, down_i = n;
      int ok = true;
      for (int i = 0; i < half_n; i++, up_i++, down_i--) {
        int bit = (state >> i) & 1;

        // 检查是否是有效状态
        if (bit == 0 && (up_i == a || up_i == b)) {
          ok = false;
          break;
        }
        if (bit == 1 && (down_i == a || down_i == b)) {
          ok = false;
          break;
        }

        if (bit == 1) {  // 上面赢了
          if (up_i < a) left++;
          if (up_i > a && up_i < b) mid++;
        } else {  // 下面赢了
          if (down_i < a) left++;
          if (down_i > a && down_i < b) mid++;
        }
      }
      if (!ok) {
        continue;  // 无效状态
      }

      if (n % 2 == 1) {
        if (next_n < a) left++;
        if (next_n > a && next_n < b) mid++;
      }

      int next_a = left + 1;
      int next_b = left + mid + 2;
      if (flag == 0) {
        MyMin(ans, 1 + dfs(next_n, next_a, next_b, flag));
      } else {
        MyMax(ans, 1 + dfs(next_n, next_a, next_b, flag));
      }
    }
    // printf("n=%d a=%d b=%d half_n=%d ans=%d\n", n,a,b,half_n, ans);

    return ans;
  }
  vector<int> earliestAndLatest(int n, int a, int b) {
    return vector<int>({dfs(n, a, b, 0), dfs(n, a, b, 1)});
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
