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
题意: n 个字符串，每个字符串选择一些字母，最终选择的字母调整顺序后，可以组成 "helloleetcode"
选择代价：字符串中，左边字符个数 * 右边字符个数。  
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


dpWord(k, mask): 第 k 个字符串筛选出 mask 的最优答案， 可以预处理得到。  
预处理方法1：预处理字符串字符，对有效字符的集合进行枚举，然后贪心计算出合法的 mask 列表以及答案。
贪心：左右依次寻找最近的。 好像有反例

预处理方法2：预处理字符串，dfs 枚举所有有效字符的排列，计算出所有 mask 的答案。
问题： dpWord dfs 的 是计数 mask， dp 的是"helloleetcode"状态压缩 mask，需要进行转换映射
转化方法：对 "helloleetcode" 有 8 个不同字符, 每个字符分配 3 bit，共 24 个 bit。
复杂度： O(8! * 8)  ： O(8!) 排列组合得到字符几个，O(n) 映射到 mask。

*/

int dp[24][8192];      // -2 代表未计算， -1 代表无解
int dpWord[24][8192];  // 一个单词取 mask 的最优答案

struct DoubleLink {
  int pos = 0;
  DoubleLink* pre = nullptr;
  DoubleLink* next = nullptr;
} head[26], tail[26], buf[100];

int strUseFlag[9];

class Solution {
  int MASK;
  int n;
  string base = "helloleetcode";
  int MASKLEN;
  string baseEx;
  vector<int> h;
  int bufIndex = 0;
  vector<vector<int>> wordStat;

  DoubleLink* New() {
    DoubleLink* v = buf + bufIndex;
    bufIndex++;
    return v;
  }

  void InitDoubleLink(const string& word) {
    memset(head, 0, sizeof(head));
    memset(tail, 0, sizeof(tail));

    for (auto c : baseEx) {
      int i = c - 'a';
      head[i]->pos = -1;
      tail[i]->pos = -1;
      head[i]->next = &tail[i];
      tail[i]->pre = &head[i];
    }

    bufIndex = 0;
    for (int i = 0; i < word.size(); i++) {
      int p = word[i] - 'a';
      if (h[p] == 0) continue;

      auto v = New();
      v->pos = i;
      v->pre = tail[p]->pre;
      v->next = tail[p];
      v->pre->next = v;
      v->next->pre = v;
    }
  }

  vector<int> maskStat;
  void MaskToStat(int mask, vector<int>& maskStat) {
    maskStat.clear();
    maskStat.resize(26, 0);
    int i = 0;
    for (int i = 0; i < MASKLEN; i++) {
      if (mask & (1 << i)) {
        maskStat[base[i]]++;
      }
    }
  }

  bool CheckMaskStat(vector<int>& maskStat, vector<int>& stat) {
    for (auto c : baseEx) {
      int p = c - 'a';
      if (stat[p] < maskStat[p]) {
        return false;
      }
    }
    return true;
  }

  int CalWordAns(int n, int p) {
    int leftNum = 0, rightNum = 0;
    for (int i = 0; i < p; i++) {
      if (strUseFlag[i] == 1) continue;
      leftNum++;
    }
    for (int i = p + 1; i < n; i++) {
      if (strUseFlag[i] == 1) continue;
      rightNum++;
    }
    return leftNum * rightNum;
  }

  int SolverWord(const string& word, int maskLen, vector<int>& maskStat) {
    InitDoubleLink(word);
    memset(strUseFlag, 0, sizeof(strUseFlag));

    for (int i = 0; i < maskLen; i++) {
      DoubleLink* ans = nullptr;
      int tmpAns = 100;

      for (auto c : baseEx) {
        int p = c - 'a';
        if (maskStat[p] == 0) continue;

        int leftAns = CalWordAns(word.size(), head[p].next->pos);
        int rightAns = CalWordAns(word.size(), tail[p].pre->pos);
        if(leftAns < rightAns)
      }
    }

    return 0;
  }

  void Init(const string& word, int* dp, vector<int>& stat) {
    int len = word.size();

    for (auto c : word) {
      stat[c - 'a']++;
    }

    dp[0] = 0;
    for (int i = 1; i < MASK; i++) {
      int one = __builtin_popcount(i);
      if (one > len) {  // 剪枝
        dp[i] = -1;
        continue;
      }

      MaskToStat(i, maskStat);
      if (!CheckMaskStat(maskStat, stat)) {  // 无解
        dp[i] = -1;
        continue;
      }

      // 寻找最优解，贪心
      dp[i] = SolverWord(word, one, maskStat);
    }
  }
  void Init(const vector<string>& words) {
    memset(dpWord, -1, sizeof(dpWord));
    wordStat.resize(n, vector<int>(26, 0));

    h.resize(26, 0);
    for (auto c : base) {
      if (h[c - 'a'] == 0) {
        h[c - 'a'] = 1;
        baseEx.push_back(c);
      }
    }

    for (int i = 0; i < n; i++) {
      Init(words[i], dpWord[i], wordStat[i]);
    }
  }

 public:
  int Leetcode(vector<string>& words) {
    n = words.size();

    MASKLEN = base.size();
    MASK = 1 << MASKLEN;
    memset(dp, -2, sizeof(dp));

    Init(words);

    return Dfs(n - 1, MASK - 1);
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
