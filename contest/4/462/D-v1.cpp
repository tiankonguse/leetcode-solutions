
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
constexpr ll INFL = 1LL << 60;
class Solution {
  int Len(ll a) {
    if (a == 0) return 1;
    int len = 0;
    while (a > 0) {
      a /= 10;
      len++;
    }
    return len;
  }
  ll bits[10];
  ll n;
  ll dfsAns;
  bool DfsAll(const int len, const int mid, const int offset, const ll val) {
    if (offset == len / 2) {
      // 先检查 数字中每个数字 k 出现 恰好 k 次
      if (mid > 0 && bits[mid] != mid) {
        return false;
      }
      for (int i = 2; i < 10; i += 2) {
        if (bits[i] > 0 && bits[i] != i) {
          return false;
        }
      }
      if (this->n < val) {
        dfsAns = val;
        return true;
      } else {
        return false;
      }
    }
    for (int i = 2; i < 10; i++) {  // 从小到大枚举，确保答案是最小的
      if (bits[i] < i && (i == mid || i % 2 == 0)) {
        bits[i] += 2;
        if (DfsAll(len, mid, offset + 1, val + i * B[offset] + i * B[len - 1 - offset])) {
          return true;
        }
        bits[i] -= 2;
      }
    }
    return false;
  }

  // 求大于 n 的长度为 len 的答案，其中 n 的长度也是 Len
  ll TryLen(int len) {
    if (len % 2 == 0) {
      fill(bits, bits + 10, 0);
      if (DfsAll(len, 0, 0, 0)) {
        return dfsAns;
      }
    } else {
      ll ans = INFL;
      for (int mid = 1; mid < 10; mid += 2) {
        fill(bits, bits + 10, 0);
        bits[mid]++;
        dfsAns = INFL;
        if (DfsAll(len, mid, 0, mid * B[len / 2])) {
          ans = min(ans, dfsAns);
        }
      }
      if (ans != INFL) {
        return ans;
      }
    }
    return 0;
  }

  ll B[20];
  void Init() {
    B[0] = 1;
    for (int i = 1; i <= 16; i++) {
      B[i] = B[i - 1] * 10;
    }
  }

 public:
  long long specialPalindrome(long long n) {  //
    Init();
    this->n = n;
    const int len = Len(n);
    MyPrintf("len = %d\n", len);
    ll ans = TryLen(len);
    if (ans > 0) {
      return ans;
    }
    return TryLen(len + 1);
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