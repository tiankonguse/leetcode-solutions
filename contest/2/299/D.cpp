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
#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define sz(x) (int)(x).size()
#define SZ(A) int((A).size())
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define CTN(T, x) (T.find(x) != T.end())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir8[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                  {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

template <class T>
inline void RST(T& A) {
  memset(A, 0, sizeof(A));
}
template <class T>
inline void FLC(T& A, int x) {
  memset(A, x, sizeof(A));
}
template <class T>
inline void CLR(T& A) {
  A.clear();
}
template <class T>
T& chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
  return a;
}
template <class T>
T& chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
  return a;
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// LONG_MIN(10进制 10位), LONG_MAX(10进制 19位)

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

vector 去重
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

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

srand((unsigned)time(NULL));
rand();

mt19937 gen{random_device{}()};
uniform_real_distribution<double> dis(min, max);
function<double(void)> Rand = [that = this]() { return that->dis(that->gen); };

*/

class Solution {
  struct Edge {
    int u, v;
    int l, r;  //[l, r)
  };
  vector<vector<int>> g;
  vector<int> xors;
  vector<int> nums;
  vector<Edge> edgeRanges;
  int n;
  int ans = INT_MAX;
  int e;

  void updateAns(int a, int b, int c) {
    int maxVal = max(max(a, b), c);
    int minVal = min(min(a, b), c);
    ans = min(ans, maxVal - minVal);
  }

  int DfsVal(int r, int pre) {
    int val = nums[r];
    for (auto c : g[r]) {
        if(c == pre) continue;
      int edgeIndex = e++;
      val ^= DfsVal(c, r);
      Edge& edge = edgeRanges[edgeIndex];
      edge.u = r;
      edge.v = c;
      edge.l = edgeIndex;
      edge.r = e;
    }
    return xors[r] = val;
  }

  void Solver(int i, int j) {  // 删除第 I 和 第 J 条边
    Edge& ei = edgeRanges[i];
    Edge& ej = edgeRanges[j];

    if (i >= ej.l && i < ej.r) {  // 3、i 是 j 的子树
      int topXor = xors[0] ^ xors[ej.v];
      int midXor = xors[ej.v] ^ xors[ei.v];
      int downXor = xors[ei.v];
      updateAns(topXor, midXor, downXor);

    } else if (j >= ei.l && j < ei.r) {  // 2、j 是 i 的子树
      int topXor = xors[0] ^ xors[ei.v];
      int midXor = xors[ei.v] ^ xors[ej.v];
      int downXor = xors[ej.v];
      updateAns(topXor, midXor, downXor);
    } else {  // 1、 i 与 j 没关系
      int topXor = xors[0] ^ xors[ei.v] ^ xors[ej.v];
      int midXor = xors[ei.v];
      int downXor = xors[ej.v];

      updateAns(topXor, midXor, downXor);
    }
  }

 public:
  int minimumScore(vector<int>& nums_, vector<vector<int>>& edges) {
    nums.swap(nums_);
    n = nums.size();
    g.resize(n);
    xors.resize(n, 0);
    edgeRanges.resize(n-1);
    for (auto& v : edges) {
      int a = v[0], b = v[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }

    e = 0;
    DfsVal(0, -1);
    ans = INT_MAX;

    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n - 1; j++) {
        Solver(i, j);
      }
    }

    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
