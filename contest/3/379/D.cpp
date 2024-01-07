// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  string s;
  int K_;
  inline int K() { return K_; }
  vector<vector<vector<int>>> dp;
  int N_;
  inline int N() { return N_; }

  inline int Get(int bit, int offset) { return (bit >> offset) & 1; }
  inline int Set(int& bit, int offset) { return bit |= 1 << offset; }

  int Dfs(const int p, const int flag) {
    if (p >= N()) {
      return 0;
    }

    int& ret = dp[flag][s[p] - 'a'][p];
    if (ret != -1) return ret;

    ret = 0;

    {  // 不使用 flag
      int P = p;
      int k = 0;
      int bit = 0;
      while (P < N() && k <= K()) {
        int v = s[P] - 'a';
        if (!Get(bit, v)) {
          if (k == K()) break;
          k++;
          Set(bit, v);
        }
        P++;
      }
      ret = max(ret, 1 + Dfs(P, flag));
      printf("unuse flag, p=%d flag=%d  K=%d ret=%d\n", p, flag, K(), ret);
    }

    if (K() < 26 && flag == 0) {  // 使用, 首次触发 K 个时，下一个设置为不同值
      int P = p;
      int k = 0;
      int bit = 0;
      int FLAG = 0;
      while (P < N() && k < K()) {
        int v = s[P] - 'a';
        if (!Get(bit, v)) {
          k++;
          Set(bit, v);
        }
        P++;
      }
      if (k == K()) {  // 满足 k 个，分情况讨论

        // 通过修改与下个相同的字符，使得下个不满足
        ret = max(ret, 1 + Dfs(P, 1));  // 修改前面
        if (P < N()) {                  // 修改后面
          for (int i = 0; i < 26; i++) {
            if (Get(bit, i)) continue;
            const char oldChar = s[P];
            s[P] = 'a' + i;
            ret = max(ret, 1 + Dfs(P, 1));
            s[P] = oldChar;
          }
        }

        if (P - p > k) {  // 大于 K() 个
          P--;  // 修改某个相同值，使得最后一个超过限制
          ret = max(ret, 1 + Dfs(P, 1));
        }
      }
      printf("use flag, p=%d flag=%d  K=%d ret=%d\n", p, flag, K(), ret);
    }

    return ret;
  }

 public:
  int maxPartitionsAfterOperations(string& s_, int k_) {
    s.swap(s_);
    K_ = k_;
    N_ = s.size();

    dp.resize(2, vector<vector<int>>(26, vector<int>(N_ + 2, -1)));

    return Dfs(0, 0);
  }
};