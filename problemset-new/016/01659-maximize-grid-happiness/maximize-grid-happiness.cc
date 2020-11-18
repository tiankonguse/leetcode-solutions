#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;

const int N = 3 * 3 * 3 * 3 * 3;
int dp[6][7][7][N];
unordered_map<int, int> hashCal;
struct StInfo {
  int now[6], a, b;
};
StInfo hashDecode[N];

class Solution {
  int M, maxM;
  void decode(int bit, int now[6], int& aNow, int& bNow) {
    int index = 0;
    memset(now, 0, sizeof(int) * 6);
    aNow = bNow = 0;
    while (bit) {
      now[index] = bit % 3;
      if (now[index] == 1) {
        aNow++;
      } else if (now[index] == 2) {
        bNow++;
      }
      index++;
      bit /= 3;
    }
  }

  int Cal(int a, int b) {
    int* pre = hashDecode[a].now;
    int* now = hashDecode[b].now;
    int ans = 0;

    // 自身的幸福值
    for (int i = 0; i < M; i++) {
      if (now[i] == 1) {
        ans += 120;
      } else if (now[i] == 2) {
        ans += 40;
      }
    }

    // 上一个与当前
    for (int i = 0; i < M; i++) {
      if (pre[i] == 1 && now[i] != 0) {
        ans -= 30;
      } else if (pre[i] == 2 && now[i] != 0) {
        ans += 20;
      }
    }

    // 当前与上一个
    for (int i = 0; i < M; i++) {
      if (now[i] == 1 && pre[i] != 0) {
        ans -= 30;
      } else if (now[i] == 2 && pre[i] != 0) {
        ans += 20;
      }
    }

    // 当前内部
    for (int i = 0; i < M; i++) {
      if (M > 1 && i < M - 1) {
        if (now[i] == 1 && now[i + 1] != 0) {
          ans -= 30;
        } else if (now[i] == 2 && now[i + 1] != 0) {
          ans += 20;
        }
      }
      if (i > 0) {
        if (now[i] == 1 && now[i - 1] != 0) {
          ans -= 30;
        } else if (now[i] == 2 && now[i - 1] != 0) {
          ans += 20;
        }
      }
    }

    return ans;
  }

  int H(int a, int b) { return a * 1000 + b; }

  int dfs(int n, int A, int B, int K) {
    if (dp[n][A][B][K] != ninf) {
      return dp[n][A][B][K];
    }

    int ans = ninf;
    int aNow = hashDecode[K].a;
    int bNow = hashDecode[K].b;

    if (n == 0) {
      ans = hashCal[H(0, K)];
    } else {
      for (int i = 0; i < maxM; i++) {
        if (aNow + hashDecode[i].a > A || bNow + hashDecode[i].b > B) {
          continue;
        }

        int tmp = hashCal[H(i, K)] + dfs(n - 1, A - aNow, B - bNow, i);

        ans = max(ans, tmp);
      }
    }

    return dp[n][A][B][K] = ans;
  }

 public:
  int getMaxGridHappiness(int n, int m, int introvertsCount,
                          int extrovertsCount) {
    memset(dp, ninf, sizeof(dp));
    if (n < m) {
      swap(n, m);
    }

    M = m;
    maxM = 1;
    for (int i = 1; i <= M; i++) {
      maxM *= 3;
    }
    for (int i = 0; i < maxM; i++) {
      decode(i, hashDecode[i].now, hashDecode[i].a, hashDecode[i].b);
    }
    for (int i = 0; i < maxM; i++) {
      for (int j = 0; j < maxM; j++) {
        hashCal[H(i, j)] = Cal(i, j);
      }
    }

    // n >= m
    return dfs(n, introvertsCount, extrovertsCount, 0);
  }
};

int main() {
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 1, 2, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 3, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 1240, 5, 5, 6, 6);

  return 0;
}
