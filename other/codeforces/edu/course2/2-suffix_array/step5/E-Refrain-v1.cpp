/*
ID: tiankonguse
TASK: E. Refrain  E. 克制
LANG: C++
MAC EOF: ctrl+D
link:
https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/E
PATH: ITMO 学院：试点课程 » 后缀数组 » 步骤5 » 实践
submission:
https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/submission/298309064
*/
#define TASK "E-Refrain-v1"
#define TASKEX ""

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void CheckUsacoTask() {
#ifdef USACO_LOCAL_JUDGE
  string filePath = __FILE__;
  string fileNameEx = filePath.substr(filePath.rfind('/') + 1);
  string fileName = fileNameEx.substr(0, fileNameEx.find("."));
  assert(fileName == TASK TASKEX);
#endif
}

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

vector<int> cnt;
vector<int> pos;
vector<pair<pair<int, int>, int>> tmpNums;
template <typename F>
void radix_sort(vector<pair<pair<int, int>, int>>& nums, const F& Callback) {
  const int n = nums.size();
  for (auto& x : nums) {
    cnt[Callback(x.first)]++;
  }

  pos[0] = 0;  // 排名为 i 时，累计个数
  for (int r = 1; r < n; r++) {
    pos[r] = pos[r - 1] + cnt[r - 1];
  }

  for (auto& x : nums) {
    cnt[Callback(x.first)]--;  // 使用完了，还原数组
  }

  for (auto& x : nums) {
    int r = Callback(x.first);
    tmpNums[pos[r]] = x;
    pos[r]++;
  }
  tmpNums.swap(nums);
}

void SuffixArray(char* str, int n, vector<int>& p, vector<int>& c) {
  vector<pair<pair<int, int>, int>> nums(n);

  cnt.resize(n, 0);
  pos.resize(n, 0);
  tmpNums.resize(n);

  p.resize(n, 0);
  c.resize(n, 0);

  for (int k = 0; 1 << max(k - 1, 0) < n; k++) {
    for (int j = 0; j < n; j++) {
      pair<int, int> v;
      if (k > 0) {
        int leftRank = c[j];
        int rightRank = c[(j + (1 << (k - 1))) % n];
        v = {leftRank, rightRank};
      } else {
        v = {str[j], 0};  // 第一次，只需要对一个值排序
      }
      nums[j] = {v, j};
    }
    if (k == 0) {
      sort(nums.begin(), nums.end());
    } else {
      radix_sort(nums, [](const std::pair<int, int>& p) { return p.second; });
      radix_sort(nums, [](const std::pair<int, int>& p) { return p.first; });
    }

    for (int j = 0; j < n; j++) {
      p[j] = nums[j].second;  // 排名第 j 的位置
    }

    // 最小的肯定是 $
    auto pre = nums.front().first;
    int rank = 0;
    for (int j = 0; j < n; j++) {
      auto [v, pos] = nums[j];
      if (v != pre) {
        pre = v;
        rank++;
      }
      c[pos] = rank;  // 第pos个值的排名
    }
    if (rank + 1 == n) break;  // 剪枝，已经没有重复了
  }
}

void Lcp(char* str, int n, vector<int>& p, vector<int>& c, vector<int>& lcp) {
  lcp.resize(n, 0);
  int k = 0;
  for (int i = 0; i < n - 1; i++) {  // 依次从最长的前缀开始处理
    int pi = c[i];                   // s[i...n]; 的排名
    int j = p[pi - 1];               // pi 上一名的位置
    while (str[i + k] == str[j + k]) k++;
    lcp[pi] = k;
    k = max(k - 1, 0);
  }
}

vector<int> P;    // 第几名的位置, 对应 sa
vector<int> C;    // 第几个元素排第几名, 对应 rk
vector<int> lcp;  // 第几名与上一名的最长前缀, 对应 height

const int N = 3e5 + 10;
char str[N];
int n, m;
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    str[i] = 'a' + v;
  }
  str[n++] = '$';
  str[n] = '\0';
}
void Solver() {  //
  SuffixArray(str, n, P, C);
  Lcp(str, n, P, C, lcp);

  // printf("str=%s\n", str);
  // for (int i = 0; i < n; i++) {
  //   printf("s=[%s] rk=%d pos=%d lcp=%d\n", str + P[i], i, P[i], lcp[i]);
  // }

  ll ans = n - 1;
  ll ansLen = n - 1;
  ll ansNum = 1;
  ll ansPos = 0;
  auto UpdateAns = [&](ll tmpLen, ll tmpNum, ll tmpPos) {
    ll tmpAns = tmpLen * tmpNum;
    if (tmpAns > ans) {
      ans = tmpAns;
      ansLen = tmpLen;
      ansNum = tmpNum;
      ansPos = tmpPos;
    }
  };

  // 维护一个lcp单调递增栈，记录栈中记录小于当前后缀长度的最大连续区间
  vector<tuple<ll, ll, int>> sta;  // <h, num, pos>
  sta.reserve(n);
  sta.push_back({-1, 1, n});  // 保持栈永远不为空
  for (int i = 0; i < n; i++) {
    int h = lcp[i];
    int p = P[i];

    ll num = 0;
    while (get<0>(sta.back()) >= h) {
      auto [h1, num1, pos1] = sta.back();
      sta.pop_back();

      auto [h2, num2, pos2] = sta.back();
      sta.pop_back();

      if (h2 >= h) {  // 合并到前一个
        UpdateAns(h2, num1 + num2, pos2);
        sta.push_back({h2, num1 + num2, pos2});  // 向前合并
      } else {                                   // 向后合并
        sta.push_back({h2, num2, pos2});         // 还原上一个
        num = num1;
        break;
      }
    }
    UpdateAns(h, num + 1, p);  // 最新的加上之前的
    sta.push_back({h, num, p});

    UpdateAns(n - 1 - p, 1, p);    // p=0 时，答案应该是 n-1
    sta.push_back({n - p, 1, p});  // 最新的完整的后缀都插入堆栈
  }
  while (sta.size() >= 2) {
    auto [h1, num1, pos1] = sta.back();
    sta.pop_back();
    auto [h2, num2, pos2] = sta.back();
    sta.pop_back();
    UpdateAns(h2, num1 + num2, pos2);
    sta.push_back({h2, num1 + num2, pos2});  // 向前合并
  }

  // cf is win, bo support %lld, should use %I64d
  // printf("%s\n", to_string(ans).data());
  printf("%lld\n", ans);
  printf("%lld\n", ansLen);
  for (ll i = 0; i < ansLen; i++) {
    printf("%d%c", str[ansPos + i] - 'a', i + 1 == ansLen ? '\n' : ' ');
  }
}

void ExSolver() {
#ifdef USACO_LOCAL_JUDGE
  auto t1 = std::chrono::steady_clock::now();
#endif
  Solver();
#ifdef USACO_LOCAL_JUDGE
  auto t2 = std::chrono::steady_clock::now();
  auto my =
      std::chrono::duration_cast<std::chrono::duration<double, ratio<1, 1000>>>(
          t2 - t1);
  printf("my 用时: %.0lfms\n", my.count());
#endif
}

int main(int argc, char** argv) {
  CheckUsacoTask();
  InitIO();
  ExSolver();
  return 0;
}

/*

*/