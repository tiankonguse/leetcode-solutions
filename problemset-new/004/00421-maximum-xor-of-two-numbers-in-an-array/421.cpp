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

const int max3 = 2010, max4 = 20010, max5 = 700010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int next[2];
};
Node tries[max5];
class Trie {
  int index = 0;

  int Add() {
    int ret = index;
    Node& node = tries[ret];
    node.endFlag = false;
    memset(node.next, -1, sizeof(node.next));
    index++;
    return ret;
  }

 public:
  /** Initialize your data structure here. */
  void Init() {
    index = 0;
    Add();
  }

  /** Inserts a word into the trie. */
  void insert(const string& word) {
    int root = 0;
    for (auto c : word) {
      int v = c - '0';
      if (tries[root].next[v] == -1) {
        tries[root].next[v] = Add();
      }
      root = tries[root].next[v];
    }
    tries[root].endFlag = 1;
  }

  /** Returns if the word is in the trie. */
  int Solver(int l, int r, int preAns, int lev) {
    // printf("l=%d r=%d preAns=%d lev=%d\n", l, r, preAns, lev);
    bool diffBit = false;

    int ans = preAns;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (i == j) continue;
        if(tries[l].next[i] == -1) continue;
        if(tries[r].next[j] == -1) continue;
        diffBit = true;
        int tmp = Solver(tries[l].next[i], tries[r].next[j],
                         preAns | (1 << lev), lev - 1);
        ans = max(ans, tmp);
      }
    }

    if (!diffBit) {
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          if (i != j) continue;
        if(tries[l].next[i] == -1) continue;
        if(tries[r].next[j] == -1) continue;
          int tmp = Solver(tries[l].next[i], tries[r].next[j], preAns, lev - 1);
          ans = max(ans, tmp);
        }
      }
    }

    return ans;
  }
};
Trie trie;
class Solution {
  string ToString(int v) {
    string s;
    while (v) {
      s.push_back('0' + (v & 1));
      v /= 2;
    }
    s.resize(32, '0');
    std::reverse(s.begin(), s.end());
    return s;
  }

 public:
  int findMaximumXOR(vector<int>& nums) {
    trie.Init();
    for (auto v : nums) {
      trie.insert(ToString(v));
    }
    return trie.Solver(0, 0, 0, 31);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
