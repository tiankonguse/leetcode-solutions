
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
/*
给你一个字符串 s 和一个整数 k 。请你找出 s 的子字符串 subs 中两个字符的出现频次之间的 最大 差值，freq[a] - freq[b]
，其中： subs 的长度 至少 为 k 。 字符 a 在 subs 中出现奇数次。 字符 b 在 subs 中出现偶数次。 返回 最大 差值。
*/
class Solution {
 public:
  int maxDifference(const string& s, const int k) {
    const int n = s.size();
    ll ans = INT_MIN;
    auto UpdateMax = [](ll& ret, ll v) { ret = max(ret, v); };
    auto NumState = [](int v) {
      if (v == 0) return 0;
      if (v % 2 == 1) return 1;
      return 2;
    };
    auto Solver = [&](int a, int b) -> ll {
      vector<int> preA(n + 1, 0);
      vector<int> preB(n + 1, 0);
      for (int i = 1; i <= n; i++) {
        int v = s[i - 1] - '0';
        preA[i] = preA[i - 1];
        preB[i] = preB[i - 1];
        if (v == a) {
          preA[i]++;
        } else if (v == b) {
          preB[i]++;
        }
      }
      ll ansTmp = INT_MIN;
      if (preA[n] == 0 || preB[n] == 0) return ansTmp;

      vector<vector<ll>> pre(3, vector<ll>(3, INT_MIN));
      // pre[0][0] = 0;
      int nextState[3] = {1, 2, 1};

      vector<vector<ll>> now(3, vector<ll>(3, INT_MIN));
      for (int i = k; i <= n; i++) {
        for (int A = 0; A < 3; A++) {
          for (int B = 0; B < 3; B++) {
            now[A][B] = INT_MIN;
          }
        }
        const ll numA = preA[i] - preA[i - k];
        const ll numB = preB[i] - preB[i - k];
        const int v = s[i - 1] - '0';
        // printf("i=%d v=%d numA=%lld numB=%lld\n", i, v, numA, numB);

        // 添加大于 k 的子串
        for (int A = 0; A < 3; A++) {
          for (int B = 0; B < 3; B++) {
            if (v == a) {
              UpdateMax(now[nextState[A]][B], pre[A][B] + 1);
            } else if (v == b) {
              UpdateMax(now[A][nextState[B]], pre[A][B] - 1);
            } else {
              UpdateMax(now[A][B], pre[A][B]);
            }
          }
        }

        // 添加 k 子串自身
        UpdateMax(now[NumState(numA)][NumState(numB)], numA - numB);
        pre.swap(now);
        // printf("i=%d tmpAns=%lld\n", i, pre[1][2]);
        UpdateMax(ansTmp, pre[1][2]);
      }
      return ansTmp;
    };
    // Solver(2, 1);
    for (int a = 0; a <= 4; a++) {
      for (int b = 0; b <= 4; b++) {
        if (a == b) continue;
        // printf("a=%d b=%d ans=%lld\n", a, b, Solver(a, b));
        ans = max(ans, Solver(a, b));
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