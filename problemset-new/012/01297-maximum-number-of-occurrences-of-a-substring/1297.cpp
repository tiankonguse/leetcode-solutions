
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const int mod1e7 = 1000000007, mod1e9 = 1000000009;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

const ll BASE = 29;

ll h[max6];
ll qpowCache[max6];

ll H(int l, int r) {
  if (l == 0) return h[r];
  ll pre = h[l - 1] * qpowCache[r - l + 1] % mod1e7;
  return (h[r] - pre + mod1e7) % mod1e7;
}

ll hash(const char* str, int l, int r) {
  ll pre = 0;
  for (int i = l; i < r; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
  }
  return pre;
}

void Init(const char* str, int n) {
  qpowCache[0] = 1;
  for (int i = 1; i <= n; i++) {
    qpowCache[i] = (qpowCache[i - 1] * BASE) % mod1e7;
  }

  ll pre = 0;
  for (int i = 0; i < n; i++) {
    pre = (pre * BASE + (str[i] - 'a' + 1)) % mod1e7;
    h[i] = pre;
  }
}
class Solution {
 public:
  int maxFreq(const string& s, int maxLetters, int minSize, int maxSize) {
    int n = s.size();
    int ans = 0;
    Init(s.c_str(), n);  // 初始化哈希预处理数组

    // 遍历所有可能的子串长度
    for (int k = minSize; k <= maxSize; k++) {
      unordered_map<ll, int> count;  // 哈希值出现次数统计
      unordered_map<char, int> cnt;  // 字符出现次数统计

      // 滑动窗口维护字符计数
      for (int i = 0; i < n; i++) {
        cnt[s[i]]++;  // 增加右边界字符计数

        int l = i - k + 1;  // 窗口左边界索引
        if (l < 0) continue;

        // 当不同字符数符合要求时统计哈希值
        if (cnt.size() <= maxLetters) {
          ll hh = H(l, i);            // 计算子串哈希值
          count[hh]++;                // 更新哈希值出现次数
          ans = max(ans, count[hh]);  // 维护最大值
        }

        // 移除左边界字符计数
        cnt[s[l]]--;
        if (cnt[s[l]] == 0) {
          cnt.erase(s[l]);  // 清理计数为0的字符
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif