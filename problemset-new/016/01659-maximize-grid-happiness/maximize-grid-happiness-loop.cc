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

 public:
  int getMaxGridHappiness(int n, int m, int A, int B) {
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

    for (int i = 0; i < n; i++) {
      for (int a = 0; a <= A; a++) {
        for (int b = 0; b <= B; b++) {
          for (int j = 0; j < maxM; j++) {
            int aNow = hashDecode[j].a;
            int bNow = hashDecode[j].b;
            if (aNow > a || bNow > b) {
              continue;
            }

            if (i == 0) {
              dp[i][a][b][j] = hashCal[H(0, j)];
              continue;
            }

            int ans = ninf;

            for (int k = 0; k < maxM; k++) {
              if (aNow + hashDecode[k].a > a || bNow + hashDecode[k].b > b) {
                continue;
              }

              int tmp = hashCal[H(k, j)] + dp[i - 1][a - aNow][b - bNow][k];
              ans = max(ans, tmp);
            }

            dp[i][a][b][j] = ans;
          }
        }
      }
    }

    int ans = ninf;
    for (int i = 0; i < maxM; i++) {
      if (hashDecode[i].a > A || hashDecode[i].b > B) {
        continue;
      }

      int tmp = hashCal[H(i, 0)] + dp[n - 1][A][B][i];

      ans = max(ans, tmp);
    }

    // n >= m
    return ans;
  }
};

