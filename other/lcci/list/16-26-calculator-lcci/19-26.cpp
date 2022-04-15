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

typedef long long ll;
struct Node {
  char type;  // 0 + - * /
  ll val;
  bool IsFirst() { return type == '*' || type == '/'; }
};

class Solution {
  bool IsNum(char c) { return c >= '0' && c <= '9'; }
  ll ReadNum(string& s, int& pos) {
    int n = s.length();
    ll v = 0;
    while (pos < n && IsNum(s[pos])) {
      v = v * 10 + (s[pos] - '0');
      pos++;
    }
    return v;
  }

  void TryCal() {
    if (sta.size() < 3) return;

    ll b = sta.back().val;
    sta.pop_back();
    char op = sta.back().type;
    sta.pop_back();
    ll a = sta.back().val;
    sta.pop_back();

    ll c;

    switch (op) {
      case '+':
        c = a + b;
        break;
      case '-':
        c = a - b;
        break;
      case '*':
        c = a * b;
        break;
      case '/':
        c = a / b;
        break;
    }

    sta.push_back(Node{'0', c});
  }

  int Parse(string& s) {
    int n = s.length();
    int pos = 0;

    sta.push_back(Node{'0', 0});
    sta.push_back(Node{'+'});
    while (pos < n) {
      if (s[pos] == ' ') {
        pos++;
      } else if (IsNum(s[pos])) {
        ll v = ReadNum(s, pos);
        //   printf("read v = %lld\n", v);
        sta.push_back(Node{'0', v});
        if (sta.size() >= 3 && sta[sta.size() - 2].IsFirst()) {
          TryCal();
        }
      } else {
        if (s[pos] == '+' || s[pos] == '-') {
          TryCal();
        }
        //   printf("read op = %c\n", s[pos]);
        sta.push_back(Node{s[pos]});
        pos++;
      }
    }
    TryCal();
    return sta.back().val;
  }

  vector<Node> sta;

 public:
  int calculate(string& s) {  //
    return Parse(s);
  }
};

int main() {
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
