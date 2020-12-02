/*************************************************************************
    > File Name: count-primes.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: 2015年05月06日 星期三 23时48分42秒
 ************************************************************************/

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

const int N = 10000;
const int M = 5000;
class Solution {
  bool is[N];
  int prm[M];
  int prmNum;

 public:
  Solution() { prmNum = getprm(); }
  int getprm() {
    int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
    memset(is, 1, sizeof(is));
    prm[k++] = 2;
    is[0] = is[1] = 0;
    for (i = 4; i < N; i += 2) is[i] = 0;
    for (i = 3; i < e; i += 2) {
      if (is[i]) {
        prm[k++] = i;
        for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
      }
    }
    for (; i < N; i += 2)
      if (is[i]) prm[k++] = i;
    return k;
  }
  bool isPrm(int n) {
    int e = (int)(sqrt(0.0 + n) + 1);
    for (int i = 0; i < prmNum; i++) {
      if (n % prm[i] == 0) {
        return false;
      }
      if (prm[i] > e) {
        break;
      }
    }

    return true;
  }
  void addPrm(int n, int& ans) {
    int e = (int)(sqrt(0.0 + n) + 1);
    for (int i = N; i < n; i++) {
      if (isPrm(i)) {
        ans = ans + 1;
      }
    }
  }
  int countPrimes(int n) {
    int ans = 0;
    int i = 0;
    for (i = 0; i < prmNum; i++) {
      if (prm[i] < n) {
        ans++;
      } else {
        break;
      }
    }
    if (i == prmNum) {
      addPrm(n, ans);
    }
    return ans;
  }
};

int main() {
  TEST_SMP1(Solution, countPrimes, 4, 10);
  TEST_SMP1(Solution, countPrimes, 0, 0);
  TEST_SMP1(Solution, countPrimes, 0, 1);
  TEST_SMP1(Solution, countPrimes, 0, 2);
  TEST_SMP1(Solution, countPrimes, 1, 3);
  TEST_SMP1(Solution, countPrimes, 1229, 10000);
  TEST_SMP1(Solution, countPrimes, 348513, 5000000);
  return 0;
}
