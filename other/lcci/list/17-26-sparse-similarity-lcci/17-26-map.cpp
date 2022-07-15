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
  vector<string> ans;

  vector<int> sortFlag;
  int Solver(int i, int j, vector<int>& a, vector<int>& b) {
    if (sortFlag[i] == 0) {
      sort(a.begin(), a.end());
      sortFlag[i] = 1;
    }
    if (sortFlag[j] == 0) {
      sort(b.begin(), b.end());
      sortFlag[j] = 1;
    }

    int an = a.size();
    int bn = b.size();

    int len = 0;
    int ai = 0, bi = 0;
    while (ai < an && bi < bn) {
      if (a[ai] < b[bi]) {
        ai++;
      } else if (a[ai] > b[bi]) {
        bi++;
      } else {
        len++;
        ai++;
        bi++;
      }
    }
    return len;
  }

  const int N = 10000;
  void AddAns(int i, int j, int a, int b) {
    int c = (a * N * 10 / b + 5) / 10;
    if (c == 0) return;

    char buf[20];
    snprintf(buf, sizeof(buf), "%d,%d: %d.%04d", i, j, c / N, c % N);
    ans.push_back(buf);
  }

 public:
  vector<string> computeSimilarities(vector<vector<int>>& docs) {
    int n = docs.size();
    sortFlag.resize(n, 1);
    unordered_map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
      auto& doc = docs[i];
      sort(doc.begin(), doc.end());
      for (auto v : doc) {
        m[v].push_back(i);
      }
    }

    vector<int> flag;
    for (int i = 0; i < n; i++) {
      if (docs[i].size() == 0) continue;
      flag.clear();
      flag.resize(n, 0);
      flag[i] = 1;
      for (auto v : docs[i]) {
        for (auto j : m[v]) {
          if (flag[j]) continue;
          if (j <= i) continue;
          flag[j] = 1;
          int len = Solver(i, j, docs[i], docs[j]);
          if (len > 0) {
            AddAns(i, j, len, docs[i].size() + docs[j].size() - len);
          }
        }
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