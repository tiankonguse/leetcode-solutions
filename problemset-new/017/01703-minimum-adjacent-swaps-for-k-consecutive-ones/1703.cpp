// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> onePos;
  unordered_map<int, int> m;

  int n;
  vector<ll> preSum;
  vector<ll> preOneNum;
  vector<ll> sufSum;
  vector<ll> sufOneNum;
  void Init(vector<int>& nums) {  //
    n = nums.size();
    preOneNum.resize(n + 2, 0);
    preSum.resize(n + 2, 0);
    sufSum.resize(n + 2, 0);
    sufOneNum.resize(n + 2, 0);

    for (int i = 1; i <= n; i++) {
      int v = nums[i - 1];
      preSum[i] = preSum[i - 1];
      preOneNum[i] = preOneNum[i - 1];
      if (v == 0) {
        preSum[i] += preOneNum[i - 1];
      } else {
        preOneNum[i] += 1;
      }
    }

    for (int i = n; i >= 1; i--) {
      int v = nums[i - 1];
      sufSum[i] = sufSum[i + 1];
      sufOneNum[i] = sufOneNum[i + 1];
      if (v == 0) {
        sufSum[i] += sufOneNum[i + 1];
      } else {
        sufOneNum[i] += 1;
      }
    }
  }

  ll GetZeroNum(int i, int j) {
    return (j - i + 1) - (preOneNum[j] - preOneNum[i - 1]);
  }

  // [i,j]之内的所有0移动到左边
  // 移动次数只与0左边 1 的个数有关
  ll SolverLeft(int i, int j) {
    int oneNum = preOneNum[i - 1];
    int zeroNum = GetZeroNum(i, j);
    return (preSum[j] - preSum[i - 1]) - zeroNum * oneNum;
  }

  ll SolverRight(int i, int j) {
    int oneNum = sufOneNum[j + 1];
    int zeroNum = GetZeroNum(i, j);
    return (sufSum[i] - sufSum[j + 1]) - zeroNum * oneNum;
  }

  // [i, j] 内恰好有 k 个 1, 下标从 1 开始，到 n
  ll Solver(int i, int j, int k) {
    if (j - i + 1 == k) {
      return 0;  // 连续 k 个 1
    }

    int leftOnePos = m[i];   // i 是第几个 1
    int rightOnePos = m[j];  // j 是第几个 1

    int midOnePos = (leftOnePos + rightOnePos) / 2;
    int mid = onePos[midOnePos];
    // printf("leftOnePos=%d rightOnePos=%d\n", leftOnePos, rightOnePos);
    // printf("midOnePos=%d mid=%d\n", midOnePos, mid);

    // 左半部
    ll ans = 0;
    ll leftAns = SolverLeft(i, mid);
    ll rightAns = SolverRight(mid + 1, j);
    // printf("leftAns=%lld rightAns=%lld\n", leftAns, rightAns);
    ans += leftAns;
    ans += rightAns;
    return ans;
  }

 public:
  int minMoves(vector<int>& nums, int k) {
    Init(nums);

    n = nums.size();
    onePos.push_back(0);
    for (int i = 1; i <= n; i++) {
      if (nums[i - 1] == 1) {
        m[i] = onePos.size();
        onePos.push_back(i);
      }
    }

    ll ans = LONG_MAX;
    for (int i = 1; i <= n; i++) {
      if (nums[i - 1] == 0) continue;
      int leftOnePos = m[i];
      int rightOnePos = leftOnePos + k - 1;
      if (rightOnePos >= onePos.size()) {
        continue;  // 以 i 为左边界，右边不够 k 个 1
      }
      int j = onePos[rightOnePos];
    //   printf("i=%d j=%d\n", i, j);
      ll tmp = Solver(i, j, k);
    //   printf("i=%d j=%d ans=%lld\n", i, j, tmp);
      ans = min(ans, tmp);
    }
    return ans;
  }
};

int main() {
  printf("\n\n");
  int ans;
  vector<int> nums;
  int k;

  ans = 1;
  nums = {1, 0, 0, 1, 0, 1};
  k = 2;
  TEST_SMP2(Solution, minMoves, ans, nums, k);


  ans = 5;
  nums = {1,0,0,0,0,0,1,1};
  k = 3;
  TEST_SMP2(Solution, minMoves, ans, nums, k);


  ans = 0;
  nums = {1,1,0,1};
  k = 2;
  TEST_SMP2(Solution, minMoves, ans, nums, k);

  return 0;
}
