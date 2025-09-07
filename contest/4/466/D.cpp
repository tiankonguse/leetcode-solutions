
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
const ll one = 1;
class Solution {
  vector<int> bits;
  int B;   // 二进制位数
  int B2;  // 二进制位数的一半,由于下标从0开始，向下取整
  ll ans = 0;
  void Init(ll n) {
    bits.clear();
    while (n > 0) {
      bits.push_back(n & 1);
      n >>= 1;
    }
    // std::reverse(bits.begin(), bits.end());
    B = bits.size();
    B2 = B / 2;
    MyPrintf("B=%d B2=%d\n", B, B2);
    for (int i = 0; i < B; i++) {
      MyPrintf("%d", bits[i]);
    }
    MyPrintf("\n");
    ans = 1;  // 0 答案是1， 1 答案是2，下面公式少算一个
    for (int i = 1; i < B; i++) {
      MyPrintf("i=%d add=%lld\n", i, one << ((i - 1) / 2));
      ans += one << ((i - 1) / 2);  // 各位任意值的答案，边界必须为1
    }
  }
  void Dfs(int k) {
    MyPrintf("Dfs k=%d B2=%d ans=%lld\n", k, B2, ans);
    if (k < B2) {
      // 需要检查低位一半是否大于高位一半，大于了也有一个答案
      for (int i = B2 - 1; i >= 0; i--) {
        if (bits[i] > bits[B - 1 - i]) {
          ans++;
          return;  // 大于，有答案
        } else if (bits[i] < bits[B - 1 - i]) {
          return;  // 小于没答案
        }
      }
      ans++;  // 相等也有一个答案
    } else {
      if (bits[k] == 1) {          // 取 0 时，后面的都是答案
        ans += (one << (k - B2));  // 各位任意值的答案，边界可以是0
      }
      Dfs(k - 1);  // 取值与 bits[k] 相同
    }
  }

 public:
  int countBinaryPalindromes(ll n) {
    if (n == 0) return 1;
    Init(n);
    MyPrintf("Init ans=%lld\n", ans);
    Dfs(B - 2);  // 最高位必须是1
    return ans;
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