int main() {
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 1, 1, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 1, 1, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 1, 1, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 2, 1, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 2, 1, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 1, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 150, 2, 1, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 180, 2, 1, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 2, 2, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 2, 2, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 2, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 2, 2, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 2, 2, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 2, 2, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 2, 2, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 2, 2, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 2, 2, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 2, 2, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 2, 2, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 2, 2, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 2, 2, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 2, 2, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 2, 2, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 2, 2, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 2, 2, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 2, 2, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 2, 2, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 2, 2, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 3, 1, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 3, 1, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 1, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 1, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 1, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 1, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 1, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 1, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 3, 1, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 3, 1, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 3, 1, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 3, 1, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 3, 1, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 230, 3, 1, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 1, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 1, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 1, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 1, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 1, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 260, 3, 1, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 3, 2, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 3, 2, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 2, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 2, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 3, 2, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 3, 2, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 2, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 3, 2, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 2, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 3, 2, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 430, 3, 2, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 2, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 3, 2, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 350, 3, 2, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 3, 2, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 2, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 2, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 3, 2, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 3, 2, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 460, 3, 2, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 2, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 2, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 3, 2, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 3, 2, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 460, 3, 2, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 2, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 2, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 3, 2, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 3, 2, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 460, 3, 2, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 2, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 2, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 3, 2, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 3, 2, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 460, 3, 2, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 2, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 3, 2, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 2, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 3, 3, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 3, 3, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 3, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 3, 3, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 3, 3, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 3, 3, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 3, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 3, 3, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 3, 3, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 3, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 3, 3, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 3, 3, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 3, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 630, 3, 3, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 3, 3, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 3, 3, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 3, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 3, 3, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 550, 3, 3, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 630, 3, 3, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 740, 3, 3, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 3, 3, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 3, 3, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 470, 3, 3, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 550, 3, 3, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 660, 3, 3, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 3, 3, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 3, 3, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 3, 3, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 3, 3, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 580, 3, 3, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 3, 3, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 700, 3, 3, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 3, 3, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 3, 3, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 3, 3, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 610, 3, 3, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 620, 3, 3, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 3, 3, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 700, 3, 3, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 3, 3, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 3, 3, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 3, 3, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 610, 3, 3, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 620, 3, 3, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 3, 3, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 700, 3, 3, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 3, 3, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 3, 3, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 4, 1, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 4, 1, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 1, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 4, 1, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 1, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 1, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 1, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 1, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 4, 1, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 1, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 310, 4, 1, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 310, 4, 1, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 310, 4, 1, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 310, 4, 1, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 1, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 270, 4, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 4, 1, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 1, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 4, 1, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 1, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 4, 1, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 1, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 300, 4, 1, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 1, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 340, 4, 1, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 4, 2, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 4, 2, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 2, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 4, 2, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 2, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 2, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 2, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 2, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 4, 2, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 2, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 2, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 2, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 2, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 630, 4, 2, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 2, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 2, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 2, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 2, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 550, 4, 2, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 610, 4, 2, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 2, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 2, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 2, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 470, 4, 2, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 530, 4, 2, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 590, 4, 2, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 660, 4, 2, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 2, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 2, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 4, 2, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 2, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 570, 4, 2, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 2, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 660, 4, 2, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 2, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 2, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 4, 2, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 2, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 570, 4, 2, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 2, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 660, 4, 2, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 2, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 2, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 500, 4, 2, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 2, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 570, 4, 2, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 2, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 660, 4, 2, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 2, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 4, 3, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 4, 3, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 3, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 4, 3, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 3, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 3, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 3, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 3, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 4, 3, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 3, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 3, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 3, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 3, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 3, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 3, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 3, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 3, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 3, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 4, 3, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 3, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 4, 3, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 3, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 3, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 3, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 4, 3, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 670, 4, 3, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 750, 4, 3, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 870, 4, 3, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 3, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 3, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 4, 3, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 3, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 4, 3, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 850, 4, 3, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 960, 4, 3, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 4, 3, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 3, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 710, 4, 3, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 780, 4, 3, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 830, 4, 3, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 890, 4, 3, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 960, 4, 3, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 4, 3, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 740, 4, 3, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 4, 3, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 810, 4, 3, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 870, 4, 3, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 890, 4, 3, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 960, 4, 3, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 4, 4, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 4, 4, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 4, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 4, 4, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 4, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 4, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 4, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 4, 4, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 4, 4, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 4, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 4, 4, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 4, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 4, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 4, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 4, 4, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 4, 4, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 4, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 4, 4, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 4, 4, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 4, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 4, 4, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 4, 4, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 4, 4, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 4, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 4, 4, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 4, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 4, 4, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 4, 4, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 4, 4, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 4, 4, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 4, 4, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 4, 4, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 4, 4, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 4, 4, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 990, 4, 4, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 4, 4, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 4, 4, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 4, 4, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 4, 4, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 910, 4, 4, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 990, 4, 4, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1100, 4, 4, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 4, 4, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 4, 4, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 4, 4, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 920, 4, 4, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 1020, 4, 4, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1080, 4, 4, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1140, 4, 4, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 5, 1, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 5, 1, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 1, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 5, 1, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 1, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 1, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 5, 1, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 1, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 1, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 390, 5, 1, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 390, 5, 1, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 390, 5, 1, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 1, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 1, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 350, 5, 1, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 5, 1, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 1, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 5, 1, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 1, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 5, 1, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 1, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 1, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 380, 5, 1, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 1, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 420, 5, 1, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 5, 2, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 5, 2, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 2, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 5, 2, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 2, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 2, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 2, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 2, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 5, 2, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 2, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 2, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 2, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 2, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 2, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 2, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 2, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 2, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 2, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 2, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 2, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 750, 5, 2, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 2, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 2, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 2, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 2, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 670, 5, 2, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 730, 5, 2, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 790, 5, 2, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 2, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 2, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 590, 5, 2, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 650, 5, 2, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 710, 5, 2, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 770, 5, 2, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 5, 2, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 2, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 620, 5, 2, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 2, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 690, 5, 2, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 710, 5, 2, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 770, 5, 2, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 5, 2, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 2, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 620, 5, 2, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 2, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 690, 5, 2, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 710, 5, 2, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 770, 5, 2, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 5, 2, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 5, 3, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 5, 3, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 3, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 5, 3, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 3, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 3, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 3, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 3, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 5, 3, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 3, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 3, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 3, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 3, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 3, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 3, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 3, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 3, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 3, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 3, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 3, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 3, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 3, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 3, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 3, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 3, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 3, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 3, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 3, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 3, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 3, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 3, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 3, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 3, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 3, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 990, 5, 3, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 3, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 3, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 3, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 3, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 910, 5, 3, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 990, 5, 3, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1100, 5, 3, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 3, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 3, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 830, 5, 3, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 910, 5, 3, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 1020, 5, 3, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1080, 5, 3, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1130, 5, 3, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 5, 4, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 5, 4, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 4, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 5, 4, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 4, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 4, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 4, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 4, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 5, 4, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 4, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 4, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 4, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 4, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 4, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 4, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 4, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 4, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 4, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 4, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 4, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 4, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 4, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 4, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 4, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 4, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 4, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 4, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 4, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 4, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 4, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 4, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 4, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 4, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 4, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1000, 5, 4, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 4, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 4, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 4, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 4, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 920, 5, 4, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1000, 5, 4, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1120, 5, 4, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 4, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 4, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 5, 4, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 920, 5, 4, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 1040, 5, 4, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1120, 5, 4, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1230, 5, 4, 6, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 0, 5, 5, 0, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 40, 5, 5, 0, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 5, 0, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 200, 5, 5, 0, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 5, 0, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 5, 0, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 5, 0, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 120, 5, 5, 1, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 160, 5, 5, 1, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 5, 1, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 320, 5, 5, 1, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 5, 1, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 5, 1, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 5, 1, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 240, 5, 5, 2, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 280, 5, 5, 2, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 5, 2, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 440, 5, 5, 2, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 5, 2, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 5, 2, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 5, 2, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 360, 5, 5, 3, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 400, 5, 5, 3, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 5, 3, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 560, 5, 5, 3, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 5, 3, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 5, 3, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 5, 3, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 480, 5, 5, 4, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 520, 5, 5, 4, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 5, 4, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 680, 5, 5, 4, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 5, 4, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 880, 5, 5, 4, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1000, 5, 5, 4, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 600, 5, 5, 5, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 640, 5, 5, 5, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 5, 5, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 800, 5, 5, 5, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 920, 5, 5, 5, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1000, 5, 5, 5, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1120, 5, 5, 5, 6);
  TEST_SMP4(Solution, getMaxGridHappiness, 720, 5, 5, 6, 0);
  TEST_SMP4(Solution, getMaxGridHappiness, 760, 5, 5, 6, 1);
  TEST_SMP4(Solution, getMaxGridHappiness, 840, 5, 5, 6, 2);
  TEST_SMP4(Solution, getMaxGridHappiness, 920, 5, 5, 6, 3);
  TEST_SMP4(Solution, getMaxGridHappiness, 1040, 5, 5, 6, 4);
  TEST_SMP4(Solution, getMaxGridHappiness, 1120, 5, 5, 6, 5);
  TEST_SMP4(Solution, getMaxGridHappiness, 1240, 5, 5, 6, 6);
  // for (int n = 1; n <= 5; n++) {
  //   for (int m = 1; m <= n; m++) {
  //     for (int a = 0; a <= 6; a++) {
  //       for (int b = 0; b <= 6; b++) {
  //         Solution solution;
  //         int ans = solution.getMaxGridHappiness(n, m, a, b);
  //         printf(
  //             "TEST_SMP4(Solution, getMaxGridHappiness, %d, %d, %d, %d,
  //             %d);\n", ans, n, m, a, b);
  //       }
  //     }
  //   }
  // }

  return 0;
}
