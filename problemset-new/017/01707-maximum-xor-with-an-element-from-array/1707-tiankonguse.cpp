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

const int kind = 2, N = 10000001;
int tire[N][kind];
ll word[N];
int tire_index = 0;
const int max_bit = 32;
const ll one = 1;
const ll onezero[2] = {0, 1};

void Init() {
  memset(word, -1, sizeof(word));

  // 从 1 开始，这样左右不存在时，可以直接判断出来
  memset(tire[1], 0, sizeof(tire[1]));
  tire_index = 2;
}

void Insert(ll val) {
  int p = 1;
  for (int i = max_bit; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (tire[p][v] == 0) {
      memset(tire[tire_index], 0, sizeof(tire[tire_index]));
      word[tire_index] = -1;
      tire[p][v] = tire_index++;
    }
    p = tire[p][v];
  }
  word[p] = val;
}

// 由于可能 x > m，所以需要边找边计算
// 明确小于的时候，直接根据异或值，取相反的就是最大的
// 处于等于边界时，特殊判断
// flag: 是否明确小于
ll Query(ll x, ll m, int p = 1, int i = max_bit, int flag = false) {
  if (p == 0) {
    return -1;
  }

  if (word[p] != -1) {  // 叶子节点
    return x;
  }

  if (flag == false) {  // <= m
    int v = (m >> i) & 1;
    if (v == 1) {  // 0 和 1 都可以选择. 1 是边界，0 是明确小于
      ll right_val = Query(x ^ (onezero[1] << i), m, tire[p][1], i - 1, false);
      ll left_val = Query(x ^ (onezero[0] << i), m, tire[p][0], i - 1, true);
      return max(right_val, left_val);
    } else {
      return Query(x ^ (onezero[0] << i), m, tire[p][0], i - 1, false);
    }
  } else {  // < m
    int v = (x >> i) & 1;
    if (tire[p][!v]) {
      return Query(x ^ (onezero[!v] << i), m, tire[p][!v], i - 1, true);
    } else if (tire[p][v]) {
      return Query(x ^ (onezero[v] << i), m, tire[p][v], i - 1, true);
    } else {
      return -1;
    }
  }
  return -1;
}

class Solution {
 public:
  vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
    Init();
    sort(nums.begin(), nums.end());
    int min_val = nums[0];
    for (auto v : nums) {
      Insert(v);
    }

    int n = queries.size();
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
      int x = queries[i][0];
      int m = queries[i][1];

      if (min_val <= m) {
        ans[i] = Query(x, m);
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
