#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

void SuffixArray(char* str, int n, vector<int>& sa, vector<int>& rk) {
  vector<pair<pair<int, int>, int>> nums(n);

  cnt.resize(n, 0);
  pos.resize(n, 0);
  tmpNums.resize(n);

  sa.resize(n, 0);
  rk.resize(n, 0);

  for (int k = 0; 1 << max(k - 1, 0) < n; k++) {
    for (int j = 0; j < n; j++) {
      pair<int, int> v;
      if (k > 0) {
        int leftRank = rk[j];
        int rightRank = rk[(j + (1 << (k - 1))) % n];
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
      sa[j] = nums[j].second;  // 排名第 j 的位置
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
      rk[pos] = rank;  // 第pos个值的排名
    }
    if (rank + 1 == n) break;  // 剪枝，已经没有重复了
  }
}

void BuildHeight(char* str, int n, vector<int>& sa, vector<int>& rk, vector<int>& height) {
  height.resize(n, 0);
  int k = 0;
  for (int i = 0; i < n - 1; i++) {  // 依次从最长的前缀开始处理
    int pi = rk[i];                  // s[i...n]; 的排名
    int j = sa[pi - 1];              // pi 上一名的位置
    while (str[i + k] == str[j + k]) k++;
    height[pi] = k;
    k = max(k - 1, 0);
  }
}

void BuildST(vector<int>& height, vector<vector<int>>& st) {
  int n = height.size();
  st.resize(n, vector<int>(20, 0));
  for (int i = 0; i < n; i++) {
    st[i][0] = height[i];
  }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; i + (1 << j) <= n; i++) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}

vector<int> sa;      // 第几名的位置, 对应 sa
vector<int> rk;      // 第几个元素排第几名, 对应 rk
vector<int> height;  // 第几名与上一名的最长前缀, 对应 height
vector<vector<int>> st;
inline int MaxBit(int v) { return 31 - __builtin_clz(v); }
int Lcp(int i, int j) {
  const int n = st.size();
  if (i == j) return n - i;
  int ri = rk[i];
  int rj = rk[j];
  if (ri > rj) {
    swap(ri, rj);
  }
  int l = ri + 1;
  int r = rj + 1;
  int k = MaxBit(r - l);
  return min(st[l][k], st[r - (1 << k)][k]);
}

void SuffixArray(char* str, int n) { SuffixArray(str, n, sa, rk); }
void BuildHeight(char* str, int n) { BuildHeight(str, n, sa, rk, height); }
void BuildST() { BuildST(height, st); }

void BuildRA(char* str, int n) {
  SuffixArray(str, n);
  BuildHeight(str, n);
  BuildST();
}

const int N = 4e5 + 10;
char str[N];
int n;
void InitIO() {
  // #ifdef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
  scanf("%s", str);
  n = strlen(str);
  str[n++] = '$';
  str[n] = '\0';
}

void Solver() {  //
  SuffixArray(str, n, sa, rk);
  BuildHeight(str, n, sa, rk, height);
  BuildST(height, st);
}