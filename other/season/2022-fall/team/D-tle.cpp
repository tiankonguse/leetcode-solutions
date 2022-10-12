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

int dp[24][8192];  // -2 代表未计算， -1 代表无解

class Solution {
  // 长度 13， 7 个不同字符， 相同字符最多出现 4 次
  string base = "helloleetcode";
  int N;
  map<char, int> charToIndex;
  string indexToChar;
  int charNum;
  vector<int> baseStat;

  int n;
  vector<string> words;
  vector<vector<int>> wordStat;
  vector<vector<int>> wordsCost;
  vector<vector<int>> wordsMask;

  int H(vector<int>& stat) {
    int h = 0;
    for (int j = 0; j < charNum; j++) {
      h = (h << baseStat[j]) + stat[j];
    }
    return h;
  }

  void TransChar(vector<string>& words) {
    N = base.length();

    map<char, char> m;
    for (auto c : base) {
      charToIndex[c];
    }

    charNum = 0;
    for (auto& [k, v] : charToIndex) {
      indexToChar.push_back(k);
      v = charNum++;
    }

    baseStat.resize(charNum, 0);
    for (auto c : base) {
      baseStat[charToIndex[c]]++;
    }

    wordsCost.resize(n, vector<int>(1 << N, INT_MAX));

    wordStat.resize(n, vector<int>(charNum, 0));
    for (int i = 0; i < n; i++) {
      const string& s = words[i];
      for (auto c : s) {
        wordStat[i][charToIndex[c]]++;
      }
    }
  }

  void UpdateWord(int i, vector<int>& stat, int cost) {
    int h = H(stat);
    wordsCost[i][h] = min(wordsCost[i][h], cost);
  }

  void DfsWord(int i, int l, int r, int leftLen, int rightLen, int cost,
               vector<int>& stat) {
    const string& s = words[i];
    if (l > r) return;  //

    int len = r - l + 1;

    // 选择左边
    if (charToIndex.count(s[l])) {
      int offset = charToIndex[s[l]];
      if (stat[offset] < baseStat[offset]) {
        stat[offset]++;
        int newCost = cost + leftLen * (len - 1 + rightLen);
        UpdateWord(i, stat, newCost);
        DfsWord(i, l + 1, r, leftLen, rightLen, newCost, stat);
        stat[offset]--;
      }
    }

    // 跳过左边
    DfsWord(i, l + 1, r, leftLen + 1, rightLen, cost, stat);

    // 选择右边
    if (charToIndex.count(s[r])) {
      int offset = charToIndex[s[r]];
      if (stat[offset] < baseStat[offset]) {
        stat[offset]++;
        int newCost = cost + (leftLen + len - 1) * rightLen;
        UpdateWord(i, stat, newCost);
        DfsWord(i, l, r - 1, leftLen, rightLen, newCost, stat);
        stat[offset]--;
      }
    }

    // 跳过右边
    DfsWord(i, l, r - 1, leftLen, rightLen + 1, cost, stat);
  }

  int dpWord(int p, int mask) {
    vector<int> stat(charNum, 0);
    for (int i = 0; i < N; i++) {
      int offset = charToIndex[base[i]];
      if (mask & (1 << i)) {
        stat[offset]++;
      }
    }

    for (int i = 0; i < charNum; i++) {
      if (stat[i] > wordStat[p][i]) return INT_MAX;
    }

    int h = H(stat);
    return wordsCost[p][h];
  }

  int Dfs(const int p, const int mask) {
    if (mask == 0) return 0;
    if (p < 0) return INT_MAX;
    printf("p=%d mask=%d \n", p, mask);

    int& ret = dp[p][mask];
    if (ret != -1) {
      return ret;
    }
    ret = Dfs(p - 1, mask);

    for (auto h: wordsMask[p]) {  // 枚举第 k 个字符串的 mask 列表
      int wordCost = dpWord(p, i);
      int cost = Dfs(p - 1, mask ^ i);
      if (cost != INT_MAX && wordCost != INT_MAX) {
        ret = min(ret, cost + wordCost);
      }
    }

    printf("p=%d mask=%d ret=%d\n", p, mask, ret);
    return ret;
  }

 public:
  int Leetcode(vector<string>& words_) {
    words.swap(words_);

    n = words.size();
    TransChar(words);

    wordsMask.resize(n);
    for (int i = 0; i < n; i++) {
      const string& s = words[i];
      vector<int> stat(charNum, 0);
      DfsWord(i, 0, s.length() - 1, 0, 0, 0, stat);

      wordsMask[i].reserve(wordsCost[i].size());
      for(int j=0;j<wordsCost[i].size();j++){
        if(wordsCost[i][j] != INT_MAX){
          wordsMask[i].push_back(j);
        }
      }
    }

    memset(dp, -1, sizeof(dp));
    int ret = Dfs(n - 1, (1 << N) - 1);
    if (ret == INT_MAX) {
      ret = -1;
    }
    return ret;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
