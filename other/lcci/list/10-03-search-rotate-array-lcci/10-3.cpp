#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef __int128_t int128;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;

typedef long double ld;
typedef vector<ld> vld;

typedef vector<bool> vb;
typedef vector<string> vs;

// const int mod = 1e9 + 7;

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define rep1(i, n) for (ll i = 1; i <= (n); i++)
#define rrep(i, n) for (ll i = (n)-1; i >= 0; i--)
#define rrep1(i, n) for (ll i = (n); i >= 1; i--)
#define all(v) (v).begin(), (v).end()

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
void chmin(T& a, T b) {
  a = min(a, b);
}
template <class T>
void chmax(T& a, T b) {
  a = max(a, b);
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

/*
unordered_map / unordered_set

lower_bound 大于等于
upper_bound 大于
reserve 预先分配内存
reverse(all(vec)) 反转
sum = accumulate(a.begin(), a.end(), 0ll);
__builtin_popcount 一的个数
vector / array : upper_bound(all(vec), v)
map: m.upper_bound(v)

区间个数： std::distance(v.begin(), it)
map/set distance 复杂度 O(N)
vector/数组 distance 复杂度 O(1)



size_t found=str.find(string/char/char*);
std::string::npos

排序，小于是升序：[](auto&a, auto&b){ return a < b; })
优先队列 priority_queue<Node>：top/pop/push/empty
struct Node {
  Node(int t = 0) : t(t) {}
  int t;
  // 小于是最大堆，大于是最小堆
  bool operator<(const Node& that) const { return this->t < that.t; }
};
*/

class Solution {
 public:
  int search(vector<int>& arr, int target) {
    while (arr.size() > 1 && arr.front() == arr.back()) arr.pop_back();
    if (arr.front() == target) return 0;
    int n = arr.size();
    int l = 0, r = n;

    while (l < r) {  // [l, r)
      int mid = (l + r) / 2;
      if (arr[mid] == target) {
        r = mid;
      } else if (arr[mid] < arr.front()) {  // 456 123, 2
        if (target < arr[mid] || target >= arr.front()) {
          r = mid;
        } else {
          l = mid + 1;
        }
      } else {  // 456 123, 5
        if (arr[mid] < target || target <= arr.back()) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
    }

    if (r < n && arr[r] == target) {
      return r;
    }
    return -1;
  }
};

int main() {
  int ans;
  vi arr;
  int target;

  ans = 5;
  arr = {1, 1, 1, 1, 1, 2, 1, 1, 1};
  target = 2;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = 8;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 5;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = -1;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 11;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = 0;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 15;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = 11;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 14;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = 4;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 25;
  TEST_SMP2(Solution, search, ans, arr, target);

  ans = 5;
  arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  target = 1;
  TEST_SMP2(Solution, search, ans, arr, target);

  return 0;
}
