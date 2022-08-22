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

typedef long long ll;
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;

  ll t = x % y;
  while (t) {
    x = y;
    y = t;
    t = x % y;
  }
  return y;
}

typedef pair<int, int> Node;

bool Zero(const Node& l) { return l.first == 0; }
Node Sample(int A, int B) {
  if (A == 0) {
    return Node{0, 1};
  }

  if (B < 0) {
    A = -A;
    B = -B;
  }

  int sign = 1;
  if (A < 0) {
    sign = -1;
    A = -A;
  }

  int G = Gcd(A, B);
  A = A / G;
  B = B / G;
  return Node{sign * A, B};
}

Node operator+(const Node& l, const Node& r) {
  int A = l.first * r.second + r.first * l.second;
  int B = l.second * r.second;
  return Sample(A, B);
}

Node operator-(const Node& l, const Node& r) {
  int A = l.first * r.second - r.first * l.second;
  int B = l.second * r.second;
  return Sample(A, B);
}

Node operator*(const Node& l, const Node& r) {
  int A = l.first * r.first;
  int B = l.second * r.second;
  return Sample(A, B);
}

Node operator/(const Node& l, const Node& r) {
  int A = l.first * r.second;
  int B = l.second * r.first;
  return Sample(A, B);
}

class Solution {
  const int n = 4;
  const Node v24{24, 1};
  vector<int> cards, cardsEx;

  set<Node> dp[4][4];

  const set<Node>& Dfs(int l, int r) {
    auto& ret = dp[l][r];

    if (ret.size() > 0) return ret;
    if (l == r) {
      ret.insert(Node{cards[l], 1});
      return ret;
    }

    for (int mid = l + 1; mid <= r; mid++) {
      auto& LS = Dfs(l, mid - 1);
      auto& RS = Dfs(mid, r);

      for (const Node& ls : LS) {
        for (const Node& rs : RS) {
          ret.insert(ls + rs);
          ret.insert(ls - rs);
          ret.insert(ls * rs);
          if (!Zero(rs)) {
            ret.insert(ls / rs);
          }
        }
      }
    }

    if (l == 0 && r == 1 || l == 2 && r == 3) {
      for (auto& node : ret) {
        printf("l=%d r=%d a=%d b=%d\n", l, r, node.first, node.second);
      }
    }

    return ret;
  }

  bool Check() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        dp[i][j].clear();
      }
    }

    Dfs(0, 3);
    for (auto& node : dp[0][3]) {
      if (node == v24) {
        return true;
      }
    }

    return false;
  }

  bool DfsEx(int pos) {
    if (pos == n) {
      return Check();
    }

    for (int i = 0; i < n; i++) {
      if (cardsEx[i] == 0) continue;
      int v = cardsEx[i];
      cardsEx[i] = 0;

      cards.push_back(v);
      if (DfsEx(pos + 1)) {
        return true;
      }
      cards.pop_back();
      cardsEx[i] = v;
    }
    return false;
  }

 public:
  bool judgePoint24(vector<int>& cards_) {
    cardsEx.swap(cards_);
    return DfsEx(0);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
