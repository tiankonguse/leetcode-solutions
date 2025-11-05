
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

const int maxBit = 7;
const vector<ll> bits = {1, 10, 100, 1000, 10000, 100000, 1000000};
const vector<vector<int>> A3 = {{1, 2, 0}, {2, 0, 1}};
class Solution {
  int SwapBit(const int v, const int i, const int j) {
    const int vi = v / bits[i] % 10;
    const int vj = v / bits[j] % 10;
    return v - vi * bits[i] - vj * bits[j] + vi * bits[j] + vj * bits[i];
  }

  unordered_map<int, bitset<5005>> valIndexs;
  int n;
  vector<int> newVal;
  bitset<5005> flag;
  int Solver(int v, int idx) {
    flag.reset();
    newVal.clear();

    // 不交换

    for (int i = 0; i < n; i++) {
      if (valIndexs[v].test(i)) {
        flag[i] = 1;
      }
    }
    // 交换 2 个位置
    for (int i = 0; i < maxBit; i++) {
      for (int j = i + 1; j < maxBit; j++) {
        // 交换 v 的 第 i 和 第 j 位
        int V = SwapBit(v, i, j);
        int vi = v / bits[i] % 10;
        int vj = v / bits[j] % 10;
        if (vi == vj) continue;  // 没有变化
        newVal.push_back(V);
        flag |= valIndexs[V];
      }
    }
    valIndexs[v].set(idx);
    for (auto v : newVal) {  // 最多 49 个
      valIndexs[v].set(idx);
    }
    return flag.count();
  }

 public:
  int countPairs(vector<int>& nums) {
    n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += Solver(nums[i], i);
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