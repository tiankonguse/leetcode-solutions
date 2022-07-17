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

typedef long long ll;
class Solution {
  struct Node {
    vector<pair<ll, ll>> levelSumCount;  // 子树各层的和, 子树各层的节点个数
    int rootLevel = 0;                   //子树的根在root树中的 Level
    int maxLevel = 0;    // 子树的最底层叶子在 root 树中的 Level
    int cacheLevel = 0;  // 最大的未计算的 level
    void Init(int h) { levelSumCount.resize(h + 1, {0, 0}); }

    void Swap(Node& o) {
      swap(rootLevel, o.rootLevel);
      swap(maxLevel, o.maxLevel);
      swap(cacheLevel, o.cacheLevel);
      levelSumCount.swap(o.levelSumCount);
    }

  } base, node;
  int h, leafCount;
  ll ans = 0;
  int DfsHeight(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(DfsHeight(root->left), DfsHeight(root->right));
  }

  void DfsBase(TreeNode* root, int lev) {
    if (root == nullptr) return;
    base.levelSumCount[lev].first += root->val;
    base.levelSumCount[lev].second++;

    DfsBase(root->left, lev + 1);
    DfsBase(root->right, lev + 1);
  }

  void Dfs(TreeNode* root, const int lev, Node& node) {
    if (root->left != nullptr && root->right != nullptr) {
      Node first, second;
      Dfs(root->left, lev + 1, first);
      Dfs(root->right, lev + 1, second);

      if (first.maxLevel < second.maxLevel) {
        first.Swap(second);
      }

      // 轻边合并到重边
      first.cacheLevel = max(first.cacheLevel, second.maxLevel);
      int p1 = first.levelSumCount.size() - 1;
      int p2 = second.levelSumCount.size() - 1;
      for (int i = second.rootLevel; i <= second.maxLevel; i++, p1--, p2--) {
        first.levelSumCount[p1].first += second.levelSumCount[p2].first;
        first.levelSumCount[p1].second += second.levelSumCount[p2].second;
      }

      first.rootLevel = lev;
      first.levelSumCount.push_back({root->val, 1});

      node.Swap(first);
    } else if (root->left == nullptr && root->right == nullptr) {
      Node first;
      first.maxLevel = lev;
      first.cacheLevel = lev;
      first.rootLevel = lev;
      first.levelSumCount.push_back({root->val, 1});

      if (lev != h || 1 != leafCount) {
        ans = max(ans, base.levelSumCount[lev].first - root->val);
      }

      node.Swap(first);
    } else {
      Node first;
      if (root->left) {
        Dfs(root->left, lev + 1, first);
      } else {
        Dfs(root->right, lev + 1, first);
      }

      first.rootLevel = lev;
      first.levelSumCount.push_back({root->val, 1});

      printf("lev=%d val=%d\n", lev, root->val);
      // 删除 root, 尝试更新答案
      int i = first.levelSumCount.size() - 1;
      i -= first.cacheLevel - first.rootLevel;

      while (first.cacheLevel >= first.rootLevel) {
        auto& [sumi, counti] = first.levelSumCount[i];

        ll sum = base.levelSumCount[first.cacheLevel].first;
        if (first.cacheLevel == first.maxLevel) {  // 最底层，存在边界问题
          if (first.cacheLevel != h || counti != leafCount) {
            ans = max(ans, sum - sumi);
          }
        } else {
          ans = max(ans, sum - sumi + first.levelSumCount[i - 1].first);
        }
        first.cacheLevel--;
        i++;
      }
      first.cacheLevel = first.rootLevel;

      node.Swap(first);
    }
  }

 public:
  int getMaxLayerSum(TreeNode* root) {
    h = DfsHeight(root) - 1;
    printf("h=%d\n", h);

    base.Init(h);
    ans = root->val;
    DfsBase(root, 0);
    leafCount = base.levelSumCount[h].second;

    for (auto [sum, count] : base.levelSumCount) {
      ans = max(ans, sum);
    }

    Dfs(root, 0, node);

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
