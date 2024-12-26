#include "base.h"

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
#define rrep1(i, n) for (ll i = (n); i >= 0; i--)
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

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

struct SegInfo {
  pair<char, ll> r, l;
  ll kNum;  // build 之后不再变化
  ll maxNum;
};

struct SegTree {
  SegInfo infos[maxn << 2];
  string s;

  void PushUp(int rt) {
    SegInfo& P = infos[rt];
    SegInfo& L = infos[rt << 1];
    SegInfo& R = infos[rt << 1 | 1];

    if (L.r.first == R.l.first) {
      pair<char, ll> mid = {L.r.first, L.r.second + R.l.second}; //中间连接起来

      P.l = L.l;
      P.r = R.r;
      P.maxNum = max(L.maxNum, R.maxNum);
      chmax(P.maxNum, mid.second);
      if (mid.second == L.kNum + R.kNum) {  // 完整覆盖
        P.l = P.r = mid;
      } else if (L.kNum == L.maxNum) {  // 左侧完整覆盖
        P.l = mid;
      } else if (R.kNum == R.maxNum) {  // 右侧完整覆盖
        P.r = mid;
      } else {
        // do nothing
      }
    } else {
      P.l = L.l;
      P.r = R.r;
      P.maxNum = max(L.maxNum, R.maxNum);
    }
  }

  void Build(int l = 1, int r = maxNM, int rt = 1) {
    SegInfo& info = infos[rt];
    info.kNum = r - l + 1;
    if (l == r) {
      info.l = info.r = {s[l - 1], 1};
      info.maxNum = 1;
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void Update(int L, int R, char add, int l = 1, int r = maxNM, int rt = 1) {
    SegInfo& info = infos[rt];
    if (L <= l && r <= R) {
      info.l = info.r = {add, R - L + 1};
      info.maxNum = R - L + 1;
      return;
    }
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
  }
  ll Query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    SegInfo& info = infos[rt];
    return info.maxNum;
  }
};

SegTree segTree;

class Solution {
 public:
  vector<int> longestRepeating(string& s, string& ss, vector<int>& nums) {
    // 线段树做更简单些
    ll n = s.size();
    ll m = ss.length();
    maxNM = n;
    segTree.s = move(s);
    segTree.Build();

    vi ans(nums.size(), 1);

    rep(i, m) {
      char c = ss[i];
      int j = nums[i];
      segTree.Update(j + 1, j + 1, c);
      ans[i] = segTree.Query(1, n);
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
