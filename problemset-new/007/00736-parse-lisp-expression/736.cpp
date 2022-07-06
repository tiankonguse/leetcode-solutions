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

typedef long long ll;
class Solution {
  string exp;
  int pos;
  int n;
  void SkipSpace() {
    while (exp[pos] == ' ') pos++;
  }
  string ReadName() {
    SkipSpace();
    string ans;
    while ((exp[pos] >= '0' && exp[pos] <= '9') ||
           (exp[pos] >= 'a' && exp[pos] <= 'z')) {
      ans.push_back(exp[pos]);
      pos++;
    }
    return ans;
  }
  ll ReadNum() {
    SkipSpace();
    ll sign = 1;
    if (exp[pos] == '-') {
      sign = -1;
      pos++;
    }

    ll ans = 0;
    while (exp[pos] >= '0' && exp[pos] <= '9') {
      ans = ans * 10 + (exp[pos] - '0');
      pos++;
    }
    return sign * ans;
  }

  ll ReadVal(map<string, std::shared_ptr<ll>> m) {
    ll ans = 0;
    SkipSpace();
    if (exp[pos] == '(') {
      ans = Dfs(m);
    } else if (exp[pos] >= 'a' && exp[pos] <= 'z') {
      string key = ReadName();
      ans = *m[key];
    } else {
      ans = ReadNum();
    }
    return ans;
  }

  ll Dfs(map<string, std::shared_ptr<ll>> m) {
    ll ans = 0;
    SkipSpace();

    pos++;  // skip (

    string op = ReadName();
    SkipSpace();
    // printf("dfs op=%s\n", op.c_str());

    if (op == "let") {  // let
      while (true) {
        SkipSpace();
        if (exp[pos] >= 'a' && exp[pos] <= 'z') {  // kv or ret Name
          string key = ReadName();
          //   printf("let key=%s\n", key.c_str());
          SkipSpace();
          if (exp[pos] == ')') {  // 返回 key
            ans = *m[key];
            // printf("let ret name=%s val=%lld\n", key.c_str(), ans);
            break;
          } else if (exp[pos] == '(') {  // kv exp
            ll val = Dfs(m);
            // printf("let add key=%s val=%lld\n", key.c_str(), val);
            m[key] = make_shared<ll>(val);
          } else if (exp[pos] >= 'a' && exp[pos] <= 'z') {  // kv name
            string name = ReadName();
            ll val = *m[name];
            // printf("let add key=%s val=%lld\n", key.c_str(), val);
            m[key] = make_shared<ll>(val);

          } else {  // kv 纯数字
            ll val = ReadNum();
            // printf("let add key=%s val=%lld\n", key.c_str(), val);
            m[key] = make_shared<ll>(val);
          }
        } else if (exp[pos] == '(') {  // ret Exp
          ans = Dfs(m);
          //   printf("let ret exp val=%lld\n", ans);
          break;
        } else {  // ret num
          ans = ReadNum();
          //   printf("let ret num val=%lld\n", ans);
          break;
        }
      }
    } else if (op == "add") {  // add
      ll a = ReadVal(m);
      ll b = ReadVal(m);
      ans = a + b;
      //   printf("add a=%lld b=%lld val=%lld\n", a, b, ans);
    } else if (op == "mult") {  // mul
      ll a = ReadVal(m);
      ll b = ReadVal(m);
      ans = a * b;
      //   printf("mul a=%lld b=%lld val=%lld\n", a, b, ans);
    } else {
    }

    pos++;  // skip )

    return ans;
  }

 public:
  int evaluate(string expression_) {
    map<string, std::shared_ptr<ll>> m;
    expression_.swap(exp);

    pos = 0;
    n = exp.size();
    return ReadVal(m);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
