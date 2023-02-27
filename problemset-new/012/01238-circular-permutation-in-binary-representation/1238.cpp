// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> dp;
  int n;
  int num = 0;
  int GetNext(int start) {
    for (int i = 0; i < n; i++) {
      int v = start ^ (1 << i);
      if (dp[v] == -1) {
        return v;
      }
    }
    return -1;
  }

  int Cal(int start) {
    int nextStart = GetNext(start);
    while (nextStart != -1) {
      dp[start] = nextStart;
      num++;
      start = nextStart;
      nextStart = GetNext(start);
    }
    return start;
  }

 public:
  vector<int> circularPermutation(int n_, int start) {
    n = n_;
    int N = 1 << n;
    dp.resize(N, -1);

    dp[start] = start;
    num++;

    while (num < N) {
      while (GetNext(start) == -1) {
        start = dp[start];
      }

      int nextStart = dp[start];
      auto tail = Cal(start);
      dp[tail] = nextStart;
    }

    vector<int> ans;
    for (int i = start; ans.size() < N; i = dp[i]) {
      ans.push_back(i);
    }
    return ans;
  }
};