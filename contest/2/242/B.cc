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

const double PI = acos(-1.0), eps = 1e-7;
const int MAX_ANS = 1e7;
typedef long long ll;

class Solution {
  double CheckSpeed(vector<int>& dist, ll maxSpeed, double hour) {
    ll hourEx = (hour + eps) * 100;
    ll preTime = 0;

    for (int i = 0; i + 1 < dist.size(); i++) {
      auto v = dist[i];
      if (v % maxSpeed == 0) {
        preTime += v / maxSpeed;
      } else {
        preTime += v / maxSpeed + 1;
      }
    }

    if (preTime * 100 > hourEx) {
      return true;
    }

    ll leftTime = hourEx - preTime * 100;
    return dist.back() * 100 > leftTime * maxSpeed;
  }

 public:
  int minSpeedOnTime(vector<int>& dist, double hour) {
    if (CheckSpeed(dist, MAX_ANS, hour)) {
      return -1;
    }

    int left = 1, right = MAX_ANS;
    while (left < right) {
      int mid = (left + right) / 2;
      if (CheckSpeed(dist, mid, hour)) {  // 速度太小了，时间超过了
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return right;
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
