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

typedef long long ll;

class FindSumPairs {
  vector<int> nums2;
  unordered_map<ll, int> m1;
  unordered_map<ll, int> m2;

 public:
  FindSumPairs(vector<int>& nums1, vector<int>& nums2_) {
    nums2.swap(nums2_);

    for (auto c : nums1) {
      m1[c]++;
    }

    for (auto c : nums2) {
      m2[c]++;
    }
  }

  void add(int index, int val) {
    // 删除
    ll pre = nums2[index];
    auto it = m2.find(pre);
    it->second--;
    if (it->second == 0) {
      m2.erase(it);
    }

    // 增加
    nums2[index] += val;
    ll after = nums2[index];
    m2[after]++;
  }

  int count(int tot) {
    ll num = 0;
    for (auto& p : m1) {
      ll val = tot - p.first;
      auto it = m2.find(val);
      if (it == m2.end()) {
        continue;
      }
      num += p.second * it->second;
    }
    return num;
  }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
