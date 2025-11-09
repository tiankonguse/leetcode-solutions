#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

namespace DC3 {

// 所有下标都是0~n-1，height[0]无意义。
// 所有相关数组都要开三倍
// 0 作为全局最小哨兵，输入字符需映射到 [1..m]
// 原字符串必须以一个最小的且前面没有出现过的字符结尾，这样才能保证结果正确
const int maxn = 6e6 + 10;
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)

int wa[maxn * 3], wb[maxn * 3], wv[maxn * 3], ws[maxn * 3];

int c0(const int* r, int a, int b) { return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2]; }
int c12(int k, const int* r, int a, int b) {
  if (k == 2) {
    return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
  } else {
    return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
  }
}
void sort(const int* r, int* a, int* b, int n, int m) {
  int i;
  for (i = 0; i < n; i++) wv[i] = r[a[i]];
  for (i = 0; i <= m; i++) ws[i] = 0;  // m 作为上界
  for (i = 0; i < n; i++) ws[wv[i]]++;
  for (i = 1; i <= m; i++) ws[i] += ws[i - 1];
  for (i = n - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
}
void dc3(int* r, int* sa, int n, int m) {
  int i, j;
  int* rn = r + n;    // 使用 r 的后段存放压缩名(需要 r 具备 3n 容量)
  int* san = sa + n;  // sa 的后段作为递归的 sa
  int ta = 0, tb = (n + 1) / 3, tbc = 0, p;

  r[n] = r[n + 1] = 0;  // 哨兵
  for (i = 0; i < n; i++)
    if (i % 3 != 0) wa[tbc++] = i;

  sort(r + 2, wa, wb, tbc, m);
  sort(r + 1, wb, wa, tbc, m);
  sort(r, wa, wb, tbc, m);

  for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++) rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;

  if (p < tbc)
    dc3(rn, san, tbc, p);
  else
    for (i = 0; i < tbc; i++) san[rn[i]] = i;

  for (i = 0; i < tbc; i++)
    if (san[i] < tb) wb[ta++] = san[i] * 3;
  if (n % 3 == 1) wb[ta++] = n - 1;

  sort(r, wb, wa, ta, m);

  for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;

  for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++) sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
  for (; i < ta; p++) sa[p] = wa[i++];
  for (; j < tbc; p++) sa[p] = wb[j++];
}

// str 和 sa 也要三倍，但这里 r 在 BuildRA 内部构造，避免修改调用者内存
void da(int r[], int sa[], int rank[], int height[], int n, int m) {
  for (int i = n; i < n * 3; i++) r[i] = 0;  // 清尾保证安全访问
  dc3(r, sa, n + 1, m);                      // 含一个哨兵位

  int i, j, k;
  for (i = 0; i < n; i++) {
    sa[i] = sa[i + 1];  // 去掉哨兵suffix
    rank[sa[i]] = i;
  }
  for (i = 0, j = 0, k = 0; i < n; height[rank[i++]] = k)
    if (rank[i] > 0) {
      j = sa[rank[i] - 1];
      if (k) k--;
      while (i + k < n && j + k < n && r[i + k] == r[j + k]) k++;
    }
}

void BuildST(int n, int height[], vector<vector<int>>& st) {
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

int sa[maxn * 3];      // 第几名的位置, 对应 sa
int rk[maxn * 3];      // 第几个元素排第几名, 对应 rk
int height[maxn * 3];  // 第几名与上一名的最长前缀, 对应 height
vector<vector<int>> st;
int r[maxn * 3];

inline int MaxBit(int v) { return 31 - __builtin_clz(v); }

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
int LcpRk(int ri, int rj) {
  assert(ri <= rj);
  if (ri == rj) {
    return st.size() - sa[ri];
  }
  if (ri > rj) {
    swap(ri, rj);
  }
  int l = ri + 1;
  int r = rj + 1;
  int k = MaxBit(r - l);
  return min(st[l][k], st[r - (1 << k)][k]);
}

void BuildRA(char* str, int n, int m = 256) {                    //  m 为值域
  for (int i = 0; i < n; i++) r[i] = (unsigned char)str[i] + 1;  // 映射到 [1..m]
  da(r, sa, rk, height, n, m);
  BuildST(n, height, st);
}

};  // namespace DC3