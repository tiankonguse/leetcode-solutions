// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int findChampion(int n, vector<vector<int>>& edges) {
    vector<int> out(n, 1);
    int ansNum = n;
    for (auto& e : edges) {
      int u = e[0];
      int v = e[1];
      if (out[v]) {
        out[v] = 0;
        ansNum--;
      }
    }
    if (ansNum > 1) {
      return -1;
    }
    for (int i = 0; i < n; i++) {
      if (out[i]) {
        return i;
      }
    }
    return 0;
  }
};