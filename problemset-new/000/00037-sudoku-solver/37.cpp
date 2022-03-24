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

class Solution {
  int num = 0;
  vector<vector<char>> board;
  vll bits;
  vvll head;
  vll count;
  void Init() {
    head.resize(9, vll(10, -1));
    count.resize(10, 0);
    count[9] = 10;
    rep(i, 9) {
      ll pre = 0;
      rep(j, 9) {
        char c = board[i][j];
        if (c == '.') {
          head[i][pre] = j + 1;
          count[i]++;
          pre = j + 1;
          num++;
        }
      }
    }

    bits.resize(27);

    rep(i, 9) {
      ll& mask = bits[i];
      rep(j, 9) {
        char c = board[i][j];
        if (c == '.') continue;
        mask |= 1 << (c - '0');
      }
    }

    rep(j, 9) {
      ll& mask = bits[9 + j];
      rep(i, 9) {
        char c = board[i][j];
        if (c == '.') continue;
        mask |= 1 << (c - '0');
      }
    }

    rep(i, 3) {
      rep(j, 3) {
        ll& mask = bits[18 + i * 3 + j];
        rep(x, 3) {
          rep(y, 3) {
            char c = board[i * 3 + x][j * 3 + y];
            if (c == '.') continue;
            mask |= 1 << (c - '0');
          }
        }
      }
    }
  }

  bool Dfs() {
    if (num == 0) {
      return true;
    }

    int i = 9;
    rep(x, 9) {
      if (count[x] == 0) continue;
      if (count[x] < count[i]) {
        i = x;
      }
    }

    int pre = head[i][0];
    if (pre == -1) return false;
    head[i][0] = head[i][pre];
    count[i]--;

    int j = pre - 1;
    rep1(v, 9) {  //
      ll& a = bits[i];
      ll& b = bits[9 + j];
      ll& c = bits[18 + i / 3 * 3 + j / 3];
      if (a & (1 << v)) continue;
      if (b & (1 << v)) continue;
      if (c & (1 << v)) continue;

      board[i][j] = v + '0';
      a ^= (1 << v);
      b ^= (1 << v);
      c ^= (1 << v);
      num--;
      if (Dfs()) {
        return true;
      }
      num++;
      a ^= (1 << v);
      b ^= (1 << v);
      c ^= (1 << v);
      board[i][j] = '.';
    }

    count[i]++;
    head[i][0] = pre;

    return false;
  }

 public:
  void solveSudoku(vector<vector<char>>& board_) {
    board.swap(board_);
    Init();
    Dfs();
    board.swap(board_);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
