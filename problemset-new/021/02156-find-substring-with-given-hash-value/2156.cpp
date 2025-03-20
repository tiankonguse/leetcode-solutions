
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
class Solution {
  ll Pow(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
      if (b & 1) {
        ans = ans * a % mod;
      }
      a = a * a % mod;
      b >>= 1;
    }
    return ans;
  }

 public:
  string subStrHash(string s, int power, int modulo, int k, int hashValue) {
    std::reverse(s.begin(), s.end());
    int n = s.size();
    ll pk1 = Pow(power, k - 1, modulo);
    int ansPos = -1;
    ll hash = 0;
    for (int i = 0; i < n; i++) {
      ll val = s[i] - 'a' + 1;
      hash = (hash * power + val) % modulo;
      if (i < k - 1) continue;
      if (hash == hashValue) {
        ansPos = i;
      }
      ll val2 = s[i - k + 1] - 'a' + 1;
      hash = (hash - val2 * pk1 % modulo + modulo) % modulo;
    }
    std::reverse(s.begin(), s.end());
    return s.substr(n - 1 - ansPos, k);
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