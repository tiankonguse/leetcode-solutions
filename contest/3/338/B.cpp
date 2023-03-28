// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int N = 1010;
const int M = 1010;
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
  bool primeSubOperation(vector<int>& nums) {
    int k = getprm();
    int pre = 0;
    for (auto v : nums) {
      if (v <= pre) {
        return false;  // 没有答案
      }
      int tmp = v;
      for (int i = 0; i < k; i++) {
        if (v - prm[i] > pre) {
          tmp = v - prm[i];
        } else {
          break;
        }
      }
      pre = tmp;
    }
    return true;
  }
};