#include <bits/stdc++.h>
using namespace std;

// n: 数组长度, q: 查询次数, l,r: 查询区间, k: 区间中点
int n, q, l, r, k, st[50010], ll, rr, u;

// a[]: 前缀和数组
// mn[]: 每个位置向左k个位置内的最小前缀和
// mx[]: 每个位置向右k个位置内的最大前缀和
// v[]: 临时数组，存储中间计算结果
// x[]: 最终答案数组，存储每个位置的最大收益
long long a[50010], mn[50010], mx[50010], v[50010], x[50010];

const long long lim = 1e18;  // 极限值，用于标记无效位置
unsigned long long ans;      // 异或和答案

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  // 读入数组并计算前缀和
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    a[i] += a[i - 1];
  }

  cin >> q;

  // 处理每个查询
  for (int _ = 1; _ <= q; ++_) {
    cin >> l >> r;
    k = r - l >> 1;  // 计算区间中点偏移量

    // === 第一步：使用单调队列计算mx数组 ===
    // mx[i]表示从位置i开始，向右k个位置内的最大前缀和
    ll = 1;  // 队列左指针
    rr = 0;  // 队列右指针

    // 从右向左遍历，维护单调递减队列
    for (int i = n; ~i; --i) {
      // 移除超出窗口范围的元素（右边界超过i+k）
      while (ll <= rr && st[ll] > i + k) {
        ++ll;
      }
      // 维护单调性：移除所有小于等于当前值的元素
      while (ll <= rr && a[st[rr]] <= a[i]) {
        --rr;
      }
      // 当前位置入队
      st[++rr] = i;
      // 队首元素就是窗口内的最大值
      mx[i] = a[st[ll]];
    }

    // === 第二步：使用单调队列计算mn数组 ===
    // mn[i]表示从位置i开始，向左k个位置内的最小前缀和
    ll = 1;
    rr = 0;

    // 从左向右遍历，维护单调递增队列
    for (int i = 0; i <= n; ++i) {
      // 移除超出窗口范围的元素（左边界小于i-k）
      while (ll <= rr && st[ll] < i - k) {
        ++ll;
      }
      // 维护单调性：移除所有大于等于当前值的元素
      while (ll <= rr && a[st[rr]] >= a[i]) {
        --rr;
      }
      // 当前位置入队
      st[++rr] = i;
      // 队首元素就是窗口内的最小值
      mn[i] = a[st[ll]];
    }

    // === 第三步：初始化x数组 ===
    // x[i]表示以位置i结尾时的最大收益
    for (int i = 1; i < l; ++i) {
      x[i] = -lim;  // 长度小于l的位置标记为无效
    }
    for (int i = l; i <= n; ++i) {
      x[i] = mx[i] - mn[i - l];  // 基础收益：右侧最大值减去左侧最小值
    }

    // === 第四步：计算v数组（第一种情况）===
    // v[i]表示从位置i开始的某种特定收益
    for (int i = 1; i <= n - r + k + 1; ++i) {
      v[i] = max(mx[i + l - 1], mx[i + r - k - 1]) - a[i - 1];
    }
    for (int i = n - r + k + 2; i <= n - l + 1; ++i) {
      v[i] = mx[i + l - 1] - a[i - 1];
    }
    for (int i = n - l + 2; i <= n; ++i) {
      v[i] = -lim;  // 超出范围的位置标记为无效
    }

    // === 第五步：用单调队列更新x数组（第一轮）===
    // 在长度为l的窗口内找v的最大值来更新x
    ll = 1;
    rr = 0;
    for (int i = 1; i <= n; ++i) {
      // 移除超出窗口的元素
      while (ll <= rr && st[ll] <= i - l) {
        ++ll;
      }
      // 维护单调递减队列
      while (ll <= rr && v[st[rr]] <= v[i]) {
        --rr;
      }
      st[++rr] = i;
      // 用窗口内的最大v值更新x[i]
      x[i] = max(x[i], v[st[ll]]);
    }

    // === 第六步：计算v数组（第二种情况）===
    // 根据r-l与2*k的关系，分两种情况计算
    if (r - l == 2 * k) {
      // 当r-l恰好等于2*k时的特殊情况
      for (int i = l; i <= n - k; ++i) {
        v[i] = max(mx[i + k] - a[i - l], a[i + k] - mn[i - l]);
      }
    } else {
      // 一般情况：考虑更复杂的边界条件
      for (int i = l; i <= n - k; ++i) {
        v[i] = max(max(mx[i + k], a[min(n, i + r - l)]) - a[i - l], a[i + k] - min(mn[i - l], a[max(0, i - r + k)]));
      }
    }
    for (int i = n - k + 1; i <= n; ++i) {
      v[i] = -lim;  // 超出范围标记为无效
    }

    // === 第七步：用单调队列更新x数组（第二轮）===
    // 在长度为k的窗口内找v的最大值来更新x
    ll = 1;
    rr = 0;
    for (int i = l; i <= n; ++i) {
      // 移除超出窗口的元素
      while (ll <= rr && st[ll] < i - k) {
        ++ll;
      }
      // 维护单调递减队列
      while (ll <= rr && v[st[rr]] <= v[i]) {
        --rr;
      }
      st[++rr] = i;
      // 用窗口内的最大v值更新x[i]
      x[i] = max(x[i], v[st[ll]]);
    }

    // === 第八步：计算最终答案 ===
    // 将所有位置的收益乘以位置编号后进行异或运算
    ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans ^= (unsigned long long)x[i] * i;
    }
    cout << ans << '\n';
  }
}
