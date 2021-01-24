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

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

const int kind = 2, N = 10000001;
int tire[N][kind];
ll word[N];
int tire_index = 0;
int max_bit = 32;
ll one = 1;

void Init() {
  memset(word, -1, sizeof(word));
  memset(tire[0], 0, sizeof(tire[0]));
  tire_index = 1;
}

void Insert(ll val) {
  int p = 0;
  for (int i = max_bit; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (tire[p][v] == 0) {
      memset(tire[tire_index], 0, sizeof(tire[tire_index]));
      word[tire_index] = -1;
      tire[p][v] = tire_index++;
    }
    p = tire[p][v];
  }
//   printf("val=%lld p=%d\n", val, p);
  word[p] = val;
}

// i： 处理到第 i 位
// flag: false 代表小于等于m
// falg: true  代表小于m
ll Query(ll x, ll m, int p = 0, int i = max_bit,
         int flag = false) {  // <=m , ^x
//   printf("q:x=%lld m=%lld p=%d i=%d flag=%d word=%lld\n", x, m, p, i, flag,
//          word[p]);
  if (word[p] != -1) {  // 叶子节点
    return x;
  }

  if (flag == false) {  // <= m
    int v = (m >> i) & 1;
    if (v == 1) {
      if (tire[p][1] == 0 && tire[p][0] == 0) {  // 没有下一个
        return -1;
      } else if (tire[p][1] != 0 && tire[p][0] == 0) {  // 有等于的，没小于的
        return Query(x ^ (one << i), m, tire[p][1], i - 1, false);
      } else if (tire[p][1] == 0 && tire[p][0] != 0) {  // 有小于的，没等于的
        return Query(x, m, tire[p][0], i - 1, true);
      } else if (tire[p][1] != 0 && tire[p][0] != 0) {  //有等于的，也有小于的
        ll right_val = Query(x ^ (one << i), m, tire[p][1], i - 1, false);
        ll left_val = Query(x, m, tire[p][0], i - 1, true);
        return max(right_val, left_val);
      }
    } else {
      if (tire[p][0] == 0) {
        return -1;
      } else {
        return Query(x, m, tire[p][0], i - 1, false);
      }
    }
  } else {  // < m
    int v = (x >> i) & 1;
    if (v == 1) {
      if (tire[p][0] != 0) {
        return Query(x, m, tire[p][0], i - 1, true);
      } else if (tire[p][1] != 0) {
        return Query(x ^ (one << i), m, tire[p][1], i - 1, true);
      } else {
        return -1;
      }
    } else {
      if (tire[p][1] != 0) {
        return Query(x ^ (one << i), m, tire[p][1], i - 1, true);
      } else if (tire[p][0] != 0) {
        return Query(x, m, tire[p][0], i - 1, true);
      } else {
        return -1;
      }
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
      min_val = min(min_val, v);
    }
    int n = queries.size();

    // printf("min_val=%d\n", min_val);

    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
      int x = queries[i][0];
      int m = queries[i][1];

      if (min_val <= m) {
        ans[i] = Query(x, m, 0, max_bit, false);
      }
    }

    return ans;
  }
};

int main() {
  //   TEST_SMP2(Solution, maximizeXor, vector<int>({3, 3, 7}),
  //             vector<int>({0, 1, 2, 3, 4}),
  //             vector<vector<int>>({{3, 1}, {1, 3}, {5, 6}}));

  //   TEST_SMP2(Solution, maximizeXor, vector<int>({12, -1, 5}),
  //             vector<int>({5, 2, 4, 6, 6, 3}),
  //             vector<vector<int>>({{12, 4}, {8, 1}, {6, 3}}));
  TEST_SMP2(Solution, maximizeXor, vector<int>({15}),
            vector<int>({5, 2, 4, 6, 6, 3}), vector<vector<int>>({{12, 4}}));

  return 0;
}
