
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

typedef long long ll;

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
    }
  }
  void AddScore(int x) {
    x = Find(x);
    score[x]++;
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};

Dsu dsu;
class Solution {
 public:
  // 前缀函数 next[j]： 前缀 [0,j] 的最长公共前后缀的长度
  // 即第 j 位匹配失败时，说明 pat[0,j-1] 与前缀是匹配的，此时 j 应该回退到 next[j-1]+1 重新开始匹配
  // 扩展: 计算 Next 是一个在线算法，可以按顺序计算 Next 数组，故可以计算树上的 Next
  //
  // 应用:
  // - 在字符串中查找子串：Knuth–Morris–Pratt 算法
  // - 字符串的周期: n - (next[n-1]+1)
  // - 统计每个前缀的出现次数
  // - 一个字符串中本质不同子串的数目
  // - 字符串压缩
  // - 根据前缀函数构建一个自动机
  // https://oi-wiki.org/string/kmp/
  //

  void getNext(const char* pat, vector<int>& next) {
    for (int i = 1; pat[i]; ++i) {
      int k = next[i - 1];
      while (k >= 0 && pat[k + 1] != pat[i]) {
        k = next[k];
      }
      if (pat[k + 1] == pat[i]) {
        next[i] = k + 1;
      }
    }
  }

  int kmp(const char* str, const char* pat, vector<int>& next) {
    int i = 0, j = 0;
    while (str[i] && pat[j]) {
      if (pat[j] == str[i]) {
        ++i;
        if (!pat[++j]) {
          return i - j;
        }
      } else if (j == 0) {
        ++i;
      } else {
        j = next[j - 1] + 1;
      }
    }
    return -1;
  }

  int minimumGroups(vector<string>& words) {
    int n = words.size();
    vector<string> strs;
    vector<vector<int>> nexts;
    strs.resize(n);
    nexts.resize(n);
    for (int i = 0; i < n; i++) {
      strs[i] = words[i] + words[i];
      nexts[i].resize(strs[i].size() + 1, -1);
      getNext(strs[i].c_str(), nexts[i]);
    }

    dsu.Init(n);

    return 1;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif