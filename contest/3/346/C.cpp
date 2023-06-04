// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
map<pair<int, int>, int> h;
int max_n = 1;
vector<int> base = {1};

int Dfs(int n, int nn) {
  if (n == nn) return 1;
  if (n > nn) return 0;
  int& ans = h[{n, nn}];

  int base = 1;
  while (base <= nn) {
    base = base * 10;
    int right = nn % base;
    int left = nn / base;
    if (right > n) break;
    if (Dfs(n - right, left)) {
      return ans = 1;
    }
  }
  return ans = 0;
}

void Init(int n) {
  while (base.size() <= 7) {
    base.push_back(base.back() * 10);
  }
  while (max_n <= n) {
    Dfs(max_n, max_n * max_n);
    max_n++;
  }
}
class Solution {
 public:
  int punishmentNumber(int n) {
    Init(n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      if (h[{i, i * i}] == 1) {
        ans += i * i;
      }
    }
    return ans;
  }
};