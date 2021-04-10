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
// reserve vector预先分配内存
// reverse(v.begin(), v.end()) 反转
// sum = accumulate(a.begin(), a.end(), 0);

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

typedef long long ll;

class Solution {
  struct Info {
    int index;
    int pre_val;
    int num;
  };
  unordered_map<ll, int> m;
  unordered_map<int, Info> tile_info;

  int FixVal(int val, int use) {
    auto it = tile_info.find(val);
    if (it == tile_info.end()) return 0;
    if (it->second.num > use) {
      return it->second.num - use;
    } else {
      return 0;
    }
  }

  int FindNextUse(int val, int use1, int use2, int use3) {
    int ans = FixVal(val, use1);
    if (ans == 0) return 0;

    int ans2 = FixVal(val - 1, use2);
    ans = min(ans, ans2);
    if (ans == 0) return 0;

    int ans3 = FixVal(val - 2, use3);
    ans = min(ans, ans3);
    if (ans == 0) return 0;

    return ans;
  }

  const ll base = 100000;
  ll hash(ll val, ll use1, ll use2) {
    return (tile_info[val].index * base + use1) * base + use2;
  }

  int dfs(const int val, const int use1, const int use2) {
    if (tile_info.count(val) == 0) return 0;

    auto p = hash(val, use1, use2);
    if (m.count(p)) {
      return m[p];
    }

    // printf("dfs: val=%d use1=%d use2=%d\n", val, use1, use2);
    int ans = 0;

    int maxNextUse = FindNextUse(val, use1, use2, 0);
    // printf("dfs: val=%d use1=%d use2=%d maxNextUse=%d\n", val, use1, use2,
    // maxNextUse); 不组成顺子
    int tmpAns = (tile_info[val].num - use1) / 3;
    int nextVal = tile_info[val].pre_val;
    if (nextVal + 1 == val) {
      tmpAns += dfs(nextVal, use2, 0);
    } else {
      tmpAns += dfs(nextVal, 0, 0);
    }
    ans = max(ans, tmpAns);
    // printf("dfs: val=%d use1=%d use2=%d no select, ans=%d\n", val, use1,
    // use2, ans);

    for (int i = 0; i <= min(maxNextUse, 3); i++) {
      // 确定可以组成 i 个顺子
      int tmpAns = i + (tile_info[val].num - use1 - i) / 3;
      tmpAns += dfs(val - 1, use2 + i, i);
      ans = max(ans, tmpAns);
    }

    // printf("dfs: val=%d use1=%d use2=%d ans=%d\n", val, use1, use2, ans);
    return m[p] = ans;
  }

 public:
  int maxGroupNumber(vector<int>& tiles) {
    sort(tiles.begin(), tiles.end());

    int index = 0, preVal = -1;
    for (auto& val : tiles) {
      // printf("val=%d index=%d preVal=%d num=%d\n", p.first, index, preVal,
      // p.second);
      if (val == preVal) {
        tile_info[val].num++;
      } else {
        tile_info[val] = Info{index, preVal, 1};
        index++;
        preVal = val;
      }
    }

    return dfs(preVal, 0, 0);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
