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

template <class T>
void chmin(T& a, T b) {
  a = min(a, b);
}
class Solution {
  int n;
  int check(int v, vector<int>& A, vector<int>& B) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (A[i] == v) continue;
      if (B[i] != v) return n;
      ans++;
    }
    return ans;
  }

 public:
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    n = A.size();
    int ans = n;
    chmin(ans, check(A.front(), A, B));
    chmin(ans, check(A.front(), B, A));
    chmin(ans, check(B.front(), A, B));
    chmin(ans, check(B.front(), B, A));

    return ans == n ? -1 : ans;
  }
};

int main() {
  int ans;
  vi A;
  vi B;

  ans = 2;
  A = {2, 1, 2, 4, 2, 2};
  B = {5, 2, 6, 2, 3, 2};
  TEST_SMP2(Solution, minDominoRotations, ans, A, B);

  ans = -1;
  A = {3, 5, 1, 2, 3};
  B = {3, 6, 3, 3, 4};
  TEST_SMP2(Solution, minDominoRotations, ans, A, B);

  return 0;
}
