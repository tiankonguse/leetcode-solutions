
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
class Solution {
 public:
  int minAllOneMultiple(int k) {
    int k0 = k % 10;
    unordered_set<int> validK0 = {1, 3, 7, 9};
    if (!validK0.count(k0)) {
      return -1;
    }
    vector<ll> base10(11, 1);
    for (int i = 1; i <= 10; i++) {
      base10[i] = base10[i - 1] * 10;
    }
    vector<int> mulTable(10);
    for (int j = 0; j <= 9; j++) {
      mulTable[(k0 * j) % 10] = j;
    }

    set<pair<int, ll>> H;

    auto Add = [&H](int len, int val) -> bool {  //
      pair<int, ll> key = {len, val};
      if (H.count(key)) {
        return false;
      }
      H.insert({len, val});
      return true;
    };
    int ans = 1;
    int len = 1;
    ll now = 1;
    Add(len, now);
    while (now) {
      const int lastDigit = now % 10;
      const ll lastMul = mulTable[lastDigit];
      const ll lastRes = k * lastMul;

      while (now < lastRes) {
        now = now + base10[len];
        len++;
        ans++;
      }
      if (now % k == 0) {
        return ans;
      }
      now = now - lastRes;
      now = now / 10;
      len--;
      if (!Add(len, now)) {
        break;
      }
    }

    return -1;
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