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

class Solution {
  string s;
  const char* str;
  int n;
  const std::size_t END = std::string::npos;

  // CLOSE_TAG: <TAG_NAME>TAG_CONTENT</TAG_NAME>
  // TAG_NAME: [A-Z]{1,9}
  // TAG_CONTENT: (CLOSE_TAG|CDATA|[^<])*
  // CDATA: <![CDATA[CDATA_CONTENT]]>
  // CDATA_CONTENT: (!]]>)

  bool CheckTagName(const string& tagName) {
    int len = tagName.length();
    if (len == 0 || len > 9) return false;
    for (auto c : tagName) {
      if (c < 'A' || c > 'Z') {
        return false;
      }
    }
    return true;
  }

  const string cDataBegin = "<![CDATA[";
  const string cDataEnd = "]]>";
  bool ReadCdata(int& p) {
    // <![CDATA[
    if (p + cDataBegin.length() > n) return false;
    if (strncmp(str + p, cDataBegin.data(), cDataBegin.length()) != 0) {
      return false;
    }

    // printf("read cdata begin:[%d]\n", p);
    p += cDataBegin.length();

    std::size_t pos = s.find(cDataEnd, p);
    if (pos == END) return false;
    p = pos;

    p += cDataEnd.length();
    return true;
  }

  bool ReadTagContent(int& p) {
    while (p < n) {
      if (s[p] != '<') {
        p++;
        continue;
      }

      //   printf("read content <:[%d]\n", p);
      if (p + 1 == n) return false;

      if (s[p + 1] == '/') break;  // 当前的 tag content 读完了

      if (s[p + 1] == '!') {
        if (!ReadCdata(p)) return false;
        continue;
      }

      if (!ReadCloseTag(p)) return false;
    }
    return true;
  }

  bool Read(int& p, char c) {
    if (p == n || s[p] != c) return false;
    p++;  // skip c
    return true;
  }

  bool ReadCloseTag(int& p) {
    if (!Read(p, '<')) return false;

    std::size_t pos = s.find('>', p);
    if (pos == END) return false;
    const string tagName = s.substr(p, pos - p);
    const int tagLen = tagName.length();

    if (!CheckTagName(tagName)) return false;

    // printf("read tag begin: %s[%d]\n", tagName.c_str(), p);

    p = pos;  // skip name

    if (!Read(p, '>')) return false;

    if (!ReadTagContent(p)) return false;

    if (p + 3 + tagLen > n) return false;

    if (!Read(p, '<')) return false;
    if (!Read(p, '/')) return false;

    if (strncmp(str + p, tagName.data(), tagLen) != 0) {
      return false;
    }
    // printf("read tag end: %s[%d]\n", tagName.c_str(), p);
    p += tagLen;  // skip tagName

    if (!Read(p, '>')) return false;

    return true;
  }

 public:
  bool isValid(string& code_) {
    s.swap(code_);
    str = s.data();
    n = s.length();
    int p = 0;
    if (!ReadCloseTag(p)) return false;
    return p == n;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
