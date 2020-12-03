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

class Solution {
 public:
  bool isPossible(vector<int>& nums) {
    map<int, int> m;
    for (auto v : nums) {
      m[v]++;
    }
    int preVal = nums[0] - 2;
    int preLen[4] = {0, 0, 0, 0};
    for (auto p : m) {
      int val = p.first, num = p.second;

      if (preVal + 1 < val) {
        //不连续，前面的必须已经组成三个
        if (preLen[1] + preLen[2] > 0) {
          return false;
        } else {
          memset(preLen, 0, sizeof(preLen));
          preLen[1] = num;
        }
      } else if (preVal + 1 == val) {
        // 连续加1
        if (preLen[1] + preLen[2] > num) {
          // 不足连续三个
          return false;
        }
        if (preLen[1] + preLen[2] + preLen[3] < num) {
          //形成新的一个
          preLen[3] += preLen[2];
          preLen[2] = preLen[1];
          preLen[1] = num - (preLen[2] + preLen[3]);
        } else {
          // 可能部分 3 需要淘汰了
          int dis = preLen[1] + preLen[2] + preLen[3] - num;
          preLen[3] -= dis;
          preLen[3] += preLen[2];
          preLen[2] = preLen[1];
          preLen[1] = 0;
        }
      }
      //   printf("val:%d 1:%d 2:%d 3:%d\n", val, preLen[1], preLen[2],
      //   preLen[3]);
      preVal = val;
    }
    return preLen[1] + preLen[2] == 0;
  }
};

int main() {
  TEST_SMP1(Solution, isPossible, false, vector<int>({1}));
  TEST_SMP1(Solution, isPossible, true, vector<int>({1, 2, 3, 3, 4, 5}));
  TEST_SMP1(Solution, isPossible, true, vector<int>({1, 2, 3, 3, 4, 4, 5, 5}));
  TEST_SMP1(Solution, isPossible, false, vector<int>({1, 2, 3, 4, 4, 5}));
  TEST_SMP1(Solution, isPossible, true,
            vector<int>({1, 2, 3, 3, 4, 5, 8, 9, 10}));

  return 0;
}
