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

/*
题意: n 个字符串，每个字符串选择一些字母，最终选择的字母调整顺序后，可以组成
"helloleetcode" 选择代价：字符串中，左边字符个数 * 右边字符个数。
注意：选择后，字符串长度减一。
目标：问是否有答案，有的话输出最小代价。

字符串个数 n = [1, 24]
字符串长度 m = [1, 8]


思路：数位DP

mask: "helloleetcode" 长度为 13，开 1<<13 的空间。
dp(k, mask): 前 k 个字符串组成 mask 的最小代价。
答案： dp(n-1, (1<< 13) - 1).


状态转移：

for(int i = mask; i>=0; i=(i-1)&mask){ // 枚举第 k 个字符串的 mask 列表
  dp(k, mask) = min(dp(k, mask), dp(k-1, mask^i) + dpWord(k, i));
}
复杂度：O(n * 2^13 * 2^8)
字符串长度为 8， 合法字符串最多 2^8 个。


dpWord(k, i): 第 k 个字符串筛选出 i 的最优答案， 可以预处理得到。
预处理方法：预处理字符串字符，对有效字符的集合进行枚举，然后贪心计算出合法的
mask 列表以及答案。

贪心：左右依次寻找最近的。 好像有反例

*/

class Solution {
  // 长度 13， 7 个不同字符， 相同字符最多出现 4 次
  string base = "helloleetcode";
  int N;
  int MASK;
  map<char, int> charToIndex;
  int charNum;
  vector<int> baseStat;

  int n;
  vector<string> words;
  vector<vector<int>> wordsCost;
  vector<vector<int>> wordsMask;

  int H(vector<int>& stat) {
    int h = 0;
    for (int j = 0; j < charNum; j++) {
      int v = stat[j];
      h = (h << baseStat[j]) + (1 << v) - 1;
    }
    return h;
  }

  int HHH(int h) {
    if (h == 1) {
      return 1;
    } else if (h == 3) {
      return 2;
    } else if (h == 7) {
      return 3;
    } else if (h == 15) {
      return 4;
    } else {
      return 0;
    }
  }

  void HH(int h, vector<int>& stat) {
    for (int j = charNum - 1; j >= 0; j--) {
      stat[j] = HHH(h % (1 << baseStat[j]));
      h >>= baseStat[j];
    }
  }

  void TransChar(const vector<string>& words) {
    n = words.size();
    N = base.length();
    MASK = 1 << N;

    for (auto c : base) {
      charToIndex[c];
    }

    charNum = 0;
    for (auto& [k, v] : charToIndex) {
      v = charNum++;
    }

    baseStat.resize(charNum, 0);
    for (auto c : base) {
      baseStat[charToIndex[c]]++;
    }
  }

  void UpdateWord(const int i, vector<int>& stat, const int cost) {
    const int h = H(stat);
    wordsCost[i][h] = min(wordsCost[i][h], cost);
  }

  void DfsWord(const int i, const int l, const int r, const int leftLen,
               const int rightLen, const int cost, vector<int>& stat) {
    if (l > r) return;  //
    const string& s = words[i];

    const int len = r - l + 1;

    // 选择左边
    if (charToIndex.count(s[l])) {
      const int offset = charToIndex[s[l]];
      if (stat[offset] < baseStat[offset]) {
        stat[offset]++;
        const int newCost = cost + leftLen * (len - 1 + rightLen);
        UpdateWord(i, stat, newCost);
        DfsWord(i, l + 1, r, leftLen, rightLen, newCost, stat);
        stat[offset]--;
      }
    }

    // 跳过左边
    DfsWord(i, l + 1, r, leftLen + 1, rightLen, cost, stat);

    // 选择右边
    if (charToIndex.count(s[r])) {
      const int offset = charToIndex[s[r]];
      if (stat[offset] < baseStat[offset]) {
        stat[offset]++;
        const int newCost = cost + (leftLen + len - 1) * rightLen;
        UpdateWord(i, stat, newCost);
        DfsWord(i, l, r - 1, leftLen, rightLen, newCost, stat);
        stat[offset]--;
      }
    }

    // 跳过右边
    DfsWord(i, l, r - 1, leftLen, rightLen + 1, cost, stat);
  }

  int Solver() {
    vector<int> dp(MASK, INT_MAX);

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
      for (int maskPre = MASK - 1; maskPre >= 0; maskPre--) {
        if (dp[maskPre] == INT_MAX) continue;  // 无效集合
        vector<int> preStat(charNum, 0);
        HH(maskPre, preStat);
        for (auto mask : wordsMask[i]) {
          vector<int> stat(charNum, 0);
          HH(mask, stat);

          bool flag = 0;
          for (int k = 0; k < charNum; k++) {
            stat[k] += preStat[k];
            if (stat[k] > baseStat[k]) {
              flag = 1;
            }
          }

          if (flag) continue;

          int h = H(stat);
          dp[h] = min(dp[h], dp[maskPre] + wordsCost[i][mask]);
        }
      }
    }

    if (dp[MASK - 1] == INT_MAX) {
      dp[MASK - 1] = -1;
    }
    return dp[MASK - 1];
  }

 public:
  int Leetcode(vector<string>& words_) {
    words.swap(words_);

    TransChar(words);

    wordsMask.resize(n);
    wordsCost.resize(n, vector<int>(MASK, INT_MAX));
    for (int i = 0; i < n; i++) {
      const string& s = words[i];
      vector<int> stat(charNum, 0);
      DfsWord(i, 0, s.length() - 1, 0, 0, 0, stat);

      wordsMask[i].reserve(MASK);
      for (int mask = 1; mask < MASK; mask++) {
        if (wordsCost[i][mask] != INT_MAX) {
          wordsMask[i].push_back(mask);
        }
      }
    }

    return Solver();
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
