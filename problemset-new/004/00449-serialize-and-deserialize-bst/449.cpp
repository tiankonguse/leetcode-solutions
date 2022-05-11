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
void chmin(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = min(a, b);
  }
}
template <class T>
void chmax(T& a, T b) {
  if (a == -1) {
    a = b;
  } else {
    a = max(a, b);
  }
}

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-12;
ld PI = acos(-1.0);

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// LONG_MIN, LONG_MAX

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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
  void split(vector<string>& vec, string& data) {
    int prePos = 1;
    for (int i = 1; i < data.size(); i++) {
      if (data[i] == ',') {
        vec.push_back(data.substr(prePos, i - prePos));
        prePos = i + 1;
      }
    }
    vec.push_back(data.substr(prePos, data.size() - prePos - 1));
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    queue<TreeNode*> que;
    if (root) que.push(root);
    vector<string> vec;
    while (!que.empty()) {
      root = que.front();
      que.pop();
      if (root == NULL) {
        vec.push_back("null");
      } else {
        vec.push_back(to_string(root->val));
        que.push(root->left);
        que.push(root->right);
      }
    }

    int iEnd = vec.size() - 1;
    while (iEnd > 0 && vec[iEnd] == "null") {
      iEnd--;
    }

    string ans = "[";
    for (int i = 0; i <= iEnd; i++) {
      if (i) ans.push_back(',');
      ans.append(vec[i]);
    }
    ans.push_back(']');
    return ans;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.length() == 2) return NULL;
    vector<string> vec;
    split(vec, data);
    // for(int i=0;i<vec.size();i++){
    //     printf("%s\n", vec[i].c_str());
    // }

    TreeNode* root = new TreeNode(atoi(vec[0].c_str()));
    queue<TreeNode*> que;
    que.push(root);

    for (int i = 1; i < vec.size();) {
      TreeNode* pre = que.front();
      que.pop();
      if (!pre) continue;
      if (i < vec.size()) {
        if (vec[i] != "null") {
          pre->left = new TreeNode(atoi(vec[i].c_str()));
          que.push(pre->left);
        }
        i++;
      }
      if (i < vec.size()) {
        if (vec[i] != "null") {
          pre->right = new TreeNode(atoi(vec[i].c_str()));
          que.push(pre->right);
        }
        i++;
      }
    }

    // printf("data[%s] %s\n",data.c_str(), serialize(root).c_str());

    return root;
  }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
