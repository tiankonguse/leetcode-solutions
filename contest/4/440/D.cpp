
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
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
 public:
  ll maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
    // 枚举子数组左端点，看看有多少个合法的右端点

    auto AddTwoQue = [](vector<ll>& nums, ll x) {
      nums.push_back(x);

      int n = nums.size();
      for (int i = n - 1; i > 0; i--) {
        if (nums[i] < nums[i - 1]) {
          swap(nums[i], nums[i - 1]);
        }
      }
      if (n > 2) {
        nums.pop_back();
      }
    };

    vector<vector<ll>> groups(n + 1);
    for (auto& v : conflictingPairs) {
      int a = v[0];
      int b = v[1];
      if (a > b) {
        swap(a, b);
      }
      AddTwoQue(groups[a], b);
    }

    ll sum = 0;  // 不删除可以得到的最大子数组个数
    vector<ll> minQue(2, n + 1);
    vector<ll> secondMinNum(n + 2, 0);
    ll maxAdd = 0;
    for (int l = n; l >= 1; l--) {
      for (auto v : groups[l]) {
        AddTwoQue(minQue, v);
      }
      const ll r0 = minQue.front();  // [l, r)
      const ll r1 = minQue.back();
      sum += r0 - l;
      secondMinNum[r0] += r1 - r0;
      maxAdd = max(maxAdd, secondMinNum[r0]);  // 有变更才有可能得到更大的答案
    }
    return sum + maxAdd;
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