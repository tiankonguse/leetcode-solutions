
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
const int N = 1000010;
const int M = 78599;
bool is[N];
int prm[M];
int K = 0;
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
int getprm() {
  if (K != 0) return K;  // 只计算一次
  // O(n log log n)
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
  return K = k;
}

class Solution {
  vector<vector<int>> prmIndexs;  // 922 / 932 个通过的测试用例
  void Split(const int index, int v) {
    for (int i = 0; i < K && v > 1; i++) {
      if (v % prm[i] == 0) {
        prmIndexs[prm[i]].push_back(index);
        while (v % prm[i] == 0) {
          v /= prm[i];
        }
      }
      if (v > 1 && is[v]) {
        prmIndexs[v].push_back(index);
        break;
      }
    }
  }

 public:
  int minJumps(const vector<int>& nums) {
    getprm();
    int maxV = 0;
    for (auto v : nums) {
      maxV = max(maxV, v+1);
    }
    prmIndexs.resize(maxV);
    const int n = nums.size();
    for (int i = 0; i < n; i++) {
      Split(i, nums[i]);
    }
    vector<int> flag(n, -1);
    queue<int> que;
    auto Add = [&](int i, int step) {
      if (i < 0 || i >= n || flag[i] != -1) return;
      flag[i] = step;
      que.push(i);
    };
    Add(0, 0);
    while (!que.empty()) {
      int i = que.front();
      que.pop();
      int step = flag[i] + 1;
      Add(i + 1, step);
      Add(i - 1, step);
      if (is[nums[i]]) {
        for (auto j : prmIndexs[nums[i]]) {
          Add(j, step);
        }
      }
      if (flag[n - 1] != -1) break;
    }
    return flag[n - 1];
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