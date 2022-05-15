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
  map<string, int> m;
  vector<string> strs;
  int n;
  const int K = 32769;

  vector<vector<int>> dp;

  map<string, int> h;
  vector<string> H;

  // 判断 a 是否包含 b（已经去重）
  bool IsIncluded(string& a, string& b) {
    if (a.length() <= b.length()) return false;

    int i = 0, j = 0;
    while (i < a.length() && j < b.length()) {
      if (a[i] == b[i]) {
        i++;
        j++;
      } else if (a[i] < b[j]) {
        i++;
      } else {
        return false;
      }
    }
    return j == b.length();
  }

  bool IsIncluded(int i) {
    for (int j = 0; j < strs.size(); j++) {
      if (j == i) continue;
      if (IsIncluded(strs[j], strs[i])) {
        return true;
      }
    }
    return false;
  }

  void Init(vector<string>& stickers, string& target) {
    map<char, int> base;
    for (auto c : target) base[c]++;

    // 删除不相关的字符，去重
    for (auto& s : stickers) {
      map<char, int> tmp;
      for (auto c : s) {
        if (base.count(c)) {
          if (tmp[c] < base[c]) {
            tmp[c]++;
          }
        }
      }

      s.clear();
      int repeatNum = 1;
      for (auto [c, num] : tmp) {
        s.resize(s.length() + num, c);
        repeatNum = max(repeatNum, (base[c] + num - 1) / num);
      }
      if (s.length() == 0) continue;
      if (m.count(s) == 0) {
        m[s] = repeatNum;
        strs.push_back(s);
      }
    }

    // 删除子集
    for (int i = 0; i < strs.size(); i++) {
      if (IsIncluded(i)) {  //
        m.erase(strs[i]);
      }
    }

    if (strs.size() != m.size()) {
      strs.clear();
      for (auto& [s, num] : m) {
        strs.push_back(s);
      }
    }

    h[""] = H.size();
    H.push_back("");
  }

  int Hash(map<char, int>& base) {
    string s;
    for (auto [c, num] : base) {
      if (num <= 0) continue;
      s.resize(s.length() + num, c);
    }

    if (h.count(s) == 0) {
      h[s] = H.size();
      H.push_back(s);
    }
    return h[s];
  }
  int Dfs(int p, map<char, int>& base) {
    int k = Hash(base);
    if (p < 0) {
      if (k == 0) {
        return 0;
      } else {
        return -1;  // 无解
      }
    }
    int& ret = dp[p][k];
    if (ret != -2) return ret;

    ret = Dfs(p - 1, base);  // 默认不选择

    string& s = strs[p];
    bool flag = true;
    int num = 0;
    while (flag) {
      flag = false;
      for (auto c : s) {
        if (base[c] > 0) {
          flag = true;
          break;
        }
      }

      if (!flag) continue;

      num++;  // 选择一次
      for (auto c : s) {
        base[c]--;
      }

      int tmp = Dfs(p - 1, base);
      if (tmp >= 0) {  // 有答案
        tmp += num;
        if (ret < 0) {
          ret = tmp;
        } else {
          ret = min(ret, tmp);
        }
      }
    }

    // 恢复
    while (num--) {
      for (auto c : s) {
        base[c]++;
      }
    }

    return ret;
  }

 public:
  int minStickers(vector<string>& stickers, string& target) {
    sort(target.begin(), target.end());
    Init(stickers, target);

    n = strs.size();
    if (n == 0) return -1;

    dp.resize(n, vector<int>(K, -2));

    map<char, int> base;
    for (auto c : target) base[c]++;
    return Dfs(n - 1, base);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
