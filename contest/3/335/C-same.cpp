// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 1000100;
const int M = 80000;
bool is[N];
int prm[M];
int getprm() {
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
  return k;
}

class Solution {
 public:
  int findValidSplit(vector<int>& nums) {
    int n = nums.size();
    int prmNum = getprm();
    vector<vector<int>> grid(n);
    unordered_set<int> L;
    unordered_map<int, int> R;

    for (int i = n - 1; i >= 0; i--) {
      int v = nums[i];

      int k = 0;
      while (v > 1) {
        if (is[v]) {
          grid[i].push_back(v);
          break;
        }

        while (v % prm[k] != 0) {
          k++;
        }
        while (v % prm[k] == 0) {
          v /= prm[k];
        }
        grid[i].push_back(prm[k]);
        k++;
      }

      for (auto v : grid[i]) {
        R[v]++;
      }
    }

    for (int i = 0; i + 1 < n; i++) {
      for (auto v : grid[i]) {
        R[v]--;
        L.insert(v);
      }

      while (!L.empty()) {
        int v = *L.begin();
        if (R[v]) break;
        L.erase(v);
      }

      if (L.empty()) {
        return i;
      }
    }

    return -1;
  }
};