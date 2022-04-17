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

// 1.bulid(); 2.query(a,b) 3.update(a,b)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 1e5 + 10;
const int kMaxVal = 10e8;

int maxNM;

struct SegTree {
  vector<ll> sign;
  vector<ll> sum;
  vector<ll> nums;

  void Init(int n) {
    maxNM = n;
    sign.clear();
    sign.resize(maxNM << 2, 0);
    sum.clear();
    sum.resize(maxNM << 2, 0);
    nums.clear();
    nums.resize(maxNM << 2);
  }

  void PushUp(int rt) {  //
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
  }
  void PushDown(int rt) {
    if (sign[rt]) {
      sign[rt << 1] = sign[rt];
      sign[rt << 1 | 1] = sign[rt];

      if (sign[rt] == -1) {
        sum[rt << 1] = 0;
        sum[rt << 1 | 1] = 0;
      } else {
        sum[rt << 1] = nums[rt << 1];
        sum[rt << 1 | 1] = nums[rt << 1 | 1];
      }

      sign[rt] = 0;
    }
  }
  void Bulid(int l = 1, int r = maxNM, int rt = 1) {
    sign[rt] = 0;
    nums[rt] = r - l + 1;
    // printf("build: rt=%d l=%d r=%d num=%lld\n", rt, l, r, nums[rt]);
    if (l == r) {
      sum[rt] = 0;
      return;
    }
    int m = (l + r) >> 1;
    Bulid(lson);
    Bulid(rson);
    PushUp(rt);
  }
  void Update(int L, int R, int add, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      sign[rt] = add;
      if (add == -1) {
        sum[rt] = 0;
      } else {
        sum[rt] = nums[rt];
      }
      // printf("update: rt=%d l=%d r=%d num=%lld\n", rt, l, r, sum[rt]);
      return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) Update(L, R, add, lson);
    if (R > m) Update(L, R, add, rson);
    PushUp(rt);
  }
  ll Query(int L, int R, int l = 1, int r = maxNM, int rt = 1) {
    if (L <= l && r <= R) {
      // printf("query: rt=%d l=%d r=%d num=%lld\n", rt, l, r, sum[rt]);
      return sum[rt];
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) {
      ret += Query(L, R, lson);
    }
    if (m < R) {
      ret += Query(L, R, rson);
    }
    return ret;
  }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

unordered_map<ll, ll> h;
vector<ll> nums;
SegTree segTree;

class Solution {
  void Init() {
    h.clear();
    nums.clear();
    nums.reserve(10e5 + 1);
  }
  void Dfs(TreeNode* root) {
    if (root == nullptr) return;
    nums.push_back(root->val);
    Dfs(root->left);
    Dfs(root->right);
  }

  int n;

 public:
  int getNumber(TreeNode* root, vector<vector<int>>& ops) {
    Init();
    Dfs(root);
    sort(nums.begin(), nums.end());
    n = nums.size();

    for (int i = 1; i <= n; i++) {
      h[nums[i - 1]] = i;
    }
    segTree.Init(n);
    segTree.Bulid();
    for (auto& op : ops) {
      int type = op[0];
      int x = h[op[1]];
      int y = h[op[2]];
      if (type == 0) {
        type = -1;
      }
      // printf("type=%d x=%d y=%d\n", type, x, y);
      segTree.Update(x, y, type);
      // printf("now ans=%lld\n", segTree.Query(1, n));
    }
    return segTree.Query(1, n);
  }
};

// int main() {
//   //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
//   //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
//   //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

//   return 0;
// }
