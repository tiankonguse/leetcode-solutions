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
struct Node {
  ll val;
  vector<string> vec;  // *
  bool operator<(const Node& o) {
    if (vec.size() == o.vec.size()) {
      return vec < o.vec;
    } else {
      return vec.size() > o.vec.size();
    }
  }
  bool operator==(const Node& o) { return vec == o.vec; }
  string ToString() {
    string ret;
    ret.append(to_string(val));
    for (auto& s : vec) {
      ret.push_back('*');
      ret.append(s);
    }
    return ret;
  }
};
struct Exp {
  vector<Node> vec;  // +
};
class Solution {
  map<string, int> names;
  string expression;
  int n;
  int pos = 0;

  Exp Smp(Exp& exp) {
    sort(exp.vec.begin(), exp.vec.end());
    Exp ret;

    for (auto& node : exp.vec) {
      if (node.val == 0) continue;
      if (ret.vec.empty()) {
        ret.vec.push_back(node);
      } else if (ret.vec.back() == node) {
        ret.vec.back().val += node.val;
        if (ret.vec.back().val == 0) {
          ret.vec.pop_back();
        }
      } else {
        ret.vec.push_back(node);
      }
    }

    return ret;
  }

  Exp Add(Exp& a, Exp& b) {
    Exp ret = a;
    for (auto& node : b.vec) {
      ret.vec.push_back(node);
    }
    return Smp(ret);
  }
  Exp Sub(Exp& a, Exp& b) {
    Exp ret = a;
    for (auto& node : b.vec) {
      ret.vec.push_back(node);
      ret.vec.back().val *= -1;
    }
    return Smp(ret);
  }
  Exp Mul(Exp& a, Exp& b) {
    Exp ret;
    for (auto& nodea : a.vec) {
      for (auto& nodeb : b.vec) {
        Node tmp;
        tmp.val = nodea.val * nodeb.val;
        for (auto& s : nodea.vec) tmp.vec.push_back(s);
        for (auto& s : nodeb.vec) tmp.vec.push_back(s);
        sort(tmp.vec.begin(), tmp.vec.end());
        ret.vec.push_back(tmp);
      }
    }
    return Smp(ret);
  }

  void BuildNum(int val, Exp& exp) {
    Node node;
    node.val = val;
    exp.vec.push_back(node);
  }
  void Buildname(const string& name, Exp& exp) {
    Node node;
    node.val = 1;
    node.vec.push_back(name);

    exp.vec.push_back(node);
  }

  void readNum(Exp& exp) {
    int val = 0;
    while (pos < n && expression[pos] >= '0' && expression[pos] <= '9') {
      val = val * 10 + (expression[pos] - '0');
      pos++;
    }
    BuildNum(val, exp);
  }

  void readName(Exp& exp) {
    string name;
    while (pos < n && expression[pos] >= 'a' && expression[pos] <= 'z') {
      name.push_back(expression[pos]);
      pos++;
    }
    if (names.count(name)) {
      BuildNum(names[name], exp);
    } else {
      Buildname(name, exp);
    }
  }

  enum { EXP = 0, NODE = 1, UNIT = 2 };

  // 0:Exp, 1:Node(unit * unit)  2: unit
  void readExpression(Exp& exp, int lev = EXP) {
    int tmpPos = pos;

    while (pos < n) {
      char c = expression[pos];
      if (c == ' ') {
        pos++;  // skip ' '
        continue;
      } else if (c == '+') {
        if (lev == UNIT || lev == NODE) break;
        pos++;  // skip '+'
        Exp tmp;
        readExpression(tmp, NODE);
        exp = Add(exp, tmp);
      } else if (c == '-') {
        if (lev == UNIT || lev == NODE) break;
        pos++;  // skip '-'
        Exp tmp;
        readExpression(tmp, NODE);
        exp = Sub(exp, tmp);
      } else if (c == '*') {
        if (lev == UNIT) break;
        pos++;  // skip '*'
        Exp tmp;
        readExpression(tmp, UNIT);
        exp = Mul(exp, tmp);
      } else if (c == '(') {
        pos++;  // skip '('
        readExpression(exp);
        pos++;  // skip ')'
      } else if (c == ')') {
        break;  // 括号
      } else if (c >= '0' && c <= '9') {
        readNum(exp);
      } else {
        readName(exp);
      }
    }

    // printf("pos=%d ", tmpPos);
    // for (auto& node : exp.vec) {
    //   printf("\t %s \n", node.ToString().c_str());
    // }
  }

 public:
  vector<string> basicCalculatorIV(string expression_, vector<string>& evalvars,
                                   vector<int>& evalints) {
    expression.swap(expression_);
    n = expression.size();
    pos = 0;
    for (int i = 0; i < evalvars.size(); i++) {
      names[evalvars[i]] = evalints[i];
    }

    Exp exp;
    readExpression(exp);

    vector<string> ans;
    for (auto& node : exp.vec) {
      ans.push_back(node.ToString());
    }
    if (ans.size() == 1 && ans.back() == "0") {
      ans.clear();
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
