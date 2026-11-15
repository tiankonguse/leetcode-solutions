
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const int B = 21;
class Solution {
  int n;
  vector<vector<int>> bits;
  ll SearchLeft(const int L, const int p, const int b) {
    int l = L, r = p;  // [l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      if (bits[p][b] - bits[mid - 1][b] == p - mid + 1) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
  ll SearchRight(const int p, const int R, const int b) {
    int l = p, r = R;  // [l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      if (bits[mid][b] - bits[p - 1][b] == mid - p + 1) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l - 1;
  }
  unordered_map<ll, ll> mp;
  ll Solver(const int p, const ll v) {
    ll leftPos = 1;
    if (mp.count(v) && mp[v] > leftPos) {
      leftPos = mp[v];
    }
    ll rightPos = n;
    for (int i = 0; i < B; i++) {
      if ((v >> i) & 1) {
        leftPos = max(leftPos, SearchLeft(leftPos, p, i));
        rightPos = min(rightPos, SearchRight(p, rightPos + 1, i));
        MyPrintf("p=%d v=%lld b=%d leftPos=%lld rightPos=%lld\n", p, v, i, leftPos, rightPos);
      }
    }
    MyPrintf("p=%d v=%lld leftPos=%lld rightPos=%lld\n", p, v, leftPos, rightPos);
    mp[v] = p + 1;
    return (p - leftPos + 1) * (rightPos - p + 1);
  }

 public:
  ll countConsistent(vector<int>& nums) {
    n = nums.size();
    bits.resize(n + 1, vector<int>(B, 0));
    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      MyPrintf("v=%d :", v);
      for (int j = 0; j < B; j++) {
        bits[i][j] = bits[i - 1][j] + ((v >> j) & 1);
        MyPrintf("%d ", bits[i][j]);
      }
      MyPrintf("\n");
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ll cur = Solver(i, nums[i - 1]);
      MyPrintf("i = %d, cur = %lld\n", i, cur);
      ans += cur;
    }
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