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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  typedef pair<long long, int> pli;
  vector<long long> sm;
  vector<int> sz;
  long long ans;

  int DfsH(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + max(DfsH(node->left), DfsH(node->right));
  }

  // 先计算每个点的深度，以及统计每一层原有的和
  void dfs1(TreeNode* node, int d) {
    if (node == nullptr) return;
    if (sm.size() <= d) sm.push_back(0), sz.push_back(0);
    sm[d] += node->val;
    sz[d]++;
    dfs1(node->left, d + 1);
    dfs1(node->right, d + 1);
  }

  struct Result {
    // mp[d].first 表示深度 d 的变化值，mp[d].second 表示深度 d 的节点变化数量
    unordered_map<int, pli> mp;
    // 哪些深度的答案有待计入答案
    unordered_set<int> pending;

    void swap(Result& r){
      mp.swap(r.mp);
      pending.swap(r.pending);
    }

    // 合并两个 Result，为了保证复杂度正确，mp.size() >= r.mp.size() 必须成立
    void merge(const Result& r) {
      for (const auto& [d, kv]: r.mp) {
        auto& p = mp[d];
        p.first += kv.first;
        p.second += kv.second;
        // 深度 it->first 的结果更新了，等待计入答案
        pending.insert(d);
      }
      for (int x : r.pending) pending.insert(x);
    }
  };

  void dfs2(TreeNode* node, int d, Result& ret) {
    if (node->left == nullptr && node->right == nullptr) {
      // 叶子节点
      if (sz[d] > 1) {
        // 删掉这个叶子节点不会掏空这一层，允许统计答案
        ans = max(ans, sm[d] - node->val);
        ret.mp[d] = pli(-node->val, -1);
      }
    } else if (node->left != nullptr && node->right != nullptr) {
      // 两个子节点
      Result a, b;
      dfs2(node->left, d + 1, a);
      dfs2(node->right, d + 1, b);
      if (a.mp.size() < b.mp.size()) a.swap(b);
      a.merge(b);

      // 自己这层的变化量也要算
      a.mp[d] = pli(node->left->val + node->right->val - node->val, 1);
      // 不能马上计算答案（因为这个点有两个子节点，不能删掉），先记下来
      a.pending.insert(d);

      ret.swap(a);
    } else {
      // 只有一个子节点
      TreeNode* ch = node->left == nullptr ? node->right : node->left;
      dfs2(ch, d + 1, ret);
      // 删掉这个子节点，开始统计所有受影响的层的答案
      for (int x : ret.pending) {
        pli p = ret.mp[x];
        // 深度 x 的变化不能导致深度 x 整层被掏空
        if (sz[x] + p.second > 0) ans = max(ans, sm[x] + p.first);
      }
      ret.pending.clear();

      // 自己这层的变化量也要算
      long long delta = ch->val - node->val;
      ans = max(ans, sm[d] + delta);
      ret.mp[d] = pli(delta, 0);
    }
  }

 public:
  int getMaxLayerSum(TreeNode* root) {
    int h = DfsH(root);
    sz.resize(h, 0);
    sm.resize(h, 0);
    dfs1(root, 0);
    ans = sm[0];
    for (long long x : sm) ans = max(ans, x);

    Result ret;
    dfs2(root, 0, ret);
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
