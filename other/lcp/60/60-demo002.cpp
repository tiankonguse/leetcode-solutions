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
  Solution& self;
  int depth = 0, leaf = 0;
  vector<int> diff;  // 这一层最大的增量

  // 递归计算出树的高度，以及最后一层叶子的个数
  void DfsDepthLeaf(int level, TreeNode* root) {
    if (root == nullptr) return;
    DfsDepthLeaf(level + 1, root->left);
    DfsDepthLeaf(level + 1, root->right);
    if (level == self.depth) {
      self.leaf += 1;
    } else if (level > self.depth) {
      self.depth = level;
      self.leaf = 1;
    }
  }

  int len(vector<int>& levels) { return levels.size(); }

  // @return 最后一层叶子的个数
  // @param level_sum 当前子树的各个层和
  int get_level_sum(const int level, TreeNode* root, vector<int>& level_sum) {
    if (root == nullptr) return 0;
    vector<int> leftLevels, rightLevels;

    int leftLeafNum = get_level_sum(level + 1, root->left, leftLevels);
    int rightLeafNum = get_level_sum(level + 1, root->right, rightLevels);

    int m = 0;
    if (level == self.depth) {
      m = 1;
    } else {
      m = leftLeafNum + rightLeafNum;
    }

    int n = max(len(leftLevels), len(rightLevels));
    leftLevels.resize(n, 0);
    rightLevels.resize(n, 0);

    level_sum.push_back(root->val);
    for (int i = 0; i < n; i++) {
      level_sum.push_back(leftLevels[i] + rightLevels[i]);
    }

    if (root->left == nullptr || root->right == nullptr) {
      for (int i = 0; i < n; i++) {
        int k = level + i;
        self.diff[k] = max(self.diff[k], level_sum[i + 1] - level_sum[i]);
      }

      // 当前子树的最后一层特殊处理，上移后最后一层还存在，但是和更大
      if (level_sum.back() < 0 && m < self.leaf) {
        self.diff[level + n] = max(self.diff[level + n], -level_sum.back());
      }
    }

    return m;
  }

 public:
  Solution() : self(*this) {}

  int getMaxLayerSum(TreeNode* root) {
    DfsDepthLeaf(0, root);

    diff.resize(self.depth + 1, 0);

    vector<int> level_sums;
    get_level_sum(0, root, level_sums);

    int ans = root->val;
    for (int i = 0; i < level_sums.size() && i < self.diff.size(); i++) {
      ans = max(ans, self.diff[i] + level_sums[i]);
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
