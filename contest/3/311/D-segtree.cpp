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

// 1.Build(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e3 + 10;
const int kMaxVal = 10e8;

int maxNM;

typedef long long ll;
struct SegTree {
  vector<ll> op; // 0 add, 1 set
  vector<ll> sign;
  vector<ll> sumVal;
  vector<ll> nums;
  vector<ll> str;

  void Init(int n) {
    n++;
    maxNM = n;
    sign.resize(maxNM << 2, 0);
    op.resize(maxNM << 2, 0);
    sumVal.resize(maxNM << 2, 0);
    nums.resize(maxNM << 2, 0);
    str.clear();
    str.resize(maxNM + 1, 0);
  }

  void PushUp(int rt) {
    sumVal[rt] = sumVal[rt << 1] + sumVal[rt << 1 | 1];
  }
  void PushDown(int rt) {
    if(op[rt] == 1){ // set
      op[rt << 1] = op[rt];
      op[rt << 1 | 1] = op[rt];

      sign[rt << 1] = sign[rt];
      sign[rt << 1 | 1] = sign[rt];

      sumVal[rt << 1] = sign[rt] * nums[rt << 1];
      sumVal[rt << 1 | 1] = sign[rt] * nums[rt << 1 | 1];

      sign[rt] = 0;
      op[rt] = 0;
    }else if(sign[rt]){ // add
      sign[rt << 1] += sign[rt];
      sign[rt << 1 | 1] += sign[rt];

      sumVal[rt << 1] += sign[rt] * nums[rt << 1];
      sumVal[rt << 1 | 1] += sign[rt] * nums[rt << 1 | 1];

      sign[rt] = 0;
    }
  }
  void Build(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    op[rt] = 0;
    nums[rt] = r - l + 1;
    if (l == r) {
      sumVal[rt] = str[l];
      return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(rt);
  }
  void UpdateAdd(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] += add;
      sumVal[rt] += add * nums[rt];
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) UpdateAdd(L, R, add, lson);
    if (R > m) UpdateAdd(L, R, add, rson);
    PushUp(rt);
  }
  void UpdateSet(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      op[rt] = 1;
      sign[rt] = add;
      sumVal[rt] = add * nums[rt];
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) UpdateSet(L, R, add, lson);
    if (R > m) UpdateSet(L, R, add, rson);
    PushUp(rt);
  }

  ll QuerySum(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      return sumVal[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += QuerySum(L, R, lson);
    }
    if (m < R) {
      ret += QuerySum(L, R, rson);
    }
    return ret;
  }
};

SegTree segTree;
class Solution {
 public:
  vector<int> sumPrefixScores(vector<string>& words) {
    map<string, pair<int, int>> m;
    for (auto& word : words) {
      if (m.count(word) == 0) {
        m[word] = {0, 0};
      }
      m[word].first++;
    }

    int MaxLen = 1010;
    segTree.Init(MaxLen);
    segTree.Build();

    string pre = "";
    for (auto& [k, v] : m) {
      int preLen = pre.length();
      int kLen = k.length();

      int commonLen = 0;
      for (int i = 0; i < min(kLen, preLen); i++) {
        if (pre[i] != k[i]) {
          break;
        }
        commonLen++;
      }
      printf("pre=%s k=%s commonLen=%d num=%d\n", pre.c_str(), k.c_str(), commonLen, v.first);

      segTree.UpdateSet(commonLen+1, MaxLen, 0);
      printf("after set\n");
      segTree.UpdateAdd(1, kLen, v.first);
      printf("after add\n");
      v.second = segTree.QuerySum(1, MaxLen);
      printf("after query\n");
      pre = k;
    }

    vector<int> ans;
    for (auto& word : words) {
      ans.push_back(m[word].second);
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
