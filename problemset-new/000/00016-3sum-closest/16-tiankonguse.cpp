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
  map<int, int> m;
  int ans;
  int dis;
  int target;

  void Check(int a, int b, int c) {
    if (c < b) {
      swap(c, b);
    }
    if (b < a) {
      swap(a, b);
    }
    // printf("a=%d b=%d c=%d\n", a, b, c);
    // a <= b <= c
    if (c < b) {
      return;
    }

    if (a == b && m[b] < 2) {
      return;
    }
    if (b == c && m[b] < 2) {
      return;
    }
    if (a == b && b == c && m[b] < 3) {
      return;
    }

    int tmp_ans = a + b + c;
    int tmp_dis = abs(tmp_ans - target);
    if (tmp_dis < dis) {
      dis = tmp_dis;
      ans = tmp_ans;
    }
  }

 public:
  int threeSumClosest(vector<int>& nums, int target_) {
    target = target_;

    for (auto v : nums) {
      m[v]++;
    }

    ans = nums[0] + nums[1] + nums[2];
    dis = abs(ans - target);

    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; ++i) {
      int a = nums[i];
      for (int j = i + 1; j < n; j++) {
        int b = nums[j];

        int c = target - a - b;
        auto it = m.lower_bound(c);  // 这个方法实际上有问题，找到的如果是
                                     // 自身，则可能需要去下一个寻找

        if (it != m.end()) {
          c = it->first;
          Check(a, b, c);
        }
        if (it != m.begin()) {
          it--;
          c = it->first;
          Check(a, b, c);
        }
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